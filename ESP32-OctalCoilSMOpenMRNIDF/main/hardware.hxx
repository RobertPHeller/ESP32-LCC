// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Jan 15 16:13:22 2023
//  Last Modified : <230131.1653>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
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

#include <freertos_drivers/arduino/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>


#define MotorPin GpioOutputSafeLow
GPIO_PIN(Motor1, MotorPin, 6);
GPIO_PIN(Motor2, MotorPin, 7);
GPIO_PIN(Motor3, MotorPin, 15);
GPIO_PIN(Motor4, MotorPin, 16);
GPIO_PIN(Motor5, MotorPin, 8);
GPIO_PIN(Motor6, MotorPin, 3);
GPIO_PIN(Motor7, MotorPin, 46);
GPIO_PIN(Motor8, MotorPin, 9);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<Motor1_Pin, Motor2_Pin, Motor3_Pin, Motor4_Pin,
                        Motor5_Pin, Motor6_Pin, Motor7_Pin, Motor8_Pin> GpioInit;

/// GPIO Pin connected to the TWAI (CAN) Transceiver RX pin.
// ADC2_CHANNEL_0
static constexpr gpio_num_t CONFIG_TWAI_RX_PIN = GPIO_NUM_4;

/// GPIO Pin connected to the TWAI (CAN) Transceiver TX pin.
static constexpr gpio_num_t CONFIG_TWAI_TX_PIN = GPIO_NUM_5;



#endif // __HARDWARE_HXX

