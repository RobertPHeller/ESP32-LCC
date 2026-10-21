// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Oct 20 14:52:24 2026
//  Last Modified : <261021.1457>
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


#ifndef __AZATRAXRIR4PCCONFIG_HXX
#define __AZATRAXRIR4PCCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"                                     

/** @page AzatraxRIR4PC  Azatrax RIR4 Configuration
 * The Azatrax RIR4 has 4 detectors and 2 stop watches (timers).
 * The detectors are in pairs and each pair has an associated stop watch 
 * timer.  The timers can then be used to time the travel time between the
 * detector pair and that can be used to calculate the speed of the train.
 * 
 * @section detector Detector Configuration
 * @arg Description This is a 16 character description of the detector.
 * @arg Occupied This event (P) is produced when a detector is occupied 
 * (covered for in track, interrupted for across track).
 * @arg Vacant This event (P) is produced when a detector is vacated
 * (uncovered for in track, not interrupted for across track).
 * @arg Threshold This is the Sensor threshold value, 0 to 255.
 * 
 * @section stopwatch Stop Watch (Timer) Configuration
 * @arg Description This is a 16 character description for the timer.
 * @arg Stopped This event (P) is produced when the Stop Watch stops.
 * @arg Left to Right This event (P) is produced when the Stop Watch starts
 * when detector 1 is triggered before detector 2 (Stop Watch 1) or when
 * detector 3 is triggered before detector 4 (Stop Watch 2).
 * @arg Right to Left This event (P) is produced when the Stop Watch starts
 * when detector 2 is triggered before detector 1 (Stop Watch 1) or when
 * detector 4 is triggered before detector 3 (Stop Watch 2).
 * @arg Reset This event (C) is consumed to reset the Stopwatch.
 */

/// CDI Configuration for a @ref AzatraxDector.
CDI_GROUP(AzatraxDetectorConfig);
/// Allows the user to assign a name for this AzatraxDetector.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, //
                Name("Description"), 
                Description("User name of this Detector."));
/// Event produced (sent) when a AzatraxDetector is occupied.
CDI_GROUP_ENTRY(occupied, openlcb::EventConfigEntry,
                Name("Occupied"),
                Description("(P) This event is produced when a detector is occupied."));
/// Event produced (sent) when a AzatraxDetector is vacant.
CDI_GROUP_ENTRY(vacant, openlcb::EventConfigEntry,
                Name("Vacant"),
                Description("(P) This event is produced when a detector is vacant."));
/// Threshold setting.
CDI_GROUP_ENTRY(threshold, openlcb::Uint8ConfigEntry,
                Default(0x18),Name("Threshold"),
                Description("Sensor threshold value, 0-255."));
CDI_GROUP_END();

#define NUM_DETECTORS 4

using AllDetectors = openlcb::RepeatedGroup<AzatraxDetectorConfig, NUM_DETECTORS>;

/// CDI Configuration for a @ref AzatraxStopwatch
CDI_GROUP(AzatraxStopwatchConfig);
/// Allows the user to assign a name for this AzatraxStopwatch.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, //
                Name("Description"),
                Description("User name of this Stopwatch."));
/// Event produced (sent) when a Stopwatch stops.
CDI_GROUP_ENTRY(stopped, openlcb::EventConfigEntry,
                Name("Stopped"),
                Description("(P) This event is produced when a Stopwatch stops."));
/// Event produced (sent) when a Stopwatch is running "left to right" (1=>2 or 3=>4).
CDI_GROUP_ENTRY(leftright, openlcb::EventConfigEntry,
                Name("Left to Right"),
                Description("(P) This event is produced when a Stopwatch starts running when triggered by the lower sensor number (1 or 3)."));
/// Event produced (sent) when a Stopwatch is running "right to left" (2=>1 or 4=>3).
CDI_GROUP_ENTRY(rightleft, openlcb::EventConfigEntry,
                Name("Right to Left"),
                Description("(P) This event is produced when a Stopwatch starts running when triggered by the higher sensor number (2 or 4)."));
/// Event Consumed (received) to reset (stop) the Stopwatch.
CDI_GROUP_ENTRY(reset, openlcb::EventConfigEntry,
                Name("Reset"),
                Description("(C) This event is consumed to reset the Stopwatch."));
CDI_GROUP_END();

#define NUM_STOPWATCH 2

using AllStopwatches = openlcb::RepeatedGroup<AzatraxStopwatchConfig, NUM_STOPWATCH>;

/// CDI Configuration for a @ref AzatraxRIR4.
CDI_GROUP(AzatraxRIR4Config);
/// Detectors (4)
CDI_GROUP_ENTRY(detectors,AllDetectors,Name("Detectors"),RepName("Detector"),
                Description("Azatrax RIR4 Detectors"));
CDI_GROUP_ENTRY(stopwatches,AllStopwatches,Name("Stopwatches"),
                RepName("Stopwatch"),
                Description("Azatrax RIR4 Stopwatches"));
CDI_GROUP_END();



#endif // __AZATRAXRIR4PCCONFIG_HXX

