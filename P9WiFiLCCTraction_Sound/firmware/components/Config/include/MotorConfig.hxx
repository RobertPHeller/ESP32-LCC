// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-30 08:19:28
//  Last Modified : <260426.0627>
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
/// @file MotorConfig.hxx
/// @author Robert Heller
/// @date 2025-11-30 08:19:28
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __MOTORCONFIG_HXX
#define __MOTORCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

static const char SpeedMode[] =
"<relation><property>0</property><value>Basic</value></relation>"
"<relation><property>1</property><value>Table</value></relation>";


CDI_GROUP(basicConfig);
CDI_GROUP_ENTRY(vstart,openlcb::Uint8ConfigEntry, Name("VStart"),
                Description("Starting value"),Min(0),Max(255),Default(0),
                Hints("<slider/>"));
CDI_GROUP_ENTRY(vmid,openlcb::Uint8ConfigEntry, Name("VMid"),
                Description("Middle value"),Min(0),Max(255),Default(127),
                Hints("<slider/>"));
CDI_GROUP_ENTRY(vhigh,openlcb::Uint8ConfigEntry, Name("VHigh"),
                Description("High value"),Min(0),Max(255),Default(255),
                Hints("<slider/>"));
CDI_GROUP_END();

CDI_GROUP(tableConfig);
CDI_GROUP_ENTRY(bar0,openlcb::Uint8ConfigEntry, Default(0),Min(0),Max(255),Name("bar0"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar1,openlcb::Uint8ConfigEntry, Default(9),Min(0),Max(255),Name("bar1"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar2,openlcb::Uint8ConfigEntry, Default(19),Min(0),Max(255),Name("bar2"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar3,openlcb::Uint8ConfigEntry, Default(28),Min(0),Max(255),Name("bar3"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar4,openlcb::Uint8ConfigEntry, Default(38),Min(0),Max(255),Name("bar4"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar5,openlcb::Uint8ConfigEntry, Default(47),Min(0),Max(255),Name("bar5"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar6,openlcb::Uint8ConfigEntry, Default(57),Min(0),Max(255),Name("bar6"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar7,openlcb::Uint8ConfigEntry, Default(66),Min(0),Max(255),Name("bar7"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar8,openlcb::Uint8ConfigEntry, Default(76),Min(0),Max(255),Name("bar8"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar9,openlcb::Uint8ConfigEntry, Default(85),Min(0),Max(255),Name("bar9"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar10,openlcb::Uint8ConfigEntry, Default(94),Min(0),Max(255),Name("bar10"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar11,openlcb::Uint8ConfigEntry, Default(104),Min(0),Max(255),Name("bar11"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar12,openlcb::Uint8ConfigEntry, Default(113),Min(0),Max(255),Name("bar12"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar13,openlcb::Uint8ConfigEntry, Default(123),Min(0),Max(255),Name("bar13"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar14,openlcb::Uint8ConfigEntry, Default(132),Min(0),Max(255),Name("bar14"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar15,openlcb::Uint8ConfigEntry, Default(142),Min(0),Max(255),Name("bar15"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar16,openlcb::Uint8ConfigEntry, Default(151),Min(0),Max(255),Name("bar16"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar17,openlcb::Uint8ConfigEntry, Default(161),Min(0),Max(255),Name("bar17"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar18,openlcb::Uint8ConfigEntry, Default(170),Min(0),Max(255),Name("bar18"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar19,openlcb::Uint8ConfigEntry, Default(179),Min(0),Max(255),Name("bar19"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar20,openlcb::Uint8ConfigEntry, Default(189),Min(0),Max(255),Name("bar20"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar21,openlcb::Uint8ConfigEntry, Default(198),Min(0),Max(255),Name("bar21"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar22,openlcb::Uint8ConfigEntry, Default(208),Min(0),Max(255),Name("bar22"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar23,openlcb::Uint8ConfigEntry, Default(217),Min(0),Max(255),Name("bar23"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar24,openlcb::Uint8ConfigEntry, Default(227),Min(0),Max(255),Name("bar24"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar25,openlcb::Uint8ConfigEntry, Default(236),Min(0),Max(255),Name("bar25"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar26,openlcb::Uint8ConfigEntry, Default(246),Min(0),Max(255),Name("bar26"),Hints("<slider/>"));
CDI_GROUP_ENTRY(bar27,openlcb::Uint8ConfigEntry, Default(255),Min(0),Max(255),Name("bar27"),Hints("<slider/>"));
CDI_GROUP_END();

static const char DirectionMode[] =
"<relation><property>0</property><value>Normal</value></relation>"
"<relation><property>1</property><value>Reversed</value></relation>";

/** @page MotorControl Motor control Configuration.
 * @arg pwm_frequency 
 * Specifies what frequency the motor should be driven at. Typical values are 
 * in the 3000-20000 range.
 * @arg direction_mode
 * Specifies where the motor is wired for forward or reverse running.
 * @arg speed_mode
 * Specifies weither to use the basic speed mode, using VStart, VMid, and 
 * VHigh or to use a 28 element speed table.
 * @arg basic
 * Includes three speed points, vstart, vmid, and vmax, which are fractions 
 * of full drive voltage, in 255'ths.
 * @arg table
 * Includes 28 speed points, which are fractions of full drive voltage, in 
 * 255'ths.
 */

CDI_GROUP(MotorControl, Name("Motor control"));
CDI_GROUP_ENTRY(pwm_frequency, openlcb::Uint16ConfigEntry, Name("PWM frequency"),
                Description("Specifies what frequency the motor should be driven at. "
                            "Typical values are in the 3000-15000 range."),
                Min(3000), Max(15000), Default(5000));
CDI_GROUP_ENTRY(direction_mode, openlcb::Uint8ConfigEntry,
                Name("Direction Mode"),
                Description("Specifies the direction mode, normal or reversed."),
                Min(0), Max(1), Default(0));
CDI_GROUP_ENTRY(speed_mode, openlcb::Uint8ConfigEntry, 
                Name("Speed Mode"),
                Description("Selects which speed mode to use:\n"
                            "Basic, using VStart, VMid, and VHigh\n"
                            "Table, use a table"),
                Hints("<radiobutton/>"),
                Min(0), Max(1), Default(0),MapValues(SpeedMode));
CDI_GROUP_ENTRY(basic,basicConfig, Name("Basic Speed Mode"));
CDI_GROUP_ENTRY(table,tableConfig,Name("Speed Table"));
CDI_GROUP_END();



#endif // __MOTORCONFIG_HXX
