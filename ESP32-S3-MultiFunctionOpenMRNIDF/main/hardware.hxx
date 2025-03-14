// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Jun 25 09:07:59 2022
//  Last Modified : <231010.0954>
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
/// @file hardware.hxx
/// @author Robert Heller 
/// @date Sat Jun 25 09:07:59 2022
//////////////////////////////////////////////////////////////////////////////

#ifndef __HARDWARE_HXX
#define __HARDWARE_HXX

#include <freertos_drivers/arduino/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>

#if defined(CONFIG_SERVO_TURNOUTS)

#define TURNOUTSERVOPINS {9,11,8,43}

#else
#define MotorPin GpioOutputSafeLow

GPIO_PIN(Motor1, MotorPin,  9);
GPIO_PIN(Motor2, MotorPin, 11);
GPIO_PIN(Motor3, MotorPin,  8);
#ifdef CONFIG_DEVKIT_BREADBOARD
GPIO_PIN(Motor4, MotorPin, 45);
#elif defined(CONFIG_T7S3)
GPIO_PIN(Motor4, MotorPin, 42);
#else
GPIO_PIN(Motor4, MotorPin, 33);
#endif
#endif

#define SensePin GpioInputNP

GPIO_PIN(Points1, SensePin, 12);
GPIO_PIN(Points2, SensePin, 13);
GPIO_PIN(Points3, SensePin, 14);
GPIO_PIN(Points4, SensePin, 10);

#define ODPin  GpioInputNP

#ifdef CONFIG_DEVKIT_BREADBOARD
GPIO_PIN(OD1, ODPin, 46);
#elif defined(CONFIG_T7S3)
GPIO_PIN(OD1, ODPin, 39);
#else
GPIO_PIN(OD1, ODPin, 34);
#endif
#ifdef CONFIG_T7S3
GPIO_PIN(OD2, ODPin, 48);
GPIO_PIN(OD3, ODPin, 45);
#else
GPIO_PIN(OD2, ODPin, 35);
GPIO_PIN(OD3, ODPin, 36);
#endif
GPIO_PIN(OD4, ODPin,  7);

#define LEDPin GpioOutputSafeLow

GPIO_PIN(LED1, LEDPin, 17);
GPIO_PIN(LED2, LEDPin, 18);
GPIO_PIN(LED3, LEDPin, 21);
GPIO_PIN(LED4, LEDPin,  1);

#define ButtonPin GpioInputNP

GPIO_PIN(Button1, ButtonPin, 38);
GPIO_PIN(Button2, ButtonPin,  6);
#ifdef CONFIG_T7S3
GPIO_PIN(Button3, ButtonPin, 46);
#else
GPIO_PIN(Button3, ButtonPin, 37);
#endif
GPIO_PIN(Button4, ButtonPin, 16);

#define ActPin GpioOutputSafeHighInvert

GPIO_PIN(LED_ACT1, ActPin, 15);
GPIO_PIN(LED_ACT2, ActPin, 0);
GPIO_PIN(BOOT,GpioInputNP, 0);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<
#if !defined(CONFIG_SERVO_TURNOUTS)
                        Motor1_Pin, Motor2_Pin, Motor3_Pin, Motor4_Pin,
#endif
                        Points1_Pin, Points2_Pin, Points3_Pin, Points4_Pin,
                        OD1_Pin, OD2_Pin, OD3_Pin, OD4_Pin,
                        LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin,
                        Button1_Pin, Button2_Pin, Button3_Pin, Button4_Pin,
                        LED_ACT1_Pin, LED_ACT2_Pin, BOOT_Pin> GpioInit;

/// GPIO Pin connected to the TWAI (CAN) Transceiver RX pin.
// ADC2_CHANNEL_0
static constexpr gpio_num_t CONFIG_TWAI_RX_PIN = GPIO_NUM_4;

/// GPIO Pin connected to the TWAI (CAN) Transceiver TX pin.
static constexpr gpio_num_t CONFIG_TWAI_TX_PIN = GPIO_NUM_5;

/// GPIO Pin used for I2C SDA.
#ifdef CONFIG_T7S3
static constexpr gpio_num_t CONFIG_SDA_PIN = GPIO_NUM_40;
#else
static constexpr gpio_num_t CONFIG_SDA_PIN = GPIO_NUM_2;
#endif
/// GPIO Pin used for I2C SCL.
static constexpr gpio_num_t CONFIG_SCL_PIN = GPIO_NUM_3;

#define PWMCHIP_ADDRESS1 0x40


#endif // __HARDWARE_HXX

