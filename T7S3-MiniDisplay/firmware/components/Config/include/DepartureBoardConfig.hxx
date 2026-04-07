// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 6 17:11:44 2026
//  Last Modified : <260406.2054>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2026  Robert Heller D/B/A Deepwoods Software
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

#ifndef __DEPARTUREBOARDCONFIG_HXX
#define __DEPARTUREBOARDCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

static const char YesNo[] = 
"<relation><property>0</property><value>No</value></relation>"
"<relation><property>1</property><value>Yes</value></relation>";

/// CDI Configuration for a @ref DepartureBoard
CDI_GROUP(DepartureBoardConfig);
/// Schedule file
CDI_GROUP_ENTRY(scheduleFile,openlcb::StringConfigEntry<128>,
                Name("Schedule file name"),
                Description("This is the name on the local uSD card OR SPIFS "
                            "filesystem containing the XML description of the "
                            "trains that depart this station."));
CDI_GROUP_ENTRY(fastclock,openlcb::Uint8ConfigEntry,
                Name("Use fast clock?"),
                Description("Use fast clock or real time clock."),
                Min(0), Max(1), Default(0), // No, use Realtime clock
                Hints("<radiobutton/>"),
                MapValues(YesNo));
CDI_GROUP_END();


#endif // __DEPARTUREBOARDCONFIG_HXX

