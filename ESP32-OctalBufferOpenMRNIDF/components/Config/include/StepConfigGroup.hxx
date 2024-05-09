// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Feb 5 21:41:05 2023
//  Last Modified : <240509.1542>
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

#ifndef __STEPCONFIGGROUP_HXX
#define __STEPCONFIGGROUP_HXX

#define STEPSCOUNT 8

#include "openlcb/ConfigRepresentation.hxx"

#include "OutputConfigGroup.hxx"

static const char NextModeMap[] = 
"<relation><property>0</property><value>Last</value></relation>"
"<relation><property>1</property><value>Next</value></relation>"
"<relation><property>2</property><value>First</value></relation>";

/** @page StepConfig Step configuration
 * @section outputs Appearence
 * This defines the outputs used in this step. See @ref OutputConfig.
 * @section time Step Time (MilliSecs)
 * This how long the sequence pauses at this step.
 * @section next Next step
 * What step to goto when this step ends.
 * - Last This is the last top. No futher steps will be performed.
 * - Next The sequence precedes to the next steo.
 * - First The sequence loops back to the first stop.
 * @section start Event to send when the step starts
 * This event is produced when this step starts.
 * @section end Event to send when the step ends
 * This event is produced when this step finishes.
 */

CDI_GROUP(StepConfig);
CDI_GROUP_ENTRY(outputs,OutputConfigGroup,Name("Appearence"),
                Description("Individual Outputs"),RepName("Output"));
CDI_GROUP_ENTRY(time,openlcb::Uint32ConfigEntry,Default(0),
                Name("Step Time (MilliSecs)"));
CDI_GROUP_ENTRY(next,openlcb::Uint8ConfigEntry,Default(0),
                MapValues(NextModeMap));
CDI_GROUP_ENTRY(start, openlcb::EventConfigEntry,
                Name("(P) Send this event when the step starts"));
CDI_GROUP_ENTRY(end, openlcb::EventConfigEntry,
                Name("(P) Send this event when the step endss"));
CDI_GROUP_END();

using StepsGroup = openlcb::RepeatedGroup<StepConfig, STEPSCOUNT>;

#endif // __STEPCONFIGGROUP_HXX

