// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Oct 20 11:48:50 2026
//  Last Modified : <261021.1635>
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

#include "sdkconfig.h"
#include "cdi.hxx"
#ifdef CONFIG_LOWRESCROSSING
#ifdef CONFIG_RIR4ADDRESS2
#define SW_MODE "LR2RIR4"
#else
#define SW_MODE "LR1RIR4"
#endif
#elif defined(CONFIG_STANDARDRESCROSSING)
#ifdef CONFIG_RIR4ADDRESS2
#define SW_MODE "SR2RIR4"
#else
#define SW_MODE "SR1RIR4"
#endif
#else
#ifdef CONFIG_RIR4ADDRESS2
#define SW_MODE "RD2RIR4"
#else
#define SW_MODE "RD1RIR4"
#endif
#endif

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
#include <esp_err.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_task_wdt.h>
#include <freertos_includes.h>
#include <openlcb/SimpleStack.hxx>
#include <freertos_drivers/esp32/Esp32HardwareTwai.hxx>
#include <freertos_drivers/esp32/Esp32BootloaderHal.hxx>
#include <freertos_drivers/esp32/Esp32SocInfo.hxx>
#include <freertos_drivers/esp32/Esp32Ledc.hxx>
#include <openlcb/MemoryConfigClient.hxx>
#include <openlcb/RefreshLoop.hxx>
#include <openlcb/SimpleStack.hxx>
#include <utils/constants.hxx>
#include <utils/format_utils.hxx>
#include "BootPauseHelper.hxx"
#include "hardware.hxx"
#include "freertos_drivers/esp32/Esp32HardwareI2C.hxx"
#include "Azatrax.hxx"
#include "Blink.hxx"
#include "BlinkingConsumerConfig.hxx"
#include "BlinkingConsumer.hxx"
#include "openlcb/ServoConsumerConfig.hxx"
#include "openlcb/ServoConsumer.hxx"
#include "StallConsumerConfig.hxx"
#include "StallConsumer.hxx"
#include "SSRConsumerConfig.hxx"
#include "SSRConsumer.hxx"
#include "WiFiManager.hxx"

#if defined(CONFIG_LOWRESCROSSING) || defined(CONFIG_STANDARDRESCROSSING)
#include "AzatraxRIR4CrossingConfig.hxx"
#include "AzatraxRIR4Crossing.hxx"
#if defined(CONFIG_LOWRESCROSSING) && defined(CONFIG_RIR4ADDRESS2)
#include "AzatraxRIR4PCConfig.hxx"
#include "AzatraxRIR4PC.hxx"
#endif
#else
#include "AzatraxRIR4PCConfig.hxx"
#include "AzatraxRIR4PC.hxx"
#endif

///////////////////////////////////////////////////////////////////////////////
// Increase the CAN RX frame buffer size to reduce overruns when there is high
// traffic load (ie: large datagram transport).
///////////////////////////////////////////////////////////////////////////////
OVERRIDE_CONST(can_rx_buffer_size, 64);
OVERRIDE_CONST(num_memory_spaces, 6);

AdafruitMetroESP32::ConfigDef cfg(0);
Esp32HardwareTwai twai(CONFIG_TWAI_RX_PIN, CONFIG_TWAI_TX_PIN);

Esp32HardwareI2C i2c("/dev/i2c");
azatrax::Azatrax rir4(CONFIG_RIR4ADDRESS);
#ifdef RIR4ADDRESS2
azatrax::Azatrax rir4_2(CONFIG_RIR4ADDRESS2);
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
        SNIP_HW_VERSION CONFIG_IDF_TARGET,
        SNIP_SW_VERSION SW_MODE
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



namespace AdafruitMetroESP32 {

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
    for (int i=0; i < NUM_DETECTORS; i++)
    {
        cfg.seg().azatraxrir4().detectors().entry(i).description().write(fd,"");
        CDI_FACTORY_RESET(cfg.seg().azatraxrir4().detectors().entry(i).threshold);
#ifdef RIR4ADDRESS2
        cfg.seg().azatraxrir4_2().detectors().entry(i).description().write(fd,"");
        CDI_FACTORY_RESET(cfg.seg().azatraxrir4_2().detectors().entry(i).threshold);
#endif
    }
    for (int i=0; i < NUM_STOPWATCH; i++)
    {
        cfg.seg().azatraxrir4().stopwatches().entry(i).description().write(fd,"");
#ifdef RIR4ADDRESS2
        cfg.seg().azatraxrir4_2().stopwatches().entry(i).description().write(fd,"");
#endif
    }
}

}

openmrn_arduino::Esp32Ledc ledc(SERVOPINS);


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
    i2c.hw_init(CONFIG_SDA_PIN,CONFIG_SCL_PIN,400000,I2C_NUM_0);
    
    rir4.begin("/dev/i2c0");
#ifdef CONFIG_RIR4ADDRESS2
    rir4_2.begin("/dev/i2c0");
#endif
    
    nvsmanager::NvsManager nvs;
    nvs.init(reset_reason);

    // Ensure the LEDs are both ON for PauseCheck
    LED_ACT1_Pin::instance()->set();
    LED_ACT2_Pin::instance()->set();
    
    LOG(INFO, "[BootPauseHelper] starting...");
    
    nvsmanager::BootPauseHelper pause;
    
    pause.CheckPause();
    LOG(INFO, "[BootPauseHelper] returned...");
    
    // Check for and reset factory reset flag.
    if (nvs.should_reset_config())
    {
        cleanup_config_tree = true;
        nvs.clear_factory_reset();
    }

    // Ensure the LEDs are both OFF when we startup.
    LED_ACT1_Pin::instance()->clr();
    LED_ACT2_Pin::instance()->clr();
    
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
        LOG(INFO, "[AdafruitMetroESP32] about to start the Simple Can Stack");
        openlcb::SimpleCanStack stack(nvs.node_id());
        LOG(INFO, "[AdafruitMetroESP32] stack started");
