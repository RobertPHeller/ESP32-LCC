// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Dec 17 09:21:55 2022
//  Last Modified : <230323.1441>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2022  Robert Heller D/B/A Deepwoods Software
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
/// @file ButtonConfig.hxx
/// @author Robert Heller
/// @date Sat Dec 17 09:21:55 2022
//////////////////////////////////////////////////////////////////////////////

#ifndef __BUTTONCONFIG_HXX
#define __BUTTONCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"


/// CDI Configuration for a @ref ConfiguredProducer.
CDI_GROUP(ButtonConfig);
/// Allows the user to assign a name for this input.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<15>, //
                Name("Description"), Description("User name of this button."));
/// This event will be produced when the input goes to HIGH.
CDI_GROUP_ENTRY(
    event_released, openlcb::EventConfigEntry, //
    Name("Button Released"),
    Description("This event will be produced when the button is released."));
/// This event will be produced when the input goes to LOW.
CDI_GROUP_ENTRY(
    event_pressed, openlcb::EventConfigEntry, //
    Name("Button Pushed"),
    Description("This event will be produced when the button is pushed."));
CDI_GROUP_END();



#endif // __BUTTONCONFIG_HXX

