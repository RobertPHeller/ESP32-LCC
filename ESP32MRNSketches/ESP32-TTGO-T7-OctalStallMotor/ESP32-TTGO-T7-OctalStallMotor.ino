// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Mar 13 10:22:45 2019
//  Last Modified : <220301.0949>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2019  Robert Heller D/B/A Deepwoods Software
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

/** @file ESP32BaseBoard.ino
 * 
 * Generic base for the various ESP32 I/O boards from Deepwoods Software.
 * (Based on ESP32IOBoard.ino by Mike Dunston.)
 * 
 * @author Robert Heller
 * @date 13 March 2019
 */

#include <Arduino.h>
#include <SPIFFS.h>

#include <OpenMRNLite.h>

static const char rcsid[] = "@(#) : $Id$";


#include "config.h"
#include "NODEID.h" // Get nodeid from an externally generated header file

#include <utils/GpioInitializer.hxx>

#include <freertos_drivers/arduino/ArduinoGpio.hxx>
#include "Turnout.h"
#include "Points.h"
#include "TrackCircuit.h"
#include "Logic.h"


#define MotorPin GpioOutputSafeLow
#define SensePin GpioInputNP

GPIO_PIN(Motor1, MotorPin, 0);
GPIO_PIN(Motor2, MotorPin, 4);
GPIO_PIN(Motor3, MotorPin, 16);
GPIO_PIN(Motor4, MotorPin, 17);
GPIO_PIN(Motor5, MotorPin, 18);
GPIO_PIN(Motor6, MotorPin, 19);
GPIO_PIN(Motor7, MotorPin, 32);
GPIO_PIN(Motor8, MotorPin, 33);

GPIO_PIN(Points1, SensePin, 34);
GPIO_PIN(Points2, SensePin, 35);
GPIO_PIN(Points3, SensePin, 36);
GPIO_PIN(Points4, SensePin, 39);
GPIO_PIN(Points5, SensePin, 23);
GPIO_PIN(Points6, SensePin, 25);
GPIO_PIN(Points7, SensePin, 26);
GPIO_PIN(Points8, SensePin, 27);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<Motor1_Pin, Motor2_Pin, Motor3_Pin, 
                        Motor4_Pin, Motor5_Pin, Motor6_Pin, 
                        Motor7_Pin, Motor8_Pin, Points1_Pin, 
                        Points2_Pin, Points3_Pin, Points4_Pin,
                        Points5_Pin, Points6_Pin, Points7_Pin,
                        Points8_Pin> GpioInit;

constexpr gpio_num_t CAN_RX_PIN = GPIO_NUM_4;
constexpr gpio_num_t CAN_TX_PIN = GPIO_NUM_5;

/// This is the primary entrypoint for the OpenMRN/LCC stack.
OpenMRN openmrn(NODE_ID);

// note the dummy string below is required due to a bug in the GCC compiler
// for the ESP32
string dummystring("abcdef");

/// ConfigDef comes from config.h and is specific to this particular device and
/// target. It defines the layout of the configuration memory space and is also
/// used to generate the cdi.xml file. Here we instantiate the configuration
/// layout. The argument of offset zero is ignored and will be removed later.
static constexpr openlcb::ConfigDef cfg(0);

// Instantiates the actual producer and consumer objects for the given GPIO
// pins from above. The ConfiguredConsumer class takes care of most of the
// complicated setup and operation requirements. We need to give it the virtual
// node pointer, the configuration configuration from the CDI definition, and
// the hardware pin definition. The virtual node pointer comes from the stack
// object. The configuration structure comes from the CDI definition object,
// segment 'seg', in which there is a repeated group 'consumers', and we assign
// the individual entries to the individual consumers. Each consumer gets its
// own GPIO pin.

TrackCircuit c1(openmrn.stack()->node(),cfg.seg().circuits().entry<0>());
TrackCircuit c2(openmrn.stack()->node(),cfg.seg().circuits().entry<1>());
TrackCircuit c3(openmrn.stack()->node(),cfg.seg().circuits().entry<2>());
TrackCircuit c4(openmrn.stack()->node(),cfg.seg().circuits().entry<3>());
TrackCircuit c5(openmrn.stack()->node(),cfg.seg().circuits().entry<4>());
TrackCircuit c6(openmrn.stack()->node(),cfg.seg().circuits().entry<5>());
TrackCircuit c7(openmrn.stack()->node(),cfg.seg().circuits().entry<6>());
TrackCircuit c8(openmrn.stack()->node(),cfg.seg().circuits().entry<7>());

TrackCircuit *circuits[8] = {&c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8};

