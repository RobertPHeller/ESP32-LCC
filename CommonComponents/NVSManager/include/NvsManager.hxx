// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Dec 17 13:13:14 2022
//  Last Modified : <231105.1500>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2022  Robert Heller D/B/A Deepwoods Software
///			51 Locke Hill Road
///			Wendell, MA 01379-9728
///
///    This program is free software; you can redistribute it and/or modify
///    it under the terms of the GNU General Public License as published by
///    the Free Software Foundation; either version 2 of the License, or
///    (at your option) any later version.
///
///    This program is distributed in the hope that it will be useful,
///    but WITHOUT ANY WARRANTY; without even the implied warranty of
///    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///    GNU General Public License for more details.
///
///    You should have received a copy of the GNU General Public License
///    along with this program; if not, write to the Free Software
///    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/// @file NvsManager.hxx
/// @author Robert Heller 
/// @date Sat Dec 17 13:13:14 2022
//////////////////////////////////////////////////////////////////////////////

#ifndef __NVSMANAGER_HXX
#define __NVSMANAGER_HXX

#include "sdkconfig.h"
#include <esp_wifi_types.h>
#include <esp_err.h>
#include <esp_partition.h>

#include <nvs.h>
#include <nvs_flash.h>
#include <string>
#include <string.h>
#include <utils/Singleton.hxx>
#include <utils/format_utils.hxx>

namespace openlcb
{
    class Node;
    class SimpleStackBase;
}
namespace openmrn_arduino
{
    class Esp32WiFiManager;
}

namespace nvsmanager
{

class NvsManager : public Singleton<NvsManager>
{
public:
    void init(uint8_t reset_reason);
    inline bool should_reset_config() {return config_.force_reset;}
    inline bool should_reset_events() {return config_.reset_events_req;}
    inline bool should_start_bootloader() {return config_.bootloader_req;}
    inline void force_factory_reset() 
    {                                        
        config_.force_reset = true;
        need_persist_ = true;
    }                                     
    inline void clear_factory_reset()
    {
        config_.force_reset = false;
        need_persist_ = true;
    }
    inline void force_reset_events()
    {
        config_.reset_events_req = true;
        need_persist_ = true;
    }
    inline void clear_reset_events()
    {
        config_.reset_events_req = false;
        need_persist_ = true;
    }
    inline void force_bootloader()
    {
        config_.bootloader_req = false;
        need_persist_ = true;          
    }
    inline void clear_bootloader()
    {
        config_.bootloader_req = false;
        need_persist_ = true;
    }
    inline bool should_test_signal_lamps() {return config_.test_signal_lamps;}
    inline void force_test_signal_lamps()
    {
        config_.test_signal_lamps = true;
        need_persist_ = true;
    }
    inline void clear_test_signal_lamps()
    {
        config_.test_signal_lamps = false;
        need_persist_ = true;
    }
    inline uint64_t node_id() {return config_.node_id;}
    inline void node_id(uint64_t node_id)
    {
        config_.node_id = node_id;
        config_.force_reset = true;
        need_persist_ = true;
    }
#ifdef CONFIG_ESP32_WIFI_ENABLED
    inline wifi_mode_t wifi_mode() {return config_.wifi_mode;}
    inline void wifi_mode(wifi_mode_t mode)
    {
        config_.wifi_mode = mode;
        need_persist_ = true;
    }
    inline const char *station_ssid() {return config_.station_ssid;}
    inline void station_ssid(const char *ssid)
    {
        int i;
        const char *s = ssid;
        char *d = config_.station_ssid;
        for (i = 0; i <= sizeof(config_.station_ssid) && *s != '\0';i++)
            *d++ = *s++;
        config_.station_ssid[sizeof(config_.station_ssid)-1] = 0;
        need_persist_ = true;
    }
    inline const char *station_pass() {return config_.station_pass;}
    inline void station_pass(const char *password)
    {
        int i;
        const char *s = password;
        char *d = config_.station_pass;
        for (i = 0; i <= sizeof(config_.station_pass) && *s != '\0';i++)
            *d++ = *s++;
        config_.station_pass[sizeof(config_.station_pass)-1] = 0;
        need_persist_ = true;
    }
    inline const char *hostname_prefix() {return config_.hostname_prefix;}
    inline void hostname_prefix(const char *hostname)
    {
        int i;
        const char *s = hostname;
        char *d = config_.hostname_prefix;
        for (i = 0; i <= sizeof(config_.hostname_prefix) && *s != '\0';i++)
            *d++ = *s++;
        config_.hostname_prefix[sizeof(config_.hostname_prefix)-1] = 0;
        need_persist_ = true;
    }
#endif
    NvsManager() : need_persist_(false) 
    {
    }
    inline bool CheckPersist() 
    {
        if (need_persist_) {
            persist_configuration();
            return true;
        } else {
            return false;
        }
    }
    void DisplayNvsConfiguration();
    void register_virtual_memory_spaces(openlcb::SimpleStackBase *stack);
private:
    /// NVS Persistence namespace.
    static constexpr char NVS_NAMESPACE[] = "node";

    /// NVS Persistence key.
    static constexpr char NVS_CFG_KEY[] = "cfg";

    struct {
        uint64_t node_id;
        bool force_reset;
        bool bootloader_req;
        bool reset_events_req;
        bool test_signal_lamps;
#ifdef CONFIG_ESP32_WIFI_ENABLED
        char hostname_prefix[16];
        char station_ssid[33];
        char station_pass[33];
        wifi_mode_t wifi_mode;
#endif
        uint8_t reserved[20];
    } config_;
    bool need_persist_;
    inline void persist_configuration()
    {
        nvs_handle_t nvs;
        ESP_ERROR_CHECK(nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs));
        ESP_ERROR_CHECK(nvs_set_blob(nvs, NVS_CFG_KEY, &config_, sizeof(config_)));
        ESP_ERROR_CHECK(nvs_commit(nvs));
        nvs_close(nvs);
        need_persist_ = false;
    }
};

}

#endif // __NVSMANAGER_HXX

