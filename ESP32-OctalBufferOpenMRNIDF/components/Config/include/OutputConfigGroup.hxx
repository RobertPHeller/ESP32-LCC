// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Feb 5 21:56:19 2023
//  Last Modified : <230206.1412>
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

#ifndef __OUTPUTCONFIGGROUP_HXX
#define __OUTPUTCONFIGGROUP_HXX

#include "openlcb/ConfigRepresentation.hxx"

#define OUTPUTCOUNT 8

static const char outputSelectMap[] = 
    "<relation><property>0</property><value>Unused</value></relation>"

    "<relation><property>1</property><value>Output1</value></relation>"
    "<relation><property>2</property><value>Output2</value></relation>"
    "<relation><property>3</property><value>Output3</value></relation>"
    "<relation><property>4</property><value>Output4</value></relation>"
    "<relation><property>5</property><value>Output5</value></relation>"
    "<relation><property>6</property><value>Output6</value></relation>"
    "<relation><property>7</property><value>Output7</value></relation>"
    "<relation><property>8</property><value>Output8</value></relation>";

static const char modeSelectMap[] = 
"<relation><property>0</property><value>On</value></relation>"
"<relation><property>1</property><value>Off</value></relation>"
"<relation><property>2</property><value>Fade On</value></relation>"
"<relation><property>3</property><value>Fade Off</value></relation>"
"<relation><property>4</property><value>Flicker</value></relation>";

CDI_GROUP(OutputConfig);
CDI_GROUP_ENTRY(selection, openlcb::Uint8ConfigEntry,
                Name("Output Selection"), MapValues(outputSelectMap),
                Default(0));
CDI_GROUP_ENTRY(mode, openlcb::Uint8ConfigEntry,
                Name("Output Mode"), MapValues(modeSelectMap),
                Default(0));
CDI_GROUP_ENTRY(brightness, openlcb::Uint16ConfigEntry,
                Name("Output brightness, hundreths of a percent (0 to 10000)"),
                Min(0), Max(10000), Default(5000));
CDI_GROUP_END();

using OutputConfigGroup = openlcb::RepeatedGroup<OutputConfig, OUTPUTCOUNT>;\


#endif // __OUTPUTCONFIGGROUP_HXX

