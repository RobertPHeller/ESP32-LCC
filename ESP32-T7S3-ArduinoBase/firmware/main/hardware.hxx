// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Mar 11 11:14:17 2023
//  Last Modified : <230413.1340>
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

#ifndef __HAERWARE_HXX
#define __HAERWARE_HXX

#ifdef ESP_PLATFORM

#include <freertos_drivers/arduino/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>



#define ActPin GpioOutputSafeHighInvert

GPIO_PIN(LED_ACT1, ActPin, 15);
GPIO_PIN(LED_ACT2, ActPin, 0);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<LED_ACT1_Pin, LED_ACT2_Pin> GpioInit;

/// GPIO Pin connected to the TWAI (CAN) Transceiver RX pin.
// ADC2_CHANNEL_0
static constexpr gpio_num_t CONFIG_TWAI_RX_PIN = GPIO_NUM_4;

/// GPIO Pin connected to the TWAI (CAN) Transceiver TX pin.
static constexpr gpio_num_t CONFIG_TWAI_TX_PIN = GPIO_NUM_5;

/// GPIO Pin used for I2C SDA.
static constexpr gpio_num_t CONFIG_SDA_PIN = GPIO_NUM_2;

/// GPIO Pin used for I2C SCL.
static constexpr gpio_num_t CONFIG_SCL_PIN = GPIO_NUM_3;

#endif

#define RIR4ADDRESS 0x30
//#define RIR4ADDRESS2 0x31

//#define LOWRESCROSSING
//#define STANDARDRESCROSSING


#endif // __HAERWARE_HXX

