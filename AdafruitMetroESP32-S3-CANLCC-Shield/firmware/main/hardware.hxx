// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Oct 20 16:23:56 2026
//  Last Modified : <261021.0856>
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

#ifndef __HARDWARE_HXX
#define __HARDWARE_HXX

#include <freertos_drivers/common/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>


/// GPIO Pin connected to the TWAI (CAN) Transceiver RX pin.
static constexpr gpio_num_t CONFIG_TWAI_RX_PIN = GPIO_NUM_41; /* RX/0 header pin */

/// GPIO Pin connected to the TWAI (CAN) Transceiver TX pin.
static constexpr gpio_num_t CONFIG_TWAI_TX_PIN = GPIO_NUM_40; /* TX/1 header pin */

/// GPIO Pin used for I2C SDA.
static constexpr gpio_num_t CONFIG_SDA_PIN = GPIO_NUM_47; /* SDA pin */

/// GPIO Pin used for I2C SCL.
static constexpr gpio_num_t CONFIG_SCL_PIN = GPIO_NUM_48; /* SCL pin */

#define ActPin GpioOutputSafeHighInvert

GPIO_PIN(LED_ACT1,ActPin,14);
GPIO_PIN(LED_ACT2,ActPin,15);


#define LEDPin GpioOutputSafeLow

GPIO_PIN(SIG1,LEDPin,2);
GPIO_PIN(SIG2,LEDPin,3);
GPIO_PIN(SIG3,LEDPin,4);
GPIO_PIN(SIG4,LEDPin,5);

#define MotorPin GpioOutputSafeLow

GPIO_PIN(StallM,MotorPin,6);
GPIO_PIN(StallN,MotorPin,7);

#define SERVOPINS {8, 9, 10, 11}

#define SwitchPin GpioOutputSafeLow

GPIO_PIN(SSR1,SwitchPin,12);
GPIO_PIN(SSR2,SwitchPin,13);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<LED_ACT1_Pin, LED_ACT2_Pin,
                        SIG1_Pin, SIG2_Pin, SIG3_Pin, SIG4_Pin, 
                        StallM_Pin, StallN_Pin, SSR1_Pin, SSR2_Pin> 
        GpioInit;

#endif // __HARDWARE_HXX

