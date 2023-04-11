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
//  Last Modified : <230411.0944>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2022  Robert Heller D/B/A Deepwoods Software
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
#include "cdidata.hxx"
#include "EventBroadcastHelper.hxx"
#include "FactoryResetHelper.hxx"
#include "HealthMonitor.hxx"
#include "fs.hxx"
#include "hardware.hxx"
#include "NvsManager.hxx"
#include "NodeRebootHelper.hxx"
#include "BootPauseHelper.hxx"

#include <algorithm>
#include <driver/uart.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_ota_ops.h>
#include <esp_system.h>
#include <esp_task_wdt.h>
#include <freertos_includes.h>   
#include <openlcb/SimpleStack.hxx>
#include <freertos_drivers/esp32/Esp32HardwareTwai.hxx>
#include <freertos_drivers/esp32/Esp32WiFiManager.hxx>
#include <freertos_drivers/esp32/Esp32BootloaderHal.hxx>
#include <freertos_drivers/esp32/Esp32SocInfo.hxx>
#include <openlcb/MemoryConfigClient.hxx>
#include <openlcb/RefreshLoop.hxx>
#include <openlcb/SimpleStack.hxx>
#include <utils/constants.hxx>
#include <utils/format_utils.hxx>
#include "utils/Debouncer.hxx"
#include <openlcb/MultiConfiguredPC.hxx>
#include <openlcb/ServoConsumerConfig.hxx>
#include <openlcb/ServoConsumer.hxx>

#include "i2c.h"
#include "i2c-dev.h"
#include "Esp32HardwareI2C.hxx"
#include "MCP23017Gpio.hxx"
#include "freertos_drivers/arduino/PWM.hxx"
#include "PCA9685PWM.hxx"

///////////////////////////////////////////////////////////////////////////////
// Increase the CAN RX frame buffer size to reduce overruns when there is high
// traffic load (ie: large datagram transport).
///////////////////////////////////////////////////////////////////////////////
OVERRIDE_CONST(can_rx_buffer_size, 64);
OVERRIDE_CONST(num_memory_spaces, 6);

esp32i2ctest::ConfigDef cfg(0);
Esp32HardwareTwai twai(CONFIG_TWAI_RX_PIN, CONFIG_TWAI_TX_PIN);
Esp32HardwareI2C i2c("/dev/i2c");
Executor<1> io_executor("io_thread", 1, 1300);
MCP23017 gpiochip(&io_executor,0,0,0);

constexpr const MCP23017Gpio IOEXT0_A0(&gpiochip, MCP23017::PORTA, 0);
constexpr const MCP23017Gpio IOEXT0_A1(&gpiochip, MCP23017::PORTA, 1);
constexpr const MCP23017Gpio IOEXT0_A2(&gpiochip, MCP23017::PORTA, 2);
constexpr const MCP23017Gpio IOEXT0_A3(&gpiochip, MCP23017::PORTA, 3);
constexpr const MCP23017Gpio IOEXT0_A4(&gpiochip, MCP23017::PORTA, 4);
constexpr const MCP23017Gpio IOEXT0_A5(&gpiochip, MCP23017::PORTA, 5);
constexpr const MCP23017Gpio IOEXT0_A6(&gpiochip, MCP23017::PORTA, 6);
constexpr const MCP23017Gpio IOEXT0_A7(&gpiochip, MCP23017::PORTA, 7);

constexpr const MCP23017Gpio IOEXT0_B0(&gpiochip, MCP23017::PORTB, 0);
constexpr const MCP23017Gpio IOEXT0_B1(&gpiochip, MCP23017::PORTB, 1);
constexpr const MCP23017Gpio IOEXT0_B2(&gpiochip, MCP23017::PORTB, 2);
constexpr const MCP23017Gpio IOEXT0_B3(&gpiochip, MCP23017::PORTB, 3);
constexpr const MCP23017Gpio IOEXT0_B4(&gpiochip, MCP23017::PORTB, 4);
constexpr const MCP23017Gpio IOEXT0_B5(&gpiochip, MCP23017::PORTB, 5);
constexpr const MCP23017Gpio IOEXT0_B6(&gpiochip, MCP23017::PORTB, 6);
constexpr const MCP23017Gpio IOEXT0_B7(&gpiochip, MCP23017::PORTB, 7);

constexpr const Gpio *const kPortExt0[] = {
    &IOEXT0_A0, &IOEXT0_A1, &IOEXT0_A2, &IOEXT0_A3, //
    &IOEXT0_A4, &IOEXT0_A5, &IOEXT0_A6, &IOEXT0_A7, //
    &IOEXT0_B0, &IOEXT0_B1, &IOEXT0_B2, &IOEXT0_B3, //
    &IOEXT0_B4, &IOEXT0_B5, &IOEXT0_B6, &IOEXT0_B7 //
};

