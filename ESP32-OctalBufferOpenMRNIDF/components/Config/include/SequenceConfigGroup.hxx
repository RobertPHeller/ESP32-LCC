// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Feb 5 21:19:52 2023
//  Last Modified : <230216.1413>
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

#ifndef __SEQUENCECONFIGGROUP_HXX
#define __SEQUENCECONFIGGROUP_HXX

#include "openlcb/ConfigRepresentation.hxx"
#include "StepConfigGroup.hxx"

#define SEQUENCECOUNT 8

static const char YesNoMap[] = 
"<relation><property>0</property><value>No</value></relation>"
"<relation><property>1</property><value>Yes</value></relation>";

/// CDI Configuration for a @ref Sequence
CDI_GROUP(SequenceConfig);
CDI_GROUP_ENTRY(name, openlcb::StringConfigEntry<32>,
                Name("Sequence Name"));
CDI_GROUP_ENTRY(enabled, openlcb::Uint8ConfigEntry,
                Name("Enabled?"),Description("Sequence Enabled"),
                Default(0),MapValues(YesNoMap));
CDI_GROUP_ENTRY(start, openlcb::EventConfigEntry,
                Name("(C) Event to start the sequence"));
CDI_GROUP_ENTRY(stop, openlcb::EventConfigEntry,
                Name("(C) Event to stop the sequence"));
CDI_GROUP_ENTRY(steps,StepsGroup,Name("Steps"),RepName("Step"));
CDI_GROUP_END();


#endif // __SEQUENCECONFIGGROUP_HXX

