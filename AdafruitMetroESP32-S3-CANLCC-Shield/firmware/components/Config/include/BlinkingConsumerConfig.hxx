// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Dec 17 09:23:01 2022
//  Last Modified : <251120.1354>
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
/// @file BlinkingConsumerConfig.hxx
/// @author Robert Heller 
/// @date Sat Dec 17 09:23:01 2022 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BLINKINGCONSUMERCONFIG_HXX
#define __BLINKINGCONSUMERCONFIG_HXX

/** @page BlinkingConsumerConfig Blinking Consumer Config
 *
 * There are four signal outputs each of which has these configuration options:
 * 
 * - Blinker Steady, Pulse, or Blink Phase (A-B): This defines the phase of
 *   signal output.  The options are Steady on, a single Pulse, or blinking, 
 *   which can be Slow, Medium, or Fast, with either phase A or B.  The phase
 *   are opposite each other: B is off when A is on, and A is off when B is on.
 * - Pulse width in seconds, 1 to 127: This is only used to the Pulse option
 *   and defined how long the plus in on.
 * - Blinker on: This Event is consumed to turn the output on.
 * - Blinker off: This event is consomed to turn the output off.
 */


#include "openlcb/ConfigRepresentation.hxx"

static const char BlinkingConsumerPhaseMap[] =
    "<relation><property>1</property><value>Steady</value></relation>"

    "<relation><property>3</property><value>Pulse</value></relation>"

    "<relation><property>4</property><value>A - Slow</value></relation>"
    "<relation><property>5</property><value>A - Medium</value></relation>"
    "<relation><property>6</property><value>A - Fast</value></relation>"

    "<relation><property>7</property><value>B - Slow</value></relation>"
    "<relation><property>8</property><value>B - Medium</value></relation>"
    "<relation><property>9</property><value>B - Fast</value></relation>";

/// CDI Configuration for a @ref BlinkingConsumer
CDI_GROUP(BlinkingConsumerConfig);
CDI_GROUP_ENTRY(phase, openlcb::Uint8ConfigEntry,
                Name("Blinker Steady, Pulse, or Blink Phase (A-B)"),
                MapValues(BlinkingConsumerPhaseMap),Default(0));
CDI_GROUP_ENTRY(pulsewidth, openlcb::Uint8ConfigEntry,
                Name("Pulse width in seconds, 1 to 127"),
                Min(1), Max(127), Default(1));
/// This event will be consumed to turn the output on.
CDI_GROUP_ENTRY(
    event_on, openlcb::EventConfigEntry, //
    Name("Blinker on"),
    Description("This event will be consumed to turn the output on."));
/// This event will be consumed to turn the output off.
CDI_GROUP_ENTRY(
    event_off, openlcb::EventConfigEntry, //
    Name("Blinker off"),
    Description("This event will be consumed to turn the output off."));
CDI_GROUP_END();



#endif // __BLINKINGCONSUMERCONFIG_HXX

