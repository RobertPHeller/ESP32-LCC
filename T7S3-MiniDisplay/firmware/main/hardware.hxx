// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-29 19:42:19
//  Last Modified : <260406.0925>
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
/// @file hardware.hxx
/// @author Robert Heller
/// @date 2025-11-29 19:42:19
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __HARDWARE_HXX
#define __HARDWARE_HXX

#include <freertos_drivers/common/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>





GPIO_PIN(BOOT,GpioInputNP, 0);

/// CAN
/// GPIO Pin connected to the TWAI (CAN) Transceiver RX pin.
static constexpr gpio_num_t CONFIG_TWAI_RX_PIN = GPIO_NUM_4;
/// GPIO Pin connected to the TWAI (CAN) Transceiver TX pin.
static constexpr gpio_num_t CONFIG_TWAI_TX_PIN = GPIO_NUM_5;

/// I2C
/// GPIO Pin connected to SCL
static constexpr gpio_num_t CONFIG_SCL_PIN = GPIO_NUM_3;
/// GPIO Pin connected to SDA
static constexpr gpio_num_t CONFIG_SDA_PIN = GPIO_NUM_2;

/// SPI
/// GPIO Pin connected to SCLK
static constexpr gpio_num_t CONFIG_SCLK_PIN = GPIO_NUM_10;
/// GPIO Pin connected to MOSI
static constexpr gpio_num_t CONFIG_MOSI_PIN = GPIO_NUM_18;
/// GPIO Pin connected to MISO
static constexpr gpio_num_t CONFIG_MISO_PIN = GPIO_NUM_38;
/// GPIO Pin connected to CardCS
static constexpr gpio_num_t CONFIG_CardCS_PIN = GPIO_NUM_47;
GPIO_PIN(CDetect,GpioInputNP, 48);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<BOOT_Pin, CDetect_Pin> GpioInit;

#endif // __HARDWARE_HXX