PCA9685PWM pwmchip;

PCA9685PWMBit Servo0(&pwmchip,0);
PCA9685PWMBit Servo1(&pwmchip,1);
PCA9685PWMBit Servo2(&pwmchip,2);
PCA9685PWMBit Servo3(&pwmchip,3);
PCA9685PWMBit Servo4(&pwmchip,4);
PCA9685PWMBit Servo5(&pwmchip,5);
PCA9685PWMBit Servo6(&pwmchip,6);
PCA9685PWMBit Servo7(&pwmchip,7);
PCA9685PWMBit Servo8(&pwmchip,8);
PCA9685PWMBit Servo9(&pwmchip,9);
PCA9685PWMBit Servo10(&pwmchip,10);
PCA9685PWMBit Servo11(&pwmchip,11);
PCA9685PWMBit Servo12(&pwmchip,12);
PCA9685PWMBit Servo13(&pwmchip,13);
PCA9685PWMBit Servo14(&pwmchip,14);
PCA9685PWMBit Servo15(&pwmchip,15);

namespace openlcb
{
    /// Name of CDI.xml to generate dynamically.
    const char CDI_FILENAME[] = "/fs/cdi.xml";

    // Path to where OpenMRN should persist general configuration data.
    extern const char *const CONFIG_FILENAME = "/fs/config";

    // The size of the memory space to export over the above device.
    extern const size_t CONFIG_FILE_SIZE =
        cfg.seg().size() + cfg.seg().offset();

    // Default to store the dynamic SNIP data is stored in the same persistant
    // data file as general configuration data.
    extern const char *const SNIP_DYNAMIC_FILENAME = "/fs/config";

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
    extern const SimpleNodeStaticValues SNIP_STATIC_DATA =
    {
        4,
        SNIP_PROJECT_PAGE,
        SNIP_PROJECT_NAME,
        SNIP_HW_VERSION,
        SNIP_SW_VERSION
    };

    /// Modify this value every time the EEPROM needs to be cleared on the node
    /// after an update.
    static constexpr uint16_t CANONICAL_VERSION = CDI_VERSION;

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


namespace esp32i2ctest {

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
    
    for (int i = 0; i < 16; i++)
    {
        cfg.seg().servo_consumers().entry(i).description().write(fd,"");
        CDI_FACTORY_RESET(cfg.seg().servo_consumers().entry(i).servo_min_percent);
        CDI_FACTORY_RESET(cfg.seg().servo_consumers().entry(i).servo_max_percent);
    }
    for (int i = 0; i < 16; i++)
    {
        CDI_FACTORY_RESET(cfg.seg().ext0_pc().entry(i).action);
        CDI_FACTORY_RESET(cfg.seg().ext0_pc().entry(i).debounce);
        cfg.seg().ext0_pc().entry(i).pc().description().write(fd,"");
    }
        
}

}


