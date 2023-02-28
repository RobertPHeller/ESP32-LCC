// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Feb 14 09:30:08 2023
//  Last Modified : <230214.1031>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
//			51 Locke Hill Road
//			Wendell, MA 01379-9728
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVOTURNOUTCONFIG_HXX
#define __SERVOTURNOUTCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

CDI_GROUP(ServoTurnoutConfig);
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, Name("Description"),
                Description("User name of this turnout."));
CDI_GROUP_ENTRY(event_normal, openlcb::EventConfigEntry, //
    Name("Normal Event"),
    Description("Receiving this event ID will rotate the servo to its normal "
                "configured point."));
CDI_GROUP_ENTRY(event_reversed, openlcb::EventConfigEntry, //
    Name("Reversed Event"),
    Description("Receiving this event ID will rotate the servo to its reversed "
                "configured point."));
#define SERVO_DESCRIPTION_SUFFIX                                               \
    "stop point of the servo, as a percentage: generally 0-100. "              \
    "May be under/over-driven by setting a percentage value "                  \
    "of -99 to 200, respectively."
CDI_GROUP_ENTRY(servo_normal_percent, openlcb::Int16ConfigEntry, Default(0), Min(-99),
    Max(200), Name("Servo Normal Stop Point Percentage"),
    Description("Normal-end " SERVO_DESCRIPTION_SUFFIX));
CDI_GROUP_ENTRY(servo_reversed_percent, openlcb::Int16ConfigEntry, Default(100), Min(-99),
    Max(200), Name("Servo Reversed Stop Point Percentage"),
    Description("Reversed-end " SERVO_DESCRIPTION_SUFFIX));
/// Specifies the event ID to set the veto to ON.
CDI_GROUP_ENTRY(
    veto_on, openlcb::EventConfigEntry, //
    Name("Veto On"),
    Description("Receiving this event ID will lock the turnout."));
/// Specifies the event ID to set the output to OFF.
CDI_GROUP_ENTRY(
    veto_off, openlcb::EventConfigEntry, //
    Name("Veto Off"),
    Description("Receiving this event ID will unlock the turnout."));
CDI_GROUP_END(); // ServoTurnoutConfig


#endif // __SERVOTURNOUTCONFIG_HXX

