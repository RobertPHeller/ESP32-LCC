// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Fri Apr 19 22:31:56 2024
//  Last Modified : <240419.2248>
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
/// @file hardware.hxx
/// @author Robert Heller
/// @date Fri Apr 19 22:31:56 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __HARDWARE_HXX
#define __HARDWARE_HXX

#include <freertos_drivers/arduino/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>

#define BacklightPin {9}
GPIO_PIN(DRs, GpioOutputSafeHighInvert, 48);
GPIO_PIN(DReset, GpioOutputSafeHighInvert, 13);

static constexpr gpio_num_t CONFIG_SCLK = GPIO_NUM_10;
static constexpr gpio_num_t CONFIG_MOSI = GPIO_NUM_18;
static constexpr gpio_num_t CONFIG_MISO = GPIO_NUM_38;
static constexpr gpio_num_t CONFIG_DCS1 = GPIO_NUM_46;
static constexpr gpio_num_t CONFIG_DCS2 = GPIO_NUM_45;
static constexpr gpio_num_t CONFIG_CardCS = GPIO_NUM_47;

#define ActPin GpioOutputSafeHighInvert

GPIO_PIN(LED_ACT1, ActPin, 15);
GPIO_PIN(LED_ACT2, ActPin, 0);
GPIO_PIN(BOOT,GpioInputNP, 0);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<DRs_Pin, DReset_Pin, LED_ACT1_Pin, LED_ACT2_Pin,
                        BOOT_Pin> GpioInit;

/// GPIO Pin connected to the TWAI (CAN) Transceiver RX pin.
static constexpr gpio_num_t CONFIG_TWAI_RX_PIN = GPIO_NUM_4;

/// GPIO Pin connected to the TWAI (CAN) Transceiver TX pin.
static constexpr gpio_num_t CONFIG_TWAI_TX_PIN = GPIO_NUM_5;

/// GPIO Pin used for I2C SDA.
static constexpr gpio_num_t CONFIG_SDA_PIN = GPIO_NUM_40;
/// GPIO Pin used for I2C SCL.
static constexpr gpio_num_t CONFIG_SCL_PIN = GPIO_NUM_3;


#endif // __HARDWARE_HXX