Logic l32(openmrn.stack()->node(),cfg.seg().logics().entry<31>(),openmrn.stack()->executor()->active_timers(),nullptr);
Logic l31(openmrn.stack()->node(),cfg.seg().logics().entry<30>(),openmrn.stack()->executor()->active_timers(),&l32);
Logic l30(openmrn.stack()->node(),cfg.seg().logics().entry<29>(),openmrn.stack()->executor()->active_timers(),&l31);
Logic l29(openmrn.stack()->node(),cfg.seg().logics().entry<28>(),openmrn.stack()->executor()->active_timers(),&l30);
Logic l28(openmrn.stack()->node(),cfg.seg().logics().entry<27>(),openmrn.stack()->executor()->active_timers(),&l29);
Logic l27(openmrn.stack()->node(),cfg.seg().logics().entry<26>(),openmrn.stack()->executor()->active_timers(),&l28);
Logic l26(openmrn.stack()->node(),cfg.seg().logics().entry<25>(),openmrn.stack()->executor()->active_timers(),&l27);
Logic l25(openmrn.stack()->node(),cfg.seg().logics().entry<24>(),openmrn.stack()->executor()->active_timers(),&l26);
Logic l24(openmrn.stack()->node(),cfg.seg().logics().entry<23>(),openmrn.stack()->executor()->active_timers(),&l25);
Logic l23(openmrn.stack()->node(),cfg.seg().logics().entry<22>(),openmrn.stack()->executor()->active_timers(),&l24);
Logic l22(openmrn.stack()->node(),cfg.seg().logics().entry<21>(),openmrn.stack()->executor()->active_timers(),&l23);
Logic l21(openmrn.stack()->node(),cfg.seg().logics().entry<20>(),openmrn.stack()->executor()->active_timers(),&l22);
Logic l20(openmrn.stack()->node(),cfg.seg().logics().entry<19>(),openmrn.stack()->executor()->active_timers(),&l21);
Logic l19(openmrn.stack()->node(),cfg.seg().logics().entry<18>(),openmrn.stack()->executor()->active_timers(),&l20);
Logic l18(openmrn.stack()->node(),cfg.seg().logics().entry<17>(),openmrn.stack()->executor()->active_timers(),&l19);
Logic l17(openmrn.stack()->node(),cfg.seg().logics().entry<16>(),openmrn.stack()->executor()->active_timers(),&l18);
Logic l16(openmrn.stack()->node(),cfg.seg().logics().entry<15>(),openmrn.stack()->executor()->active_timers(),&l17);
Logic l15(openmrn.stack()->node(),cfg.seg().logics().entry<14>(),openmrn.stack()->executor()->active_timers(),&l16);
Logic l14(openmrn.stack()->node(),cfg.seg().logics().entry<13>(),openmrn.stack()->executor()->active_timers(),&l15);
Logic l13(openmrn.stack()->node(),cfg.seg().logics().entry<12>(),openmrn.stack()->executor()->active_timers(),&l14);
Logic l12(openmrn.stack()->node(),cfg.seg().logics().entry<11>(),openmrn.stack()->executor()->active_timers(),&l13);
Logic l11(openmrn.stack()->node(),cfg.seg().logics().entry<10>(),openmrn.stack()->executor()->active_timers(),&l12);
Logic l10(openmrn.stack()->node(),cfg.seg().logics().entry<9>(),openmrn.stack()->executor()->active_timers(),&l11);
Logic l9(openmrn.stack()->node(),cfg.seg().logics().entry<8>(),openmrn.stack()->executor()->active_timers(),&l10);
Logic l8(openmrn.stack()->node(),cfg.seg().logics().entry<7>(),openmrn.stack()->executor()->active_timers(),&l9);
Logic l7(openmrn.stack()->node(),cfg.seg().logics().entry<6>(),openmrn.stack()->executor()->active_timers(),&l8);
Logic l6(openmrn.stack()->node(),cfg.seg().logics().entry<5>(),openmrn.stack()->executor()->active_timers(),&l7);
Logic l5(openmrn.stack()->node(),cfg.seg().logics().entry<4>(),openmrn.stack()->executor()->active_timers(),&l6);
Logic l4(openmrn.stack()->node(),cfg.seg().logics().entry<3>(),openmrn.stack()->executor()->active_timers(),&l5);
Logic l3(openmrn.stack()->node(),cfg.seg().logics().entry<2>(),openmrn.stack()->executor()->active_timers(),&l4);
Logic l2(openmrn.stack()->node(),cfg.seg().logics().entry<1>(),openmrn.stack()->executor()->active_timers(),&l3);
Logic l1(openmrn.stack()->node(),cfg.seg().logics().entry<0>(),openmrn.stack()->executor()->active_timers(),&l2);

