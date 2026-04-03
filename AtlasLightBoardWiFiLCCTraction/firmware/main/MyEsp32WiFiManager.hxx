// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Fri Mar 27 11:41:42 2026
//  Last Modified : <260329.1524>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2026  Robert Heller D/B/A Deepwoods Software
//			51 Locke Hill Road
//			Wendell, MA 01379-9728
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __MYESP32WIFIMANAGER_HXX
#define __MYESP32WIFIMANAGER_HXX

#include "executor/Service.hxx"
#include "openlcb/ConfiguredTcpConnection.hxx"
#include "openmrn_features.h"
#include "utils/format_utils.hxx"

#include <sys/socket.h>

#include <list>

#include <freertos_drivers/esp_idf/EspIdfWiFi.hxx>
#include <openlcb/ConfiguredTcpConnection.hxx>
#include <utils/SocketClient.hxx>
#include <utils/SocketClientParams.hxx>
#include "executor/Executor.hxx"
#include "executor/Service.hxx"
#include "executor/StateFlow.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "openlcb/ConfiguredTcpConnection.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/GcTcpHub.hxx"
#include "utils/macros.h"
#include "utils/Singleton.hxx"

namespace openlcb
{
class SimpleStackBase;
}

class SocketClient;

class MyEsp32WiFiManager 
      : public DefaultConfigUpdateListener
