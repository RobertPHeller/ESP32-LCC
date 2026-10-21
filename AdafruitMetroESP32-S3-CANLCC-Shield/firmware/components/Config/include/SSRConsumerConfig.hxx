// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 12 12:12:38 2023
//  Last Modified : <251120.1358>
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
/// @file SSRConsumerConfig.hxx
/// @author Robert Heller
/// @date Wed Apr 12 12:12:38 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __SSRCONSUMERCONFIG_HXX
#define __SSRCONSUMERCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

/** @page SSRConsumerConfig Solid State Relay Consumer Configuration
 * 
 * There are two SSRs and they have these configuration options:
 * 
 * - Description: This ia an eight character name for the relay, used for
 *   identification purposes.
 * - Event On: This event is consumed to turn the relay on.
 * - Event Off: This event is consumed to turn the relay off.
 */

/// CDI Configuration for a @ref SSRConsumer
CDI_GROUP(SSRConsumerConfig);
/// Allows the user to assign a name for this relay.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<8>, //
                Name("Description"), Description("User name of this relay."));
/// Specifies the event ID to set the output to ON.
CDI_GROUP_ENTRY(
                event_on, openlcb::EventConfigEntry, //
                Name("Event On"),
                Description("Receiving this event ID will turn the relay on."));
/// Specifies the event ID to set the output to OFF.
CDI_GROUP_ENTRY(
                event_off, openlcb::EventConfigEntry, //
                Name("Event Off"),
                Description("Receiving this event ID will turn the relay off."));
CDI_GROUP_END();


#endif // __SSRCONSUMERCONFIG_HXX

