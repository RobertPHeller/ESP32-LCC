// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-29 15:16:51
//  Last Modified : <251130.0828>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2025  Robert Heller D/B/A Deepwoods Software
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
/// @file AtlasLightBoardWiFiLCCTraction.cpp
/// @author Robert Heller
/// @date 2025-11-29 15:16:51
/// 
///
//////////////////////////////////////////////////////////////////////////////

/** @mainpage Introduction 
 * Atlas Light Board WiFi LCC Traction node.
 * 
 * @image html AtlasLightBoardWiFiLCCTraction_Top3D.png
 * 
 * This is a WiFi LCC node that drops in to any locomotive that takes a
 * DCC decoder that follows the Atlas Light Board form factor.  This
 * board replaces a DCC decoder and works as a LCC node that connects via
 * WiFi using a GC Hub (such as the one provided by JMRI or OpenMRN). It
 * needs a LCC aware throttle (such as TCS's UWT-100).  It does NOT need
 * a command station, but does need powered rails (either DC or DCC).
 */

static const char rcsid[] = "@(#) : $Id$";


#include "sdkconfig.h"
#include "cdi.hxx" 
#include "cdidata.hxx"
#include "DelayRebootHelper.hxx"
#include "FactoryResetHelper.hxx"
#include "HealthMonitor.hxx"
#include "fs.hxx"
#include "NodeRebootHelper.hxx"
#include "NvsManager.hxx"

#include <algorithm>
#include <driver/uart.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_ota_ops.h>
#include <esp_system.h>
#include <esp_task_wdt.h>
#include <esp32s3/rom/rtc.h>
#include <freertos_includes.h>   
#include "openlcb/SimpleStack.hxx"
#include "openlcb/TractionTrain.hxx"
#include "openlcb/TrainInterface.hxx"
#include <freertos_drivers/esp32/Esp32BootloaderHal.hxx>
#include <freertos_drivers/esp32/Esp32SocInfo.hxx>
#ifdef CONFIG_ESP32_WIFI_ENABLED
#include <freertos_drivers/esp32/Esp32WiFiManager.hxx>
#endif
#include <openlcb/MemoryConfigClient.hxx>
#include <openlcb/RefreshLoop.hxx>
#include <utils/constants.hxx>
#include <utils/format_utils.hxx>

#include "BootPauseHelper.hxx"
#include <freertos_drivers/esp32/Esp32Ledc.hxx>
#include "freertos_drivers/arduino/PWM.hxx"
#include "hardware.hxx"

#include "FunctionConfig.hxx"
#include "FunctionConsumer.hxx"

#include "ESP32S3Train.hxx"

OVERRIDE_CONST(num_memory_spaces, 6);
AtlasLightBoardWiFiLCCTraction::ConfigDef cfg(0);

namespace openlcb
{
    /// Name of CDI.xml to generate dynamically.
    const char CDI_FILENAME[] = "/fs/cdi.xml";

    // Path to where OpenMRN should persist general configuration data.
    const char *const CONFIG_FILENAME = "/fs/config";

    // The size of the memory space to export over the above device.
    const size_t CONFIG_FILE_SIZE =
        cfg.seg().size() + cfg.seg().offset();

    // Default to store the dynamic SNIP data is stored in the same persistant
    // data file as general configuration data.
    const char *const SNIP_DYNAMIC_FILENAME = "/fs/config";

