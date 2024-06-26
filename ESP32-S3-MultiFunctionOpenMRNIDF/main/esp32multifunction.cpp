// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Thu Jun 23 12:17:40 2022
//  Last Modified : <230805.2126>
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
/// @file esp32multifunction.cpp
/// @author Robert Heller 
/// @date Thu Jun 23 12:17:40 2022
//////////////////////////////////////////////////////////////////////////////

/** @mainpage Introduction
 * 
 * This is the firmware for various ESP32S3-based "MultiFunction" LCC Node 
 * boards.
 * Boards this software will work for include:
 * 
 * - ESP32-S3-MultiFunction original S3-MultiFunction board using a "bare"
 *   ESP32-S3FN8 chip.
 * - ESP32-T7S3-MultiFunction A version of the original S3-MultiFunction board
 *   using a TTGO-T7S3 module.
 * - ESP32-T7S3-MultiFunctionUniversalTurnout A version of the 
 *   T7S3-MultiFunction board using a daughter board for the turnout driver
 *   allowing four different turnout types (Stall Motor, Single Coil, 
 *   Twin Coil, and Servo).
 * - This code will also work on a breadboard version using a ESP32S3 DevKit 
 *   board.
 * 
 * There are configuration options to adjust how the code is compiled for 
 * different hardware options.
 * 
 * 
 * 
 */

static const char rcsid[] = "@(#) : $Id$";

#include "sdkconfig.h"
#include "cdi.hxx"
#if defined(CONFIG_T7S3)
#define TARGETMOD "T7S3"
#elif defined(CONFIG_DEVKIT_BREADBOARD)
#define TARGETMOD "DEVKIT_BREADBOARD"
#else
#define TARGETMOD "BARES3"
#endif
#if defined(CONFIG_SERVO_TURNOUTS)
#define TARGETDAUGHTER " SERVOS"
#else
#define TARGETDAUGHTER ""
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
#include "Lamp.hxx"
#include "Mast.hxx"
#include "Blink.hxx"
#include "TrackCircuit.hxx"
#include "Logic.hxx"
#if defined(CONFIG_SERVO_TURNOUTS)
#include <freertos_drivers/esp32/Esp32Ledc.hxx>
#include "ServoTurnoutConfig.hxx"
#include "ServoTurnout.hxx"
#else
#include "Turnout.hxx"
#endif
#include "Points.hxx"
#include "OccupancyDetector.hxx"
#include "Button.hxx"
#include "LED.hxx"
#include "hardware.hxx"
#include "freertos_drivers/esp32/Esp32HardwareI2C.hxx"
#include "freertos_drivers/arduino/PWM.hxx"
#include "PCA9685PWM.hxx"
#include "SignalLampTester.hxx"


///////////////////////////////////////////////////////////////////////////////
// Increase the CAN RX frame buffer size to reduce overruns when there is high
// traffic load (ie: large datagram transport).
///////////////////////////////////////////////////////////////////////////////
OVERRIDE_CONST(can_rx_buffer_size, 64);
OVERRIDE_CONST(num_memory_spaces, 6);

TrackCircuit *circuits[TRACKCIRCUITCOUNT];

esp32multifunction::ConfigDef cfg(0);
Esp32HardwareTwai twai(CONFIG_TWAI_RX_PIN, CONFIG_TWAI_TX_PIN);
Esp32HardwareI2C i2c("/dev/i2c");


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

DEFINE_SINGLETON_INSTANCE(BlinkTimer);
PWM* Lamp::pinlookup_[17];
PCA9685PWM pwmchip1;
PCA9685PWMBit LampA0(&pwmchip1,0);
PCA9685PWMBit LampA1(&pwmchip1,1);
PCA9685PWMBit LampA2(&pwmchip1,2);
PCA9685PWMBit LampA3(&pwmchip1,3);
PCA9685PWMBit LampA4(&pwmchip1,4);
PCA9685PWMBit LampA5(&pwmchip1,5);
PCA9685PWMBit LampA6(&pwmchip1,6);
PCA9685PWMBit LampA7(&pwmchip1,7);

