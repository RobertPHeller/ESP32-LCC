// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Apr 20 09:26:26 2024
//  Last Modified : <240420.2150>
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
/// @file RetailDisplayConfig.hxx
/// @author Robert Heller
/// @date Sat Apr 20 09:26:26 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __RETAILDISPLAYCONFIG_HXX
#define __RETAILDISPLAYCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

static const char CurrencySignsMap[] =
"<relation><property>0</property><value>None</value></relation>"
"<relation><property>1</property><value>Dollar Sign</value></relation>"
"<relation><property>2</property><value>Pound (UK) Sign</value></relation>"
"<relation><property>3</property><value>Euro</value></relation>";

static const char PriceSuffixMap[] =
"<relation><property>0</property><value>None</value></relation>"
"<relation><property>1</property><value>9/10</value></relation>"
"<relation><property>2</property><value>ea.</value></relation>"
"<relation><property>3</property><value>hr.</value></relation>";

static const char ColorMap[] =
"<relation><property>0x0000</property><value>Black</value></relation>"
"<relation><property>0xFFFF</property><value>White</value></relation>"
"<relation><property>0xF800</property><value>Red</value></relation>"
"<relation><property>0x07E0</property><value>Green</value></relation>"
"<relation><property>0x001F</property><value>Blue</value></relation>"
"<relation><property>0x07FF</property><value>Cyan</value></relation>"
"<relation><property>0xF81F</property><value>Magenta</value></relation>"
"<relation><property>0xFFE0</property><value>Yellow</value></relation>"
"<relation><property>0xFC00</property><value>Orange</value></relation>";

CDI_GROUP(PriceConfig);
CDI_GROUP_ENTRY(product,openlcb::StringConfigEntry<8>,
                Name("Product Name"),
                Description("Product name (eg Regular, Diesel, Coffee, etc."));
CDI_GROUP_ENTRY(productColor,openlcb::Uint16ConfigEntry,
                Name("Product Color"),
                Description("Product color"),
                MapValues(ColorMap),Default(0xFFFF)); // White
CDI_GROUP_ENTRY(currency,openlcb::Uint8ConfigEntry,
                Name("Currency sign"),MapValues(CurrencySignsMap),
                Description("Currency Sign to use."),
                Default(1));
CDI_GROUP_ENTRY(price,openlcb::StringConfigEntry<5>,
                Name("Product Price"),
                Description("Product price, including"));
CDI_GROUP_ENTRY(suffix,openlcb::Uint8ConfigEntry,
                Name("Suffix"),MapValues(PriceSuffixMap),
                Description("Suffic added after price."),
                Default(1));
CDI_GROUP_ENTRY(priceColor,openlcb::Uint16ConfigEntry,
                Name("Price Color"),
                Description("Price Color"),
                MapValues(ColorMap),Default(0x07E0)); // Green
CDI_GROUP_END();

#define NUM_PRICES 4
using PriceGroup = openlcb::RepeatedGroup<PriceConfig,NUM_PRICES>;

CDI_GROUP(TODConfig);
CDI_GROUP_ENTRY(onevent,openlcb::EventConfigEntry,Name("Message On Event"),
                Description("(C) Receiving this event ID will turn the message on."));
CDI_GROUP_ENTRY(offevent,openlcb::EventConfigEntry,Name("Message Off Event"),
                Description("(C) Receiving this event ID will turn the message off."));
CDI_GROUP_ENTRY(message,openlcb::StringConfigEntry<32>,
                Name("Message"),Description("The message text to display."));
CDI_GROUP_ENTRY(messageColor,openlcb::Uint16ConfigEntry,
                Name("Message Color"),Description("Message Color"),
                MapValues(ColorMap),Default(0x001F)); // Blue
CDI_GROUP_END();

#define NUM_TOD 4
using TODGroup = openlcb::RepeatedGroup<TODConfig,NUM_TOD>;

static const char DisplayOrientMap[] =
"<relation><property>0</property><value>Landscape</value></relation>"
"<relation><property>1</property><value>Portrait</value></relation>"
"<relation><property>2</property><value>Seascape</value></relation>"
"<relation><property>3</property><value>UpsideDown</value></relation>";

static const char TrueFalseMap[] =
"<relation><property>0</property><value>False</value></relation>"
"<relation><property>1</property><value>True</value></relation>";

/// CDI Configuration for a @ref RetailDisplay.
CDI_GROUP(RetailDisplayConfig);
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<15>, //
                Name("Description"), 
                Description("User name of this retail display."));
CDI_GROUP_ENTRY(orient, openlcb::Uint8ConfigEntry,
                Name("Display Rotation"),
                MapValues(DisplayOrientMap),Default(1),
                Description("Display orientatiom"));
CDI_GROUP_ENTRY(background,openlcb::Uint16ConfigEntry,
                Name("Background Color"),
                Description("Background Color"),
                MapValues(ColorMap),Default(0x0000)); // Black
CDI_GROUP_ENTRY(signon, openlcb::EventConfigEntry,Name("Sign On Event"),
                Description("(C) Receiving this event ID will turn the sign on."));
CDI_GROUP_ENTRY(signoff, openlcb::EventConfigEntry,Name("Sign Off Event"),
                Description("(C) Receiving this event ID will turn the sign off."));
CDI_GROUP_ENTRY(brightness,openlcb::Uint16ConfigEntry,
                Name("Display brightness, hundreths of a percent (0 to 10000)"),
                Min(0), Max(10000), Default(5000));
CDI_GROUP_ENTRY(logofile, openlcb::StringConfigEntry<32>, //
                Name("Store Logo File"),Description("Store logo bitmap file"));
CDI_GROUP_ENTRY(prices,PriceGroup,Description("Price Listing"),Name("Price"),
                RepName("Price"));
CDI_GROUP_ENTRY(mod, openlcb::StringConfigEntry<128>, //
                Name("Message of the Day"),
                Description("Clever comeon message"));
CDI_GROUP_ENTRY(modColor,openlcb::Uint16ConfigEntry,
                Name("Message of the Day Color"),
                Description("Clever comeon message"),
                MapValues(ColorMap),Default(0x07FF)); // Cyan
CDI_GROUP_ENTRY(displayTime, openlcb::Uint8ConfigEntry,
                Name("Display Time"),MapValues(TrueFalseMap),
                Description("Display the time of day"),Default(0));
CDI_GROUP_ENTRY(timeColor,openlcb::Uint16ConfigEntry,
                Name("Clock color"),Description("Color of the clock."),
                MapValues(ColorMap),Default(0xF800)); // Red
CDI_GROUP_ENTRY(timedofdaymessages,TODGroup,
                Description("Time Of Day Messages"),Name("TOD Message"),
                RepName("TOD Message"));
                
CDI_GROUP_END();


#endif // __RETAILDISPLAYCONFIG_HXX

