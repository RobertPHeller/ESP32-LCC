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
//  Last Modified : <251202.1353>
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

/** @page MotorControl Motor control Configuration.
 * There is only one configuration option, @c PWM @c frequency, which 
 * specifies what frequency the motor should be driven at. Typical values are 
 * in the 3000-20000 range.
 */

CDI_GROUP(MotorControl, Name("Motor control"));
CDI_GROUP_ENTRY(pwm_frequency, openlcb::Uint16ConfigEntry, Name("PWM frequency"),
                Description("Specifies what frequency the motor should be driven at. "
                            "Typical values are in the 3000-20000 range."),
                Min(3), Max(50000), Default(13000));
CDI_GROUP_END();



#endif // __MOTORCONFIG_HXX
