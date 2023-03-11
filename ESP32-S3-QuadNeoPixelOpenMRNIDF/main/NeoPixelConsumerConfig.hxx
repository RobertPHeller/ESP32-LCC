// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Mar 11 09:46:54 2023
//  Last Modified : <230311.1031>
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

#ifndef __NEOPIXELCONSUMERCONFIG_HXX
#define __NEOPIXELCONSUMERCONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"

static const char NeoPixelTypeMap[] = 
"<relation><property>0</property><value>RGB</value></relation>"
"<relation><property>1</property><value>RBG</value></relation>"
"<relation><property>2</property><value>GRB</value></relation>"
"<relation><property>3</property><value>GBR</value></relation>"
"<relation><property>4</property><value>BRG</value></relation>"
"<relation><property>5</property><value>BGR</value></relation>"
"<relation><property>6</property><value>WRGB</value></relation>"
"<relation><property>7</property><value>WRBG</value></relation>"
"<relation><property>8</property><value>WGRB</value></relation>"
"<relation><property>9</property><value>WGBR</value></relation>"
"<relation><property>10</property><value>WBRG</value></relation>"
"<relation><property>11</property><value>WBGR</value></relation>"
"<relation><property>12</property><value>RWGB</value></relation>"
"<relation><property>13</property><value>RWBG</value></relation>"
"<relation><property>14</property><value>RGWB</value></relation>"
"<relation><property>15</property><value>RGBW</value></relation>"
"<relation><property>16</property><value>RBWG</value></relation>"
"<relation><property>17</property><value>RBGW</value></relation>"
"<relation><property>18</property><value>GWRB</value></relation>"
"<relation><property>19</property><value>GWBR</value></relation>"
"<relation><property>20</property><value>GRWB</value></relation>"
"<relation><property>21</property><value>GRBW</value></relation>"
"<relation><property>22</property><value>GBWR</value></relation>"
"<relation><property>23</property><value>GBRW</value></relation>"
"<relation><property>24</property><value>BWRG</value></relation>"
"<relation><property>25</property><value>BWGR</value></relation>"
"<relation><property>26</property><value>BRWG</value></relation>"
"<relation><property>27</property><value>BRGW</value></relation>"
"<relation><property>28</property><value>BGWR</value></relation>"
"<relation><property>29</property><value>BGRW</value></relation>"
;

static const char NeoPixelPatternMap[] =
"<relation><property>0</property><value>White Chase</value></relation>"
"<relation><property>1</property><value>Red Chase</value></relation>"
"<relation><property>2</property><value>Green Chase</value></relation>"
"<relation><property>3</property><value>Blue Chase</value></relation>"
"<relation><property>4</property><value>Rainbow Chase</value></relation>"
"<relation><property>5</property><value>Red Wipe</value></relation>"
"<relation><property>6</property><value>Green Wipe</value></relation>"
"<relation><property>7</property><value>Blue Wipe</value></relation>"
"<relation><property>8</property><value>Rainbow</value></relation>";

CDI_GROUP(NeoPixelConsumerConfig);
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, Name("Description"),
                Description("User name of this NeoPixel String."));
CDI_GROUP_ENTRY(event_on, openlcb::EventConfigEntry, //
                Name("On Event"),
                Description("(C) Receiving this event ID will turn on the "
                            "NeoPixel String."));
CDI_GROUP_ENTRY(event_off, openlcb::EventConfigEntry, //
                Name("Off Event"),
                Description("(C) Receiving this event ID will turn off the "
                            "NeoPixel String."));
CDI_GROUP_ENTRY(length, openlcb::Uint8ConfigEntry, Default(0),
                Name("Length"),
                Description("The length of the NeoPixel String."));
CDI_GROUP_ENTRY(type, openlcb::Uint8ConfigEntry, Default(2),
                MapValues(NeoPixelTypeMap),Name("Type"),
                Description("The type of NeoPixel String."));
CDI_GROUP_ENTRY(speed, openlcb::Uint8ConfigEntry, Default(0),
                MapValues("<relation><property>0</property><value>KHZ800</value></relation>"
                          "<relation><property>1</property><value>KHZ400</value></relation>"),
                Name("Speed"),
                Description("The transmission speed of the NeoPixel String."));
CDI_GROUP_ENTRY(pattern, openlcb::Uint8ConfigEntry, Default(0),
                MapValues(NeoPixelPatternMap), Default(0),
                Name("Pattern"),
                Description("The pattern to run."));
CDI_GROUP_END(); // NeoPixelConsumerConfig

#endif // __NEOPIXELCONSUMERCONFIG_HXX