#if CONFIG_OLCB_PRINT_ALL_PACKETS
        stack.print_all_packets();
#endif
        nvs.register_virtual_memory_spaces(&stack);
        openlcb::MemoryConfigClient memory_client(stack.node(), stack.memory_config_handler());
        LOG(INFO, "[AdafruitMetroESP32] MemoryConfigClient done.");
        AdafruitMetroESP32::FactoryResetHelper factory_reset_helper;
        LOG(INFO, "[AdafruitMetroESP32] FactoryResetHelper done.");
        reboothelpers::DelayRebootHelper delayed_reboot(stack.service());
        LOG(INFO, "[AdafruitMetroESP32] DelayRebootHelper done.");
        healthmonitor::HealthMonitor health_mon(stack.service());
        LOG(INFO, "[AdafruitMetroESP32] HealthMonitor done.");
        WiFiManager wifi_manager(nvs.station_ssid(),
                                 nvs.station_pass(),
                                 &stack, 
                                 cfg.seg().uplinkParams(),
                                 nvs.hostname_prefix(),
                                 nvs.wifi_mode() != 0);
        BlinkTimer blinker(stack.executor()->active_timers());
        LOG(INFO, "[AdafruitMetroESP32] BlinkTimer done.");
#ifdef CONFIG_LOWRESCROSSING
        AzatraxRIR4Crossing crossing(stack.node(),cfg.seg().azatraxrir4crossing(),
                                     &rir4,true);
        openlcb::RefreshLoop crossingloop(stack.node(), {(openlcb::Polling*)&crossing});
        LOG(VERBOSE,"[AdafruitMetroESP32] crossing (LOWRESCROSSING) initialized.");
#ifdef CONFIG_RIR4ADDRESS2
        AzatraxRIR4 shield2(stack.node(),cfg.seg().azatraxrir4_2(),&rir4_2);
        openlcb::RefreshLoop shieldloop(stack.node(), {(openlcb::Polling*)&shield});
        LOG(VERBOSE,"[AdafruitMetroESP32] shield2 initialized.");
#endif
#elif defined(CONFIG_STANDARDRESCROSSING)
#ifdef CONFIG_RIR4ADDRESS2
        AzatraxRIR4Crossing crossing(stack.node(),cfg.seg().azatraxrir4crossing(),
                                 &rir4,&rir4_2);
        openlcb::RefreshLoop crossingloop(stack.node(), {(openlcb::Polling*)&crossing});
        LOG(VERBOSE,"[AdafruitMetroESP32] crossing (STANDARDRESCROSSING, 2 shields) initialized.");
#else
        AzatraxRIR4 shield(stack.node(),cfg.seg().azatraxrir4(),&rir4);
        openlcb::RefreshLoop shieldloop(stack.node(), {(openlcb::Polling*)&shield});
        LOG(VERBOSE,"[AdafruitMetroESP32] shield initialized.");
#endif
#ifdef CONFIG_RIR4ADDRESS2
        AzatraxRIR4 shield2(stack.node(),cfg.seg().azatraxrir4_2(),&rir4_2);
        openlcb::RefreshLoop shield2loop(stack.node(), {(openlcb::Polling*)&shield2});
        LOG(VERBOSE,"[AdafruitMetroESP32] shield2 initialized.");
#endif
#endif        
        BlinkingConsumer signal1(stack.node(), cfg.seg().signals().entry<0>(),SIG1_Pin());
        BlinkingConsumer signal2(stack.node(), cfg.seg().signals().entry<1>(),SIG2_Pin());
        BlinkingConsumer signal3(stack.node(), cfg.seg().signals().entry<2>(),SIG3_Pin());
        BlinkingConsumer signal4(stack.node(), cfg.seg().signals().entry<3>(),SIG4_Pin());
        LOG(VERBOSE,"[AdafruitMetroESP32] signal1, signal2, signal3, signal4 initialized.");
        openlcb::ServoConsumer srv0(stack.node(), cfg.seg().servos().entry<0>(),1000, ledc.get_channel(0));
        openlcb::ServoConsumer srv1(stack.node(), cfg.seg().servos().entry<1>(),1000, ledc.get_channel(1));
        openlcb::ServoConsumer srv2(stack.node(), cfg.seg().servos().entry<2>(),1000, ledc.get_channel(2));
        openlcb::ServoConsumer srv3(stack.node(), cfg.seg().servos().entry<3>(),1000, ledc.get_channel(3));
        LOG(VERBOSE,"[AdafruitMetroESP32] srv0, srv1, srv2, srv3 initialized.");
        StallConsumer stall1(stack.node(), cfg.seg().stallmotors().entry<0>(),StallM_Pin());                            
        StallConsumer stall2(stack.node(), cfg.seg().stallmotors().entry<1>(),StallN_Pin());
        LOG(VERBOSE,"[AdafruitMetroESP32] stall1 and stall2 initialized.");
        SSRConsumer ssr1(stack.node(), cfg.seg().ssrs().entry<0>(),SSR1_Pin());
        SSRConsumer ssr2(stack.node(), cfg.seg().ssrs().entry<1>(),SSR2_Pin());
        LOG(VERBOSE,"[AdafruitMetroESP32] ssr1 and ssr2 initialized."); 
        
        blinker.start(500000000);
        LOG(VERBOSE,"[AdafruitMetroESP32] blinker started.");
        
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
    