void app_main()
{
    // capture the reason for the CPU reset
    uint8_t reset_reason = Esp32SocInfo::print_soc_info();
    
    LOG(INFO, "[SNIP] version:%d, manufacturer:%s, model:%s, hw-v:%s, sw-v:%s"
      , openlcb::SNIP_STATIC_DATA.version
      , openlcb::SNIP_STATIC_DATA.manufacturer_name
      , openlcb::SNIP_STATIC_DATA.model_name
      , openlcb::SNIP_STATIC_DATA.hardware_version
      , openlcb::SNIP_STATIC_DATA.software_version);
    bool reset_events = false;
    bool cleanup_config_tree = false;
    
    i2c.hw_init(CONFIG_SDA_PIN,CONFIG_SCL_PIN,400000,I2C_NUM_0);
    int i2cfd = ::open("/dev/i2c/i2c0", O_RDWR);
    gpiochip.init(i2cfd);
    
    
    pwmchip.init("/dev/i2c/i2c0",PWMCHIP_ADDRESS1);
    
    //GpioInit::hw_init();
    
    nvsmanager::NvsManager nvs;
    nvs.init(reset_reason);
    
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
    
    if (nvs.should_reset_events())
    {
        reset_events = true;
        // reset the flag so we start in normal operating mode next time.
        nvs.clear_reset_events();
    }
    nvs.CheckPersist();
    
    nvs.DisplayNvsConfiguration();
    mount_fs(cleanup_config_tree);
    openlcb::SimpleCanStack stack(nvs.node_id());
    LOG(INFO, "[MAIN] SimpleCanStack allocated");
#if CONFIG_OLCB_PRINT_ALL_PACKETS
    stack.print_all_packets();
#endif
    nvs.register_virtual_memory_spaces(&stack);
    openlcb::MemoryConfigClient memory_client(stack.node(), stack.memory_config_handler());
    LOG(INFO, "[MAIN] MemoryConfigClient allocated");
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
    esp32i2ctest::FactoryResetHelper factory_reset_helper;
    LOG(INFO, "[MAIN] FactoryResetHelper allocated");
    esp32i2ctest::EventBroadcastHelper event_helper;
    LOG(INFO, "[MAIN] EventBroadcastHelper allocated");
    healthmonitor::HealthMonitor health_mon(stack.service());
    LOG(INFO, "[MAIN] HealthMonitor allocated");
    
    openlcb::MultiConfiguredPC ext0_pcs(stack.node(), kPortExt0, 
                                        ARRAYSIZE(kPortExt0), 
                                        cfg.seg().ext0_pc());
    openlcb::RefreshLoop ext0(stack.node(),{ext0_pcs.polling()});
    
    openlcb::ServoConsumer srv0(stack.node(), 
                                cfg.seg().servo_consumers().entry<0>(),
                                1000,&Servo0);
    openlcb::ServoConsumer srv1(stack.node(), 
                                cfg.seg().servo_consumers().entry<1>(),
                                1000,&Servo1);
    openlcb::ServoConsumer srv2(stack.node(), 
                                cfg.seg().servo_consumers().entry<2>(),
                                1000,&Servo2);
    openlcb::ServoConsumer srv3(stack.node(), 
                                cfg.seg().servo_consumers().entry<3>(),
                                1000,&Servo3);
    openlcb::ServoConsumer srv4(stack.node(), 
                                cfg.seg().servo_consumers().entry<4>(),
                                1000,&Servo4);
    openlcb::ServoConsumer srv5(stack.node(), 
                                cfg.seg().servo_consumers().entry<5>(),
                                1000,&Servo5);
    openlcb::ServoConsumer srv6(stack.node(), 
                                cfg.seg().servo_consumers().entry<6>(),
                                1000,&Servo6);
    openlcb::ServoConsumer srv7(stack.node(), 
                                cfg.seg().servo_consumers().entry<7>(),
                                1000,&Servo7);
    openlcb::ServoConsumer srv8(stack.node(), 
                                cfg.seg().servo_consumers().entry<8>(),
                                1000,&Servo8);
    openlcb::ServoConsumer srv9(stack.node(), 
                                cfg.seg().servo_consumers().entry<9>(),
                                1000,&Servo9);
    openlcb::ServoConsumer srv10(stack.node(), 
                                 cfg.seg().servo_consumers().entry<10>(),
                                 1000,&Servo10);
    openlcb::ServoConsumer srv11(stack.node(), 
                                 cfg.seg().servo_consumers().entry<11>(),
                                 1000,&Servo11);
    openlcb::ServoConsumer srv12(stack.node(), 
                                 cfg.seg().servo_consumers().entry<12>(),
                                 1000,&Servo12);
    openlcb::ServoConsumer srv13(stack.node(), 
                                 cfg.seg().servo_consumers().entry<13>(),
                                 1000,&Servo13);
    openlcb::ServoConsumer srv14(stack.node(), 
                                 cfg.seg().servo_consumers().entry<14>(),
                                 1000,&Servo14);
    openlcb::ServoConsumer srv15(stack.node(), 
                                 cfg.seg().servo_consumers().entry<15>(),
                                 1000,&Servo15);
                                
    LOG(INFO, "[MAIN] config file size is %d",openlcb::CONFIG_FILE_SIZE);
    // Create config file and initiate factory reset if it doesn't exist or is
    // otherwise corrupted.
    int config_fd =
          stack.create_config_file_if_needed(cfg.seg().internal_config(),
                                             openlcb::CANONICAL_VERSION,
                                             openlcb::CONFIG_FILE_SIZE);
    stack.check_version_and_factory_reset(cfg.seg().internal_config(),
                                          CDI_VERSION,
                                          cleanup_config_tree);
    reboothelpers::NodeRebootHelper node_reboot_helper(&stack, config_fd);

    if (reset_events)
    {
        LOG(WARNING, "[CDI] Resetting event IDs");
        stack.factory_reset_all_events(cfg.seg().internal_config(), 
                                       nvs.node_id(), config_fd);
        fsync(config_fd);
    }
    
    
    // Initialize the TWAI driver.
    twai.hw_init();
    
    // Add the TWAI port to the stack.
    stack.add_can_port_select("/dev/twai/twai0");
    
    // Start the stack in the background using it's own task.
    stack.loop_executor();
    // At this point the OpenMRN stack is running in it's own task and we can
    // safely exit from this one. We do not need to cleanup as that will be
    // handled automatically by ESP-IDF.
}



} // extern "C"
    