    /// Defines the identification information for the node. The arguments are:
    ///
    /// - 4 (version info, always 4 by the standard
    /// - Manufacturer name
    /// - Model name
    /// - Hardware version
    /// - Software version
    ///
    /// This data will be used for all purposes of the identification:
    ///
    /// - the generated cdi.xml will include this data
    /// - the Simple Node Ident Info Protocol will return this data
    /// - the ACDI memory space will contain this data.
    const SimpleNodeStaticValues SNIP_STATIC_DATA =
    {
        4,
        SNIP_PROJECT_PAGE,
        SNIP_PROJECT_NAME,
        SNIP_HW_VERSION,
        SNIP_SW_VERSION
    };

} // namespace openlcb
extern "C"
{

void *node_reboot(void *arg)
{
    Singleton<reboothelpers::NodeRebootHelper>::instance()->reboot();
    return nullptr;
}

void reboot()
{
    os_thread_create(nullptr, nullptr, uxTaskPriorityGet(NULL) + 1, 2048
                   , node_reboot, nullptr);
}

ssize_t os_get_free_heap()
{
    return heap_caps_get_free_size(MALLOC_CAP_8BIT);
}

/// Verifies that the bootloader has been requested.
///
/// @return true (always).
///
/// NOTE: On the ESP32 this defaults to always return true since this code will
/// not be invoked through normal node startup.
bool request_bootloader(void)
{
    LOG(VERBOSE, "[Bootloader] request_bootloader");
    // Default to allow bootloader to run since we are not entering the
    // bootloader loop unless requested by app_main.
    return true;
}
/// Initializes the node specific bootloader hardware (LEDs)
void bootloader_hw_set_to_safe(void)
{
    LOG(VERBOSE, "[Bootloader] bootloader_hw_set_to_safe");
}

namespace AtlasLightBoardWiFiLCCTraction {

ConfigUpdateListener::UpdateAction FactoryResetHelper::apply_configuration(
    int fd, bool initial_load, BarrierNotifiable *done)
{
    // nothing to do here as we do not load config
    AutoNotify n(done);
    LOG(VERBOSE, "[CFG] apply_configuration(%d, %d)", fd, initial_load);
    if (!initial_load &&
        Singleton<nvsmanager::NvsManager>::instance()->CheckPersist())
    {
        LOG(WARNING, "[CFG] NVS has been updated requesting a restart.");
        return ConfigUpdateListener::UpdateAction::REBOOT_NEEDED;
    }

    return ConfigUpdateListener::UpdateAction::UPDATED;
}

void FactoryResetHelper::factory_reset(int fd)
{
    LOG(VERBOSE, "[CFG] factory_reset(%d)", fd);
    // set the name of the node to the SNIP model name
    cfg.userinfo().name().write(fd, openlcb::SNIP_STATIC_DATA.model_name);
    cfg.userinfo().description().write(fd, "");
    
}

}

void app_main()
{
    
    //bool stackrunning = false;
    // capture the reason for the CPU reset
    uint8_t reset_reason = Esp32SocInfo::print_soc_info();
    // If this is the first power up of the node we need to reset the flag
    // since it will not be initialized automatically.
    LOG(INFO, "[SNIP] version:%d, manufacturer:%s, model:%s, hw-v:%s, sw-v:%s"
      , openlcb::SNIP_STATIC_DATA.version
      , openlcb::SNIP_STATIC_DATA.manufacturer_name
      , openlcb::SNIP_STATIC_DATA.model_name
      , openlcb::SNIP_STATIC_DATA.hardware_version
      , openlcb::SNIP_STATIC_DATA.software_version);
    bool reset_events = false;
    bool cleanup_config_tree = false;
    GpioInit::hw_init();

    nvsmanager::NvsManager nvs;
    nvs.init(reset_reason);

    LOG(INFO, "[BootPauseHelper] starting...");
    
    nvsmanager::BootPauseHelper pause;
    
    pause.CheckPause();
    LOG(INFO, "[BootPauseHelper] returned...");
    if (BOOT_Pin::instance()->is_clr())
    {
        nvs.force_factory_reset();
    }
    
    // Check for and reset factory reset flag.
    if (nvs.should_reset_config())
    {
        cleanup_config_tree = true;
        nvs.clear_factory_reset();
    }

    if (nvs.should_reset_events())
    {
        reset_events = true;
        // reset the flag so we start in normal operating mode next time.
        nvs.clear_reset_events();
    }
    nvs.CheckPersist();

    nvs.DisplayNvsConfiguration();
    mount_fs(cleanup_config_tree);
    LOG(INFO, "[AtlasLightBoardWiFiLCCTraction] about to start the PhysicalTrainNode");
    
    ESP32S3Train trainImpl;
    openlcb::SimpleTrainCanStack stack(&trainImpl, ESP32_FDI, nvs.node_id());
    ESP32SpeedController esp32_speed_controller(stack.service(), cfg.seg().motor_control());
    
    LOG(INFO, "[AtlasLightBoardWiFiLCCTraction] stack started");
#if CONFIG_OLCB_PRINT_ALL_PACKETS
    stack.print_all_packets();
#endif
    nvs.register_virtual_memory_spaces(&stack);
    openlcb::MemoryConfigClient memory_client(stack.node(), stack.memory_config_handler());
    LOG(INFO, "[AtlasLightBoardWiFiLCCTraction] MemoryConfigClient done.");
#ifdef CONFIG_ESP32_WIFI_ENABLED
    openmrn_arduino::Esp32WiFiManager wifi_manager(
                                                   nvs.station_ssid(), 
                                                   nvs.station_pass(),
                                                   &stack, 
                                                   cfg.seg().olbcwifi(), 
                                                   nvs.wifi_mode(),
                                                   (uint8_t)CONFIG_OLCB_WIFI_MODE, /* uplink / hub mode */
                                                   nvs.hostname_prefix());
#endif
    AtlasLightBoardWiFiLCCTraction::FactoryResetHelper factory_reset_helper;
    LOG(INFO, "[AtlasLightBoardWiFiLCCTraction] FactoryResetHelper done.");
    reboothelpers::DelayRebootHelper delayed_reboot(stack.service());
    LOG(INFO, "[AtlasLightBoardWiFiLCCTraction] DelayRebootHelper done.");
    healthmonitor::HealthMonitor health_mon(stack.service());
    LOG(INFO, "[AtlasLightBoardWiFiLCCTraction] HealthMonitor done.");
    // Create config file and initiate factory reset if it doesn't exist or is
    // otherwise corrupted.
    int config_fd =
          stack.create_config_file_if_needed(cfg.seg().internal_config(),
                                             CDI_VERSION,
                                             openlcb::CONFIG_FILE_SIZE);
    stack.check_version_and_factory_reset(cfg.seg().internal_config(),
                                          CDI_VERSION,
                                          cleanup_config_tree);
    
    reboothelpers::NodeRebootHelper node_reboot_helper(&stack, config_fd);
    
    if (reset_events)
    {
        LOG(WARNING, "[CDI] Resetting event IDs");
        stack.factory_reset_all_events(
                                       cfg.seg().internal_config(), nvs.node_id(), config_fd);
        fsync(config_fd);
    }
        
        
    // if a brownout was detected send an event as part of node startup.
    if (reset_reason == RTCWDT_BROWN_OUT_RESET)
    {
        //event_helper.send_event(openlcb::Defs::NODE_POWER_BROWNOUT_EVENT);
    }
        
    // Start the stack in the background using it's own task.
    stack.loop_executor();
    //stackrunning = true;
    
    // At this point the OpenMRN stack is running in it's own task and we can
    // safely exit from this one. We do not need to cleanup as that will be
    // handled automatically by ESP-IDF.
    //if (!stackrunning) {
    //    reboot();
    //}
}


} // extern "C"
    


