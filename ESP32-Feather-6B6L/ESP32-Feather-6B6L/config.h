// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Fri Dec 13 12:48:05 2024
//  Last Modified : <241215.1355>
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
/// @file config.h
/// @author Robert Heller
/// @date Fri Dec 13 12:48:05 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONFIG_H
#define __CONFIG_H

#include "openlcb/ConfigRepresentation.hxx"
#include "openlcb/MemoryConfig.hxx"

#include "LEDConfig.h"
#include "ButtonConfig.h"

#include "freertos_drivers/esp32/Esp32WiFiConfiguration.hxx"

// catch invalid configuration at compile time
#if !defined(USE_TWAI) && !defined(USE_WIFI)
#error "Invalid configuration detected, USE_TWAI or USE_WIFI must be defined."
#endif
namespace openlcb
{

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
extern const SimpleNodeStaticValues SNIP_STATIC_DATA = {
    4,
    "OpenMRN",
#if defined(USE_WIFI) && !defined(USE_TWAI)
    "6B6L (WiFi)",
#elif defined(USE_TWAI) && !defined(USE_WIFI)
    "6B6L (CAN)",
#elif defined(USE_TWAI) && defined(USE_WIFI)
    "6B6L (WiFi/CAN)",
#else
    "6B6L",
#endif
    "ESP32-S3 Feather", //ARDUINO_VARIANT,
    "1.00"};

constexpr uint8_t NUM_LEDS = 8;
constexpr uint8_t NUM_BUTTONS = 6;

/// Declares a repeated group of a given base group and number of repeats. The
/// ProducerConfig and ConsumerConfig groups represent the configuration layout
/// needed by the ConfiguredProducer and ConfiguredConsumer classes, and come
/// from their respective hxx file.
using AllLEDs = RepeatedGroup<LEDConfig, NUM_LEDS>;
using AllButtons = RepeatedGroup<ButtonConfig, NUM_BUTTONS>;

/// Modify this value every time the EEPROM needs to be cleared on the node
/// after an update.
static constexpr uint16_t CANONICAL_VERSION = 0x100b;

/// Defines the main segment in the configuration CDI. This is laid out at
/// origin 128 to give space for the ACDI user data at the beginning.
CDI_GROUP(IoBoardSegment, Segment(MemoryConfigDefs::SPACE_CONFIG), Offset(128));
/// Each entry declares the name of the current entry, then the type and then
/// optional arguments list.
CDI_GROUP_ENTRY(internal_config, InternalConfigData);
CDI_GROUP_ENTRY(leds, AllLEDs, Name("LEDs"), RepName("LED"))
CDI_GROUP_ENTRY(buttons, AllButtons, Name("Buttons"), RepName("Button"));
#if defined(USE_WIFI)
CDI_GROUP_ENTRY(wifi, WiFiConfiguration, Name("WiFi Configuration"));
#endif
CDI_GROUP_END();

/// The main structure of the CDI. ConfigDef is the symbol we use in main.cxx
/// to refer to the configuration defined here.
CDI_GROUP(ConfigDef, MainCdi());
/// Adds the <identification> tag with the values from SNIP_STATIC_DATA above.
CDI_GROUP_ENTRY(ident, Identification);
/// Adds an <acdi> tag.
CDI_GROUP_ENTRY(acdi, Acdi);
/// Adds a segment for changing the values in the ACDI user-defined
/// space. UserInfoSegment is defined in the system header.
CDI_GROUP_ENTRY(userinfo, UserInfoSegment, Name("User Info"));
/// Adds the main configuration segment.
CDI_GROUP_ENTRY(seg, IoBoardSegment, Name("Settings"));
CDI_GROUP_END();

} // namespace openlcb



#endif // __CONFIG_H