PCA9685PWMBit LampB0(&pwmchip1,8);
PCA9685PWMBit LampB1(&pwmchip1,9);
PCA9685PWMBit LampB2(&pwmchip1,10);
PCA9685PWMBit LampB3(&pwmchip1,11);
PCA9685PWMBit LampB4(&pwmchip1,12);
PCA9685PWMBit LampB5(&pwmchip1,13);
PCA9685PWMBit LampB6(&pwmchip1,14);
PCA9685PWMBit LampB7(&pwmchip1,15);


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

namespace esp32multifunction {

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
    
    for(int i = 0; i < NUM_OCS; i++)
    {
        cfg.seg().ocs().entry(i).description().write(fd, "");
        CDI_FACTORY_RESET(cfg.seg().ocs().entry(i).debounce);
    }
    for(int i = 0; i < NUM_TURNOUTS; i++)
    {
        cfg.seg().turnouts().entry(i).description().write(fd, "");
#if defined(CONFIG_SERVO_TURNOUTS)
        CDI_FACTORY_RESET(cfg.seg().turnouts().entry(i).servo_normal_percent);
        CDI_FACTORY_RESET(cfg.seg().turnouts().entry(i).servo_reversed_percent);
#endif
    }
    for(int i = 0; i < NUM_POINTSS; i++)
    {
        cfg.seg().points().entry(i).description().write(fd, "");
    }
    for(int i = 0; i < NUM_BUTTONS; i++)
    {
        cfg.seg().buttons().entry(i).description().write(fd, "");
    }
    for(int i = 0; i < NUM_LEDS; i++)
    {
        CDI_FACTORY_RESET(cfg.seg().leds().entry(i).phase);
        CDI_FACTORY_RESET(cfg.seg().leds().entry(i).pulsewidth);
    }
    
#if 1
    for(int i = 0; i < LOGICCOUNT; i++)
    {
        cfg.seg().logics().entry(i).description().write(fd, "");
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).groupFunction);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).logic().logicFunction);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).trueAction);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).falseAction);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).timing().timedelay);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).timing().interval);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).timing().retriggerable);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).v1().trigger);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).v1().source);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).v1().trackspeed);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).v2().trigger);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).v2().source);
        CDI_FACTORY_RESET(cfg.seg().logics().entry(i).v2().trackspeed);
        for (int j = 0; j < 4 ; j++)
        {
            CDI_FACTORY_RESET(cfg.seg().logics().entry(i).actions().entry(j).actiontrigger);
        }
    }
    for(int i = 0; i < MASTCOUNT; i++)
    {
        CDI_FACTORY_RESET(cfg.seg().masts().entry(i).processing);
        cfg.seg().masts().entry(i).mastid().write(fd,"");
#ifdef HAVEPWM
        CDI_FACTORY_RESET(cfg.seg().masts().entry(i).fade);
#endif
        for (int j = 0; j < RULESCOUNT; j++)
        {
            CDI_FACTORY_RESET(cfg.seg().masts().entry(i).rules().entry(j).name);
            CDI_FACTORY_RESET(cfg.seg().masts().entry(i).rules().entry(j).speed);
            for (int k = 0; k < LAMPCOUNT; k++)
            {
                CDI_FACTORY_RESET(cfg.seg().masts().entry(i).rules().entry(j).lamps().entry(k).selection);
                CDI_FACTORY_RESET(cfg.seg().masts().entry(i).rules().entry(j).lamps().entry(k).phase);
                CDI_FACTORY_RESET(cfg.seg().masts().entry(i).rules().entry(j).lamps().entry(k).brightness);
                CDI_FACTORY_RESET(cfg.seg().masts().entry(i).rules().entry(j).lamps().entry(k).period);
            }
        }
    }
    for(int i = 0; i < TRACKCIRCUITCOUNT; i++)
    {
        cfg.seg().circuits().entry(i).description().write(fd,"");
    }
#endif
}

}

