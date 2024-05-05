// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 17 10:16:07 2024
//  Last Modified : <240505.1335>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
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
/// @file esp32textdisplay.cpp
/// @author Robert Heller
/// @date Wed Apr 17 10:16:07 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////


/** @mainpage Introduction 
 * This board controls one or two small TFT displays that is being used as 
 * modern digital retail displays, commonly used by gas (filling) stations, 
 * but might also be used by movie theaters, shopping malls, or other retail 
 * establishments.  The displays can display a store logo, fuel (or other 
 * product) prices, along with other information.  LCC events can turn the 
 * whole display on or off, or to select one of four short messages.  The 
 * display can also display the time of day, using the Broadcast Time 
 * Protocol (either real time or fast clock).
 */

static const char rcsid[] = "@(#) : $Id$";

#include "sdkconfig.h"
#include "cdi.hxx" 
#include "cdidata.hxx"
#include "DelayRebootHelper.hxx"
#include "FactoryResetHelper.hxx"
#include "HealthMonitor.hxx"
#include "fs.hxx"
#include "hardware.hxx"
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
#include <openlcb/SimpleStack.hxx>
#include <freertos_drivers/esp32/Esp32HardwareTwai.hxx>
#include <freertos_drivers/esp32/Esp32BootloaderHal.hxx>
#include <freertos_drivers/esp32/Esp32SocInfo.hxx>
#ifdef CONFIG_ESP32_WIFI_ENABLED
#include <freertos_drivers/esp32/Esp32WiFiManager.hxx>
#endif
#include <openlcb/MemoryConfigClient.hxx>
#include <openlcb/RefreshLoop.hxx>
#include <openlcb/SimpleStack.hxx>
#include <utils/constants.hxx>
#include <utils/format_utils.hxx>

#include "BootPauseHelper.hxx"
#include <freertos_drivers/esp32/Esp32Ledc.hxx>
#include "freertos_drivers/arduino/PWM.hxx"
#include "hardware.hxx"
#include "Esp32SPI.hxx"
#include "Adafruit_ST7735.h"

#include "RetailDisplayConfig.hxx"
#include "RetailDisplay.hxx"

///////////////////////////////////////////////////////////////////////////////
// Increase the CAN RX frame buffer size to reduce overruns when there is high
// traffic load (ie: large datagram transport).
///////////////////////////////////////////////////////////////////////////////
OVERRIDE_CONST(can_rx_buffer_size, 64);
OVERRIDE_CONST(num_memory_spaces, 6);

esp32textdisplay::ConfigDef cfg(0);
Esp32HardwareTwai twai(CONFIG_TWAI_RX_PIN, CONFIG_TWAI_TX_PIN);
Esp32SPI spibus;
Adafruit_ST7735 display1(CONFIG_DCS1,DRs_Pin::instance(),DReset_Pin::instance());
#ifdef CONFIG_TWO_DISPLAY_PANELS
Adafruit_ST7735 display2(CONFIG_DCS2,DRs_Pin::instance(),nullptr);
#endif

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

/// Halts execution with a specific blink pattern for the two LEDs that are on
/// the IO base board.
///
/// @param activity1 Sets the initial state of the Activity1 (Green) LED.
/// @param activity2 Sets the initial state of the Activity2 (Red)   LED.
/// @param period Sets the delay between blinking the LED(s).
/// @param toggle_both Controls if both LEDs will blink or if only the activity
/// LED will blink.
void die_with(bool activity1, bool activity2, unsigned period = 1000
            , bool toggle_both = false)
{
    LED_ACT1_Pin::set(activity1);
    LED_ACT2_Pin::set(activity2);

    while(true)
    {
        if (toggle_both)
        {
            LED_ACT1_Pin::toggle();
        }
        LED_ACT2_Pin::toggle();
        usleep(period);
    }
}

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



/// Updates the state of a status LED.
///
/// @param led is the LED to update.
/// @param value is the new state of the LED.
///
/// NOTE: Currently the following mapping is being used for the LEDs:
/// LED_ACTIVE -> Bootloader LED
/// LED_WRITING -> Bootloader Write LED
/// LED_REQUEST -> Used only as a hook for printing bootloader startup.
void bootloader_led(enum BootloaderLed led, bool value)
{
    LOG(VERBOSE, "[Bootloader] bootloader_led(%d, %d)", led, value);
    if (led == LED_ACTIVE)
    {
        LED_ACT1_Pin::instance()->write(value);
    }
    else if (led == LED_WRITING)
    {
        LED_ACT2_Pin::instance()->write(value);
    }
    else if (led == LED_REQUEST)
    {
        //LOG(INFO, "[Bootloader] Preparing to receive firmware");
        //LOG(INFO, "[Bootloader] Current partition: %s", current->label);
        //LOG(INFO, "[Bootloader] Target partition: %s", target->label);
    }
}

/// Initializes the node specific bootloader hardware (LEDs)
void bootloader_hw_set_to_safe(void)
{
    LOG(VERBOSE, "[Bootloader] bootloader_hw_set_to_safe");
    LED_ACT1_Pin::hw_init();
    LED_ACT2_Pin::hw_init();
}

