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
//  Last Modified : <240505.1529>
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

/** @page retailDiaplayConfig Retail Display Configuration 
 * There can one or two displays (compile time configuration). 
 * The display displays this information from top to bottom:
 * 
 * The logo at the top, then the time (if enabled), then the four product
 * prices, then one of the short one line message, and finally the fixed
 * message of the day message.
 * 
 * Each display has these configuration options:
 * @section description Description
 * This is a user suppplied descriptive name for identifing purposes.
 * @section orient Display Rotation
 * This is the orientation of the display.  Portrait is the display in an 
 * upright position with the connector pins at the bottom. Landscape is the 
 * display with the pins to the right and Seascape is the display with the
 * pins to the left, and UpsideDown is with pins at the top.
 * @section background Background Color
 * The general packground color for the display.
 * @section signon Sign On Event
 * Receiving this event ID will turn the sign on.
 * @section signoff Sign Off Event
 * Receiving this event ID will turn the sign off.
 * @section brightness Display brightness
 * This controls the display's backlight brightness in hundreths of a percent 
 * (0 to 10000).
 * @section logofile Store Logo File
 * This is the name of a BMP file on the uSD card. It can be either an 
 * uncompressed 24bit RGB or a 1bit bitmap.
 * @section prices Prices
 * These are the fuel (or other product) prices.  There is space for 4 
 * products, for example Economy, Regular, Primium, and Diesel.
 * @subsection product Product Name
 * The product name (eg Regular, Diesel, Coffee, etc.).
 * @subsection productColor Product color
 * The color to use for the product name.
 * @subsection currency Currency sign
 * The currency sign to use: None, Dollar, Pound (British), or Euro.
 * @subsection price Product Price
 * The product price.  This is a text field, not a number, so be sure to 
 * include a decimal point.
 * @subsection suffix Suffix
 * A suffix to add: None, 9/10 (typical for US fuel prices), "ea", or "hr".
 * @subsection priceColor Price Color
 * The color to use for the product price.
 * @section mod Message of the Day
 * This is a fixed message displayed at the bottom of the sign.
 * @section modColor Message of the Day Color
 * The color to use for the Message of the Day.
 * @section displayTime Display Time
 * Display the time, yes or no.  A compile time option selects real time or 
 * fast clock time. The time display uses a "seven segment" format, like old
 * digital clocks.
 * @section timeColor Clock color
 * The color to use for the time.
 * @section timedofdaymessages Time Of Day Messages
 * There is a space for short 1-line messages.  One of up to four message can
 * be displayed in response to an event.
 * @subsection onevent Message On Event
 * This event selects this message.
 * @subsection message Message
 * The message text.
 * @subsection messageColor Message Color
 * The message color.
 * 
 */


CDI_GROUP(PriceConfig);
CDI_GROUP_ENTRY(product,openlcb::StringConfigEntry<8>,
                Name("Product Name"),
                Description("Product name (eg Regular, Diesel, Coffee, etc.)"));
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