Turnout turnout1(openmrn.stack()->node(), cfg.seg().turnouts().entry<0>(),Motor1_Pin());
Turnout turnout2(openmrn.stack()->node(), cfg.seg().turnouts().entry<1>(),Motor2_Pin());
Turnout turnout3(openmrn.stack()->node(), cfg.seg().turnouts().entry<2>(),Motor3_Pin());
Turnout turnout4(openmrn.stack()->node(), cfg.seg().turnouts().entry<3>(),Motor4_Pin());
Turnout turnout5(openmrn.stack()->node(), cfg.seg().turnouts().entry<0>(),Motor5_Pin());
Turnout turnout6(openmrn.stack()->node(), cfg.seg().turnouts().entry<1>(),Motor6_Pin());
Turnout turnout7(openmrn.stack()->node(), cfg.seg().turnouts().entry<2>(),Motor7_Pin());
Turnout turnout8(openmrn.stack()->node(), cfg.seg().turnouts().entry<3>(),Motor8_Pin());

Points  points1(openmrn.stack()->node(), cfg.seg().points().entry<0>(),Points1_Pin());
Points  points2(openmrn.stack()->node(), cfg.seg().points().entry<1>(),Points2_Pin());
Points  points3(openmrn.stack()->node(), cfg.seg().points().entry<2>(),Points3_Pin());
Points  points4(openmrn.stack()->node(), cfg.seg().points().entry<3>(),Points4_Pin());
Points  points5(openmrn.stack()->node(), cfg.seg().points().entry<0>(),Points5_Pin());
Points  points6(openmrn.stack()->node(), cfg.seg().points().entry<1>(),Points6_Pin());
Points  points7(openmrn.stack()->node(), cfg.seg().points().entry<2>(),Points7_Pin());
Points  points8(openmrn.stack()->node(), cfg.seg().points().entry<3>(),Points8_Pin());


// The producers need to be polled repeatedly for changes and to execute the
// debouncing algorithm. This class instantiates a refreshloop and adds the two
// producers to it.
openlcb::RefreshLoop points_refresh_loop(openmrn.stack()->node(),{
    points1.polling()
          , points2.polling()
          , points3.polling()
          , points4.polling()
          , points5.polling()
          , points6.polling()
          , points7.polling()
          , points8.polling()
});

class FactoryResetHelper : public DefaultConfigUpdateListener {
public:
    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable *done) OVERRIDE {
        AutoNotify n(done);
        return UPDATED;
    }

    void factory_reset(int fd) override
    {
        cfg.userinfo().name().write(fd, openlcb::SNIP_STATIC_DATA.model_name);
        cfg.userinfo().description().write(
            fd, "OpenLCB + Arduino-ESP32 on an ESP32QuadSMCSense.");
        for(int i = 0; i < openlcb::NUM_TURNOUTS; i++)
        {
            cfg.seg().turnouts().entry(i).description().write(fd, "");
        }
        for(int i = 0; i < openlcb::NUM_POINTSS; i++)
        {
            cfg.seg().points().entry(i).description().write(fd, "");
        }
    }
} factory_reset_helper;

namespace openlcb
{
    // Name of CDI.xml to generate dynamically.
    const char CDI_FILENAME[] = "/spiffs/cdi.xml";

    // This will stop openlcb from exporting the CDI memory space upon start.
    extern const char CDI_DATA[] = "";

    // Path to where OpenMRN should persist general configuration data.
    extern const char *const CONFIG_FILENAME = "/spiffs/openlcb_config";

    // The size of the memory space to export over the above device.
    extern const size_t CONFIG_FILE_SIZE = cfg.seg().size() + cfg.seg().offset();

    // Default to store the dynamic SNIP data is stored in the same persistant
    // data file as general configuration data.
    extern const char *const SNIP_DYNAMIC_FILENAME = CONFIG_FILENAME;
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200L);
    // Initialize the SPIFFS filesystem as our persistence layer
    if (!SPIFFS.begin())
    {
        printf("SPIFFS failed to mount, attempting to format and remount\n");
        if (!SPIFFS.begin(true))
        {
            printf("SPIFFS mount failed even with format, giving up!\n");
            while (1)
            {
                // Unable to start SPIFFS successfully, give up and wait
                // for WDT to kick in
            }
        }
    }

    // Create the CDI.xml dynamically
    openmrn.create_config_descriptor_xml(cfg, openlcb::CDI_FILENAME);

    // Create the default internal configuration file
    openmrn.stack()->create_config_file_if_needed(cfg.seg().internal_config(),
        openlcb::CANONICAL_VERSION, openlcb::CONFIG_FILE_SIZE);

    // initialize all declared GPIO pins
    GpioInit::hw_init();

    // Start the OpenMRN stack
    openmrn.begin();
    openmrn.start_executor_thread();

    // Add the hardware CAN device as a bridge
    openmrn.add_can_port(
        new Esp32HardwareCan("esp32can", CAN_RX_PIN, CAN_TX_PIN));
}
                
void loop() {
    // put your main code here, to run repeatedly:
    // Call the OpenMRN executor, this needs to be done as often
    // as possible from the loop() method.
    openmrn.loop();
}    
