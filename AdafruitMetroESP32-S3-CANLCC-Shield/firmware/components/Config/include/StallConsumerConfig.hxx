// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 12 12:12:30 2023
//  Last Modified : <251120.1401>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
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
/// @file StallConsumerConfig.hxx
/// @author Robert Heller
/// @date Wed Apr 12 12:12:30 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __STALLCONSUMERCONFIG_HXX
#define __STALLCONSUMERCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

/** @page StallConsumerConfig Stall Motor Consumer Configuration
 * 
 * There are two stall motor drivers.  They have these configuration options:
 * 
 * - Description: This is an eight character name for the stall motor.
 * - Event Up: This Event is consumed to raise the gate.
 * - Event Down: This Event is consumed to lower the gate.
 */

/// CDI Configuration for a @ref StallConsumer
CDI_GROUP(StallConsumerConfig);
/// Allows the user to assign a name for this output.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<8>, //
                Name("Description"), Description("User name of this output."));
/// Specifies the event ID to set the output to UP.
CDI_GROUP_ENTRY(
    event_up, openlcb::EventConfigEntry, //
    Name("Event Up"),
    Description("Receiving this event ID will raise the gate."));            
/// Specifies the event ID to set the output to DOWN.
CDI_GROUP_ENTRY(
    event_down, openlcb::EventConfigEntry, //
    Name("Event Down"),
    Description("Receiving this event ID will lower the gate."));            
CDI_GROUP_END();

#endif // __STALLCONSUMERCONFIG_HXX

