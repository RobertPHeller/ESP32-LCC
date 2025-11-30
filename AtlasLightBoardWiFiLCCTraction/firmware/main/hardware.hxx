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
//  Last Modified : <251129.1949>
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

#include <freertos_drivers/arduino/DummyGPIO.hxx>
#include <freertos_drivers/esp32/Esp32Gpio.hxx>
#include <os/Gpio.hxx>
#include <utils/GpioInitializer.hxx>

// Motor control (PWM)
GPIO_PIN(MForward,GpioOutputSafeLow,1);
GPIO_PIN(MReverse,GpioOutputSafeLow,2);

// Functions (PWM)
GPIO_PIN(Function1,GpioOutputSafeLow,3);
GPIO_PIN(Function2,GpioOutputSafeLow,4);
GPIO_PIN(Function3,GpioOutputSafeLow,5);
GPIO_PIN(Function4,GpioOutputSafeLow,6);
GPIO_PIN(Function5,GpioOutputSafeLow,7);
GPIO_PIN(Function6,GpioOutputSafeLow,8);

GPIO_PIN(BOOT,GpioInputNP, 0);

// Create an initializer that can initialize all the GPIO pins in one shot
typedef GpioInitializer<MForward_Pin, MReverse_Pin, Function1_Pin, 
                        Function2_Pin, Function3_Pin, Function4_Pin, 
                        Function5_Pin, Function6_Pin, BOOT_Pin> GpioInit;

#endif // __HARDWARE_HXX
