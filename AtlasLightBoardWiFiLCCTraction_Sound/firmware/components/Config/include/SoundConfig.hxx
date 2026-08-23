// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Aug 19 16:00:52 2026
//  Last Modified : <260821.1126>
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

#ifndef __SOUNDCONFIG_HXX
#define __SOUNDCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx" 

static const char EngineType[] = 
"<relation><property>0</property><value>Disabled</value></relation>"
"<relation><property>1</property><value>EMD576 16-Cyl</value></relation>"
"<relation><property>2</property><value>EMD710g3</value></relation>"
"<relation><property>3</property><value>EMD576 8-Cyl</value></relation>"
"<relation><property>4</property><value>EMD576 12-Cyl</value></relation>"
"<relation><property>5</property><value>EMD645 8-Cyl</value></relation>"
"<relation><property>6</property><value>EMD645 12-Cyl</value></relation>"
"<relation><property>7</property><value>EMD645 16-Cyl</value></relation>"
"<relation><property>8</property><value>EMD645 Turbo 12-Cyl</value></relation>"
"<relation><property>9</property><value>EMD645 Turbo 16-Cyl</value></relation>"
"<relation><property>10</property><value>EMD645 Turbo 20-Cyl</value></relation>"
;

static const char HornType[] = 
"<relation><property>0</property><value>Disabled</value></relation>"
"<relation><property>1</property><value>Leslie RS-3L</value></relation>"
"<relation><property>2</property><value>Nathan AirChime</value></relation>"
;

static const char BellType[] = 
"<relation><property>0</property><value>Disabled</value></relation>"
"<relation><property>1</property><value>Standard</value></relation>"
;

/** @page SoundConfig Sound Configuration
 * @arg engine_sound This is the type of engine sound.
 * @arg horn_sound This is the type of horn sound.
 * @arg bell_type This is the type of bell sound.
 */
CDI_GROUP(SoundConfig, Name("Sound config"))
CDI_GROUP_ENTRY(engine_sound, openlcb::Uint8ConfigEntry,
                Name("Engine Type"),
                Description("Specifies the type of engine"),
                Min(0), Max(10), MapValues(EngineType));
CDI_GROUP_ENTRY(horn_sound, openlcb::Uint8ConfigEntry,
                Name("Horn Type"),
                Description("Specifies the type of horn"),
                Min(0), Max(2), MapValues(HornType));
CDI_GROUP_ENTRY(bell_type, openlcb::Uint8ConfigEntry,
                Name("Bell Type"),
                Description("Specifies the type of bell"),
                Min(0), Max(1), MapValues(BellType));
CDI_GROUP_END();

#endif // __SOUNDCONFIG_HXX

