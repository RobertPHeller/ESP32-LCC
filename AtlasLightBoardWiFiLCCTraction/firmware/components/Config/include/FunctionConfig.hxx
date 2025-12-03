// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-29 19:50:58
//  Last Modified : <251202.1956>
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
/// @file FunctionConfig.hxx
/// @author Robert Heller
/// @date 2025-11-29 19:50:58
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __FUNCTIONCONFIG_HXX
#define __FUNCTIONCONFIG_HXX

/** @page FunctionConfig Function Config
 * There are six function outputs, each of which has these configuration options:
 * 
 * - Function Steady or Blink Phase (A-B): This defines the phase of
 *   the function output.  The options are Steady on or 
 *   blinking, which can be Slow, Medium, or Fast, with either phase A or B.  
 *   The phase are opposite each other: B is off when A is on, and A is off 
 *   when B is on.
 * - Brightness percent, 1 to 100: This defines how bright the light, from 1
 *   (very dim) to 100 (maximum possible brightness). default 50.
 */

#include "openlcb/ConfigRepresentation.hxx"

static const char FunctionConsumerPhaseMap[] =
"<relation><property>1</property><value>Steady</value></relation>"
"<relation><property>2</property><value>A - Slow</value></relation>"
"<relation><property>3</property><value>A - Medium</value></relation>"
"<relation><property>4</property><value>A - Fast</value></relation>"

"<relation><property>5</property><value>B - Slow</value></relation>"
"<relation><property>6</property><value>B - Medium</value></relation>"
"<relation><property>7</property><value>B - Fast</value></relation>";

/// CDI Configuration for a @ref FunctionConsumer
CDI_GROUP(FunctionConsumerConfig);
CDI_GROUP_ENTRY(phase, openlcb::Uint8ConfigEntry,
                Name("Function Steady or Blink Phase (A-B)"),
                MapValues(FunctionConsumerPhaseMap),Default(0));
CDI_GROUP_ENTRY(brightness, openlcb::Uint8ConfigEntry, 
                Name("Brightness percent, 1 to 100"),
                Min(1), Max(100), Default(50));
CDI_GROUP_END();

#define NUM_FUNCTIONS 6

using FunctionConsumers = openlcb::RepeatedGroup<FunctionConsumerConfig, NUM_FUNCTIONS>;

#endif // __FUNCTIONCONFIG_HXX