namespace esp32textdisplay {

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

openmrn_arduino::Esp32Ledc ledc(BacklightPin);
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
    bool run_bootloader = false;
    bool cleanup_config_tree = false;
    GpioInit::hw_init();
    spibus.hw_initbus(CONFIG_MOSI,CONFIG_MISO,CONFIG_SCLK);
    display1.initR(&spibus,INITR_BLACKTAB);
#ifdef CONFIG_TWO_DISPLAY_PANELS
    display2.initR(&spibus,INITR_BLACKTAB);
#endif
    spibus.mount_sd_card("/sdcard",CONFIG_CardCS);

    nvsmanager::NvsManager nvs;
    nvs.init(reset_reason);

    // Ensure the LEDs are both ON for PauseCheck
    LED_ACT1_Pin::instance()->set();
    LED_ACT2_Pin::instance()->set();
    
    LOG(INFO, "[BootPauseHelper] starting...");
    
    nvsmanager::BootPauseHelper pause;
    
    pause.CheckPause();
    LOG(INFO, "[BootPauseHelper] returned...");
    if (BOOT_Pin::instance()->is_clr())
    {
        nvs.force_factory_reset();
    }
    
    // Ensure the LEDs are both OFF when we startup.
    LED_ACT1_Pin::instance()->clr();
    LED_ACT2_Pin::instance()->clr();
    
    // Check for and reset factory reset flag.
    if (nvs.should_reset_config())
    {
        cleanup_config_tree = true;
        nvs.clear_factory_reset();
    }

    if (nvs.should_start_bootloader())
    {
        run_bootloader = true;
        // reset the flag so we start in normal operating mode next time.
        nvs.clear_bootloader();
    }
    
    if (nvs.should_reset_events())
    {
        reset_events = true;
        // reset the flag so we start in normal operating mode next time.
        nvs.clear_reset_events();
    }
    nvs.CheckPersist();

    if (run_bootloader)
    {
        LOG(VERBOSE, "[Bootloader] bootloader_hw_set_to_safe");
        LED_ACT1_Pin::hw_init();
        LED_ACT2_Pin::hw_init();
        esp32_bootloader_run(nvs.node_id(), CONFIG_TWAI_TX_PIN, CONFIG_TWAI_RX_PIN, true);
        esp_restart();
    }
    else
    {
        nvs.DisplayNvsConfiguration();
        mount_fs(cleanup_config_tree);
        LOG(INFO, "[esp32textdisplay] about to start the Simple Can Stack");
        openlcb::SimpleCanStack stack(nvs.node_id());
        LOG(INFO, "[esp32textdisplay] stack started");
        stack.set_tx_activity_led(LED_ACT1_Pin::instance());
        LOG(INFO, "[esp32textdisplay] set activity led");
#if CONFIG_OLCB_PRINT_ALL_PACKETS
        stack.print_all_packets();
#endif
        nvs.register_virtual_memory_spaces(&stack);
        openlcb::MemoryConfigClient memory_client(stack.node(), stack.memory_config_handler());
        LOG(INFO, "[esp32textdisplay] MemoryConfigClient done.");
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
        esp32textdisplay::FactoryResetHelper factory_reset_helper;
        LOG(INFO, "[esp32textdisplay] FactoryResetHelper done.");
        reboothelpers::DelayRebootHelper delayed_reboot(stack.service());
        LOG(INFO, "[esp32textdisplay] DelayRebootHelper done.");
        healthmonitor::HealthMonitor health_mon(stack.service());
        LOG(INFO, "[esp32textdisplay] HealthMonitor done.");
#ifdef CONFIG_FAST_CLOCK
        openlcb::BroadcastTimeClient timeClient(stack.node(),
                           openlcb::BroadcastTimeDefs::DEFAULT_FAST_CLOCK_ID);
#else
        openlcb::BroadcastTimeClient timeClient(stack.node(),
                        openlcb::BroadcastTimeDefs::DEFAULT_REALTIME_CLOCK_ID);
#endif
        ledc.hw_init();
        RetailDisplay sign1(stack.node(), cfg.seg().display1(), 
                            &display1, &timeClient, ledc.get_channel(0));
        LOG(INFO, "[esp32textdisplay] Sign1 done.");
#ifdef CONFIG_TWO_DISPLAY_PANELS
        RetailDisplay sign2(stack.node(), cfg.seg().display2(),
                            &display2, &timeClient);
        LOG(INFO, "[esp32textdisplay] Sign2 done.");
#endif
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
        
        
        // Initialize the TWAI driver.
        twai.hw_init();
        
        // Add the TWAI port to the stack.
        stack.add_can_port_select("/dev/twai/twai0");
        
        // if a brownout was detected send an event as part of node startup.
        if (reset_reason == RTCWDT_BROWN_OUT_RESET)
        {
            //event_helper.send_event(openlcb::Defs::NODE_POWER_BROWNOUT_EVENT);
        }
        
        // Start the stack in the background using it's own task.
        stack.loop_executor();
        //stackrunning = true;
    }
    // At this point the OpenMRN stack is running in it's own task and we can
    // safely exit from this one. We do not need to cleanup as that will be
    // handled automatically by ESP-IDF.
    //if (!stackrunning) {
    //    reboot();
    //}
}


} // extern "C"
    

