// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Oct 20 14:54:30 2026
//  Last Modified : <261020.1458>
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

#ifndef __AZATRAXRIR4CROSSINGCONFIG_HXX
#define __AZATRAXRIR4CROSSINGCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"
/** @page AzatraxRIR4Crossing Azatrax RIR4 Crossing Configuration
 * 
 * Configured Producer for Azatrax RIR4 being used as a grade crossing
 * (railroad and road level crossing).
 * 
 * The Azatrax RIR4 Crossing Configuration has these configuration options:
 * 
 * - Description (16 char string) User name of this Azatrax RIR4 Crossing.
 *   This is just a name for identifing purposes.
 * - Activated Event Produced (Event ID) (P) This event is produced when 
 *   the crossing is "activated" -- a train is aproaching the crossing. This
 *   event can be used to activate crossing protections: lowering gates
 *   (barriers), turn on flashers, and turn on the bell.
 * - Deactivated Event Produced (Event ID) (P) This event is produced when
 *   the crossing is "deactivated" -- the train has cleared the crossing.
 *   This event can be used to deactivate crossing protections: raising
 *   gates (barriers), turn off flashers, and turn off the bell.
 */



/// CDI Configuration for a @ref AzatraxRIR4Crossing
CDI_GROUP(AzatraxRIR4CrossingConfig);
/// Allows the user to assign a name for this unit
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, //
                Name("Description"),
                Description("User name of this grade crossing."));
/// Event produced (sent) when the the grade crossing is activated.
CDI_GROUP_ENTRY(activated, openlcb::EventConfigEntry,
                Name("Activated"),
                Description("(P) This event is produced when the grade crossing is activated."));
/// Event produced (sent) when the the grade crossing is deactivated.
CDI_GROUP_ENTRY(deactivated, openlcb::EventConfigEntry,
                Name("Deactivated"),
                Description("(P) This event is produced when the grade crossing is deactivated."));
CDI_GROUP_END();



#endif // __AZATRAXRIR4CROSSINGCONFIG_HXX