#if defined(CONFIG_SERVO_TURNOUTS)
openmrn_arduino::Esp32Ledc ledc(TURNOUTSERVOPINS);
#endif

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
    bool test_signal_lamps = false;
    GpioInit::hw_init();

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
    if (nvs.should_test_signal_lamps())
    {
        test_signal_lamps = true;
        nvs.clear_test_signal_lamps();
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
        LOG(INFO, "[esp32multifunction] about to start the Simple Can Stack");
        openlcb::SimpleCanStack stack(nvs.node_id());
        LOG(INFO, "[esp32multifunction] stack started");
        stack.set_tx_activity_led(LED_ACT1_Pin::instance());
        LOG(INFO, "[esp32multifunction] set activity led");
#if CONFIG_OLCB_PRINT_ALL_PACKETS
        stack.print_all_packets();
#endif
        nvs.register_virtual_memory_spaces(&stack);
        openlcb::MemoryConfigClient memory_client(stack.node(), stack.memory_config_handler());
        LOG(INFO, "[esp32multifunction] MemoryConfigClient done.");
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
        esp32multifunction::FactoryResetHelper factory_reset_helper;
        LOG(INFO, "[esp32multifunction] FactoryResetHelper done.");
        reboothelpers::DelayRebootHelper delayed_reboot(stack.service());
        LOG(INFO, "[esp32multifunction] DelayRebootHelper done.");
        healthmonitor::HealthMonitor health_mon(stack.service());
        LOG(INFO, "[esp32multifunction] HealthMonitor done.");
        BlinkTimer blinker(stack.executor()->active_timers());
        blinker.start(500000000);
        LOG(INFO, "[esp32multifunction] BlinkTimer done.");
        
        int i = 0;
        Mast *masts[MASTCOUNT];
        Mast *prevMast = nullptr;
        for (i = 0; i < MASTCOUNT; i++) {
            masts[i] = new Mast(stack.node(),cfg.seg().masts().entry(i),prevMast);
            prevMast = masts[i];
        }
        LOG(INFO, "[esp32multifunction] Masts  done.");
        for (i = 0; i < TRACKCIRCUITCOUNT; i++) {
            circuits[i] = new TrackCircuit(stack.node(),cfg.seg().circuits().entry(i));
        }
        LOG(INFO, "[esp32multifunction] TrackCircuits  done.");
        Logic *prevLogic = nullptr;
        Logic *logics[LOGICCOUNT];
        for (i = LOGICCOUNT-1; i >= 0; i--) {
            logics[i] = new Logic(stack.node(), cfg.seg().logics().entry(i),stack.executor()->active_timers(),prevLogic);
            prevLogic = logics[i];
        }
        LOG(INFO, "[esp32multifunction] Logics done.");
#if defined(CONFIG_SERVO_TURNOUTS)
        ledc.hw_init();
        ServoTurnout turnout1(stack.node(), cfg.seg().turnouts().entry<0>(),1000,ledc.get_channel(0));
        ServoTurnout turnout2(stack.node(), cfg.seg().turnouts().entry<1>(),1000,ledc.get_channel(1));
        ServoTurnout turnout3(stack.node(), cfg.seg().turnouts().entry<2>(),1000,ledc.get_channel(2));
        ServoTurnout turnout4(stack.node(), cfg.seg().turnouts().entry<3>(),1000,ledc.get_channel(3));
#else
        Turnout turnout1(stack.node(), cfg.seg().turnouts().entry<0>(),Motor1_Pin());
        Turnout turnout2(stack.node(), cfg.seg().turnouts().entry<1>(),Motor2_Pin());
        Turnout turnout3(stack.node(), cfg.seg().turnouts().entry<2>(),Motor3_Pin());
        Turnout turnout4(stack.node(), cfg.seg().turnouts().entry<3>(),Motor4_Pin());
#endif
        LOG(INFO, "[esp32multifunction] Turnouts done.");
        Points points1(stack.node(), cfg.seg().points().entry<0>(),Points1_Pin());
        Points points2(stack.node(), cfg.seg().points().entry<1>(),Points2_Pin());
        Points points3(stack.node(), cfg.seg().points().entry<2>(),Points3_Pin());
        Points points4(stack.node(), cfg.seg().points().entry<3>(),Points4_Pin());
        LOG(INFO, "[esp32multifunction] Points done.");
        OccupancyDetector od1(stack.node(), cfg.seg().ocs().entry<0>(),OD1_Pin());
        OccupancyDetector od2(stack.node(), cfg.seg().ocs().entry<1>(),OD2_Pin());
        OccupancyDetector od3(stack.node(), cfg.seg().ocs().entry<2>(),OD3_Pin());
        OccupancyDetector od4(stack.node(), cfg.seg().ocs().entry<3>(),OD4_Pin());
        LOG(INFO, "[esp32multifunction] OccupancyDetector done."); 
        Button button1(stack.node(), cfg.seg().buttons().entry<0>(),Button1_Pin());
        Button button2(stack.node(), cfg.seg().buttons().entry<1>(),Button2_Pin());
        Button button3(stack.node(), cfg.seg().buttons().entry<2>(),Button3_Pin());
        Button button4(stack.node(), cfg.seg().buttons().entry<3>(),Button4_Pin());
        LOG(INFO, "[esp32multifunction] Buttons done.");
        LED Led1(stack.node(), cfg.seg().leds().entry<0>(),LED1_Pin());
        LED Led2(stack.node(), cfg.seg().leds().entry<1>(),LED2_Pin());
        LED Led3(stack.node(), cfg.seg().leds().entry<2>(),LED3_Pin());
        LED Led4(stack.node(), cfg.seg().leds().entry<3>(),LED4_Pin());
        LOG(INFO, "[esp32multifunction] LEDs done.");
        openlcb::RefreshLoop points_refresh_loop(stack.node(),{
                                                 points1.polling()
                                                 , points2.polling()
                                                 , points3.polling()
                                                 , points4.polling()
                                                 , od1.polling()
                                                 , od2.polling()
                                                 , od3.polling()
                                                 , od4.polling()
                                                 , button1.polling()
                                                 , button2.polling()
                                                 , button3.polling()
                                                 , button4.polling()
                                             });
        LOG(INFO, "[esp32multifunction] RefreshLoop done.");
        i2c.hw_init(CONFIG_SDA_PIN,CONFIG_SCL_PIN,400000,I2C_NUM_0);
        i2c.scan(I2C_NUM_0);

        pwmchip1.init("/dev/i2c/i2c0",PWMCHIP_ADDRESS1);
        LOG(INFO, "[esp32multifunction] Lamps done.");
        esp32multifunction::SignalLampTester tester;
        if (test_signal_lamps)
        {
            tester.testLamps(
                         {&LampA0,&LampA1,&LampA2,&LampA3,
                             &LampA4,&LampA5,&LampA6,&LampA7,
                             &LampB0,&LampB1,&LampB2,&LampB3,
                             &LampB4,&LampB5,&LampB6,&LampB7});
        }
        
        Lamp::PinLookupInit(0,nullptr);
        
        Lamp::PinLookupInit(Lamp::A0_,&LampA0);
        Lamp::PinLookupInit(Lamp::A1_,&LampA1);
        Lamp::PinLookupInit(Lamp::A2_,&LampA2);
        Lamp::PinLookupInit(Lamp::A3_,&LampA3);
        Lamp::PinLookupInit(Lamp::A4_,&LampA4);
        Lamp::PinLookupInit(Lamp::A5_,&LampA5);
        Lamp::PinLookupInit(Lamp::A6_,&LampA6);
        Lamp::PinLookupInit(Lamp::A7_,&LampA7);
        
        Lamp::PinLookupInit(Lamp::B0_,&LampB0);
        Lamp::PinLookupInit(Lamp::B1_,&LampB1);
        Lamp::PinLookupInit(Lamp::B2_,&LampB2);
        Lamp::PinLookupInit(Lamp::B3_,&LampB3);
        Lamp::PinLookupInit(Lamp::B4_,&LampB4);
        Lamp::PinLookupInit(Lamp::B5_,&LampB5);
        Lamp::PinLookupInit(Lamp::B6_,&LampB6);
        Lamp::PinLookupInit(Lamp::B7_,&LampB7);
        
        LOG(INFO, "[esp32multifunction] pwmchip inited.");
        
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
    