, public Singleton<MyEsp32WiFiManager>
{
public:
    /// Constructor.
    ///
    /// With this constructor the ESP32 WiFi and MDNS systems will be managed
    /// automatically by the Esp32WiFiManager class in addition to the inbound
    /// and outbound connections. The WiFi and MDNS systems will only be
    /// started after the initial loading of the CDI which occurs only after  
    /// the application code calls OpenMRN::begin().
    /// @param station_ssid is the WiFi AP to connect to.
    /// @param station_password is the password for the WiFi AP being connected
    /// to.
    /// @param stack is the SimpleCanStackBase for this node. Must stay alive
    /// forever.
    /// @param cfg is the WiFiConfiguration instance used for this node. This
    /// will be monitored for changes and the WiFi behavior altered
    /// accordingly.
    /// @param hostname_prefix is the hostname prefix to use for this node.
    /// The @ref NodeID will be appended to this value. The maximum length for
    /// final hostname is 32 bytes.
    MyEsp32WiFiManager(const char *station_ssid
                       , const char *station_password
                       , openlcb::SimpleStackBase *stack
                       , const openlcb::TcpClientConfig<openlcb::TcpClientDefaultParams> &cfg
                       , const char *hostname_prefix = "esp32_");
    /// Destructor.
    ~MyEsp32WiFiManager();
    
    /// Display the configuration settings in use. 
    void display_configuration();
    
    /// Updates the TcpClientConfig settings used by this node.
    ///
    /// @param fd is the file descriptor used for the configuration settings.
    /// @param initial_load is set to true when this node loads the
    /// configuration for the first time, otherwise it is an update to the
    /// configuration and may require a restart.
    /// @param done is the control used by the caller to track when all config
    /// consumers have completed their updates.
    ///
    /// @return UPDATED when the configuration has been successfully updated,
    /// or REBOOT_NEEDED if the node needs to reboot for configuration to take
    /// effect.
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    /// Resets the TcpClientConfig settings used by this node.
    ///
    /// @param fd is the file descriptor used for the configuration settings.
    virtual void factory_reset(int fd);
    
    
    const char *Hostname() const {return hostname_.c_str();}
    const char *Ssid() const {return ssid_.c_str();}
    const char *Password() const {return password_.c_str();}
private:
    /// Default constructor.
    MyEsp32WiFiManager();
    
    /// Dynamically generated hostname for this node, esp32_{node-id}. This is
    /// also used for the SoftAP SSID name (if enabled).
    std::string hostname_;
    
    /// User provided SSID to connect to.
    std::string ssid_;

    /// User provided password for the SSID to connect to.
    std::string password_;

    /// Persistent configuration that will be used for this node's WiFi usage.
    const openlcb::TcpClientConfig<openlcb::TcpClientDefaultParams> cfg_;
    
    /// Notifiable handle provided by the @ref SocketClient once a connection
    /// has been established. This will be called by @ref UplinkNotifiable when
    /// not null and the connection needs to be re-established. This will be
    /// set to null when the uplink is intentionally disconnected by
    /// configuration updates.
    Notifiable *uplinkNotifiable_{nullptr};
    
    /// Socket handle used by the uplink connection.
    int uplinkFd_{-1};
    
    /// OpenMRN stack for the Arduino system.
    openlcb::SimpleStackBase *stack_;

    /// This class provides a proxy for the @ref Notifiable provided by the
    /// @ref SocketClient. This is necessary to ensure the @ref Notifiable does
    /// not get invalidated when the @ref SocketClient is deleted prior to the
    /// socket being closed.
    class UplinkNotifiable : public Notifiable
    {
    public:
        /// Constructor.
        ///
        /// @param parent @ref Esp32WiFiManager instance that this notifiable
        /// will interact with for uplink disconnect events.
        UplinkNotifiable(MyEsp32WiFiManager *parent) : parent_(parent)
        {
        }

        /// Proxies the notify() call to the uplink if it is not null.
        virtual void notify() override
        {
            // if we have a valid notifiable from the uplink forward the notify
            // call, otherwise this method is a no-op.
            if (parent_->uplinkNotifiable_ != nullptr)
            {
                parent_->uplinkNotifiable_->notify();
            }
        }
    private:
        /// @ref Esp32WiFiManager instance that manages this class instance.
        MyEsp32WiFiManager *parent_;
    };

    /// @ref UplinkNotifiable to use for uplink connections.
    UplinkNotifiable uplinkNotifiableProxy_{this};

    /// Connection callback, called when the connection has been completed.
    void connect_callback_(WiFiDefs :: Interface iface , bool acquired);
    
    /// Callback for the @ref SocketClient to handle a newly connected outbound
    /// socket connection.
    ///
    /// @param fd is the connected socket descriptor.
    /// @param on_exit is the Notifiable for when this socket has closed.
    void on_uplink_created(int fd, Notifiable *on_exit);

    /// EspIdfWiFi object
    EspIdfWiFiNoConfig espIdfWiFi_;
    bool mdns_started_{false};

    /// Adapter class to load/store configuration via CDI
    class Esp32SocketParams : public DefaultSocketClientParams
    {
    public:
        Esp32SocketParams(
                          int fd, const openlcb::TcpClientConfig<openlcb::TcpClientDefaultParams> &cfg)
        {
            // set the parameters on the parent class, all others are loaded
            // on-demand.
            mdnsService_ = cfg.auto_address().service_name().read(fd);
            staticHost_ = cfg.manual_address().ip_address().read(fd);
            staticPort_ = CDI_READ_TRIMMED(cfg.manual_address().port, fd);
            search_mode_ = (SocketClientParams::SearchMode)CDI_READ_TRIMMED(cfg.search_mode, fd);
            mdnsHostName_ = cfg.auto_address().host_name().read(fd);
            enableLast_ = CDI_READ_TRIMMED(cfg.reconnect, fd);
            lastHostName_ = cfg.last_address().ip_address().read(fd);
            lastPort_ = CDI_READ_TRIMMED(cfg.last_address().port, fd);
        }
        
        /// @return search mode for how to locate the server.
        SocketClientParams::SearchMode search_mode() override
        {
            return search_mode_;
        }
        
        /// @return null or empty string if any mdns server is okay to connect
        /// to. If nonempty, then only an mdns server will be chosen that has the
        /// specific host name.
        string mdns_host_name() override
        {
            return mdnsHostName_;
        }
        
        /// @return true if first attempt should be to connect to
        /// last_host_name:last_port.
        bool enable_last() override
        {
            return enableLast_;
        }
        
        /// @return the last successfully used IP address, as dotted
        /// decimal. Nullptr or empty if no successful connection has ever been
        /// made.
        string last_host_name() override
        {
            return lastHostName_;
        }
        
        /// @return the last successfully used port number.
        int last_port() override
        {
            return lastPort_;
        }
         
        /// Stores the last connection details for use when reconnect is enabled.
        ///
        /// @param hostname is the hostname that was connected to.
        /// @param port is the port that was connected to.
        void set_last(const char *hostname, int port) override
        {
            //cfg_.last_address().ip_address().write(configFd_, hostname);
            //cfg_.last_address().port().write(configFd_, port);
        }
        
        
        /// @return true if we should actively skip connections that happen to
        /// match our own IP address.
        bool disallow_local() override
        {
            return true;
        }
        
    private:
        SocketClientParams::SearchMode search_mode_;
        string mdnsHostName_;
        bool enableLast_;
        string lastHostName_;
        int lastPort_;
    
    };
    
    /// Socket parameters.
    std::unique_ptr<Esp32SocketParams> esp32Params_{nullptr};
    
    /// @ref SocketClient for this node's uplink connection.
    std::unique_ptr<SocketClient> uplink_;
    
    DISALLOW_COPY_AND_ASSIGN(MyEsp32WiFiManager);
};

#endif // __MYESP32WIFIMANAGER_HXX

