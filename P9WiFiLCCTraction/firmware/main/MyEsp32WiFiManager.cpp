// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Fri Mar 27 12:21:25 2026
//  Last Modified : <260401.1440>
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

static const char rcsid[] = "@(#) : $Id$";

#include "openlcb/ConfiguredTcpConnection.hxx" 
#include "executor/Executor.hxx"
#include "executor/Service.hxx"
#include "executor/StateFlow.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "openlcb/ConfiguredTcpConnection.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/GcTcpHub.hxx"
#include "utils/macros.h"
#include "utils/Singleton.hxx"
#include <freertos_drivers/common/WifiDefs.hxx>
#include "MyEsp32WiFiManager.hxx"
#include "openlcb/SimpleStack.hxx"
#include "openlcb/TcpDefs.hxx"
#include "os/MDNS.hxx"
#include "utils/FdUtils.hxx"
#include "utils/format_utils.hxx"
#include "utils/SocketClient.hxx"
#include "utils/SocketClientParams.hxx"
#include <freertos_drivers/esp_idf/EspIdfWiFi.hxx>



static string formhostname(const char *prefix, uint64_t nodeid)
{
    char buffer[32];
    snprintf(buffer,sizeof(buffer),"%s_%06llx", prefix, nodeid);
    return string(buffer);
}

MyEsp32WiFiManager::MyEsp32WiFiManager(const char *station_ssid
                                       , const char *station_password
                                       , openlcb::SimpleStackBase *stack
                                       , const openlcb::TcpClientConfig<openlcb::TcpClientDefaultParams> &cfg
                                       , const char *hostname_prefix)
      : DefaultConfigUpdateListener()
, hostname_(formhostname(hostname_prefix,stack->node()->node_id()))
, ssid_(station_ssid)
, password_(station_password)
, cfg_(cfg)
, stack_(stack)
, espIdfWiFi_(stack->service(),hostname_.c_str(),"","",
              WiFiDefs::SecurityType::SEC_OPEN,
              station_ssid,station_password)
{
}

MyEsp32WiFiManager::~MyEsp32WiFiManager()
{
}


void MyEsp32WiFiManager::display_configuration()
{
    LOG(INFO, "[WiFi] Configuration Settings:");
    LOG(INFO, "[WiFi] Station SSID:'%s'", ssid_.c_str());
    LOG(INFO, "[WiFi] Hostname:%s", hostname_.c_str());
}

ConfigUpdateListener::UpdateAction 
      MyEsp32WiFiManager::apply_configuration(int fd, 
                                              bool initial_load,
                                              BarrierNotifiable *done)
{
    esp32Params_.reset(new Esp32SocketParams(fd,cfg_));
    if (initial_load)
    {
        //espIdfWiFi_.disable_mdns_publish_on_sta ();
        espIdfWiFi_.init();
        espIdfWiFi_.set_ip_acquired_callback(std::bind(&MyEsp32WiFiManager::connect_callback_,
                                                       this,
                                                       std::placeholders::_1,
                                                       std::placeholders::_2));
        espIdfWiFi_.start(WlanRole::STA);
    }
    else
    {
        if (uplink_)
        {
            // If we already have an uplink, update the parameters it is using.
            uplink_->reset_params(std::move(esp32Params_));
        }
    }

    // Inform the caller that the configuration has been updated as the wifi
    // task will reload the configuration as part of it's next wake up cycle.
    return ConfigUpdateListener::UpdateAction::UPDATED;
}

void MyEsp32WiFiManager::factory_reset(int fd)
{
    // Node link configuration settings.
    CDI_FACTORY_RESET(cfg_.search_mode);
    CDI_FACTORY_RESET(cfg_.reconnect);

    // Node link manual configuration settings.
    cfg_.manual_address().ip_address().write(fd, "");
    CDI_FACTORY_RESET(cfg_.manual_address().port);

    // Node link automatic configuration settings.
    cfg_.auto_address().service_name().write(
        fd, openlcb::TcpDefs::MDNS_SERVICE_NAME_GRIDCONNECT_CAN_TCP);
    cfg_.auto_address().host_name().write(fd, "");

    // Node link automatic last connected node address.
    cfg_.last_address().ip_address().write(fd, "");
    CDI_FACTORY_RESET(cfg_.last_address().port);

    // Reconnect to last connected node.
    CDI_FACTORY_RESET(cfg_.reconnect);
}

void MyEsp32WiFiManager::connect_callback_(WiFiDefs :: Interface iface , 
                                                          bool acquired )
{
    if (acquired && ! mdns_started_)
    {
        mdns_started_ = true;
        LOG(INFO,"[MyEsp32WiFiManager::WiFiStackFlow] connect_callback_() ip acquired");
        uplink_.reset(new SocketClient(stack_->service(), stack_->executor(),
                                       stack_->executor(), 
                                       std::move(esp32Params_),
                                       std::bind(&MyEsp32WiFiManager::on_uplink_created, 
                                                 this,
                                                 std::placeholders::_1, 
                                                 std::placeholders::_2)));
        
    }
}

void MyEsp32WiFiManager::on_uplink_created(int fd, Notifiable *on_exit)
{
    LOG(INFO, "[Uplink] Connected to hub, configuring GridConnect HubPort.");

    // stash the socket handle and notifiable for future use if we need to
    // clean up or re-establish the connection.
    uplinkFd_ = fd;
    uplinkNotifiable_ = on_exit;

    const bool use_select =
        (config_gridconnect_tcp_use_select() == CONSTANT_TRUE);

    // create the GridConnect port from the provided socket fd.
    // NOTE: this uses a local notifiable object instead of the provided
    // on_exit since it will be invalidated upon calling stop_uplink() which
    // may result in a crash or other undefined behavior.
    create_gc_port_for_can_hub(
        static_cast<openlcb::SimpleCanStackBase *>(stack_)->can_hub(),
        uplinkFd_, &uplinkNotifiableProxy_, use_select);

    // restart the stack to kick off alias allocation and send node init
    // packets.
    stack_->restart_stack();
}
