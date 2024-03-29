// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Dec 17 09:29:55 2022
//  Last Modified : <230324.0933>
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
/// @file RuleConfig.hxx
/// @author Robert Heller 
/// @date Sat Dec 17 09:29:55 2022
//////////////////////////////////////////////////////////////////////////////

#ifndef __RULECONFIG_HXX
#define __RULECONFIG_HXX
#define RULESCOUNT 8

#include "openlcb/ConfigRepresentation.hxx"

#include "LampConfig.hxx"

static const char RuleNamesMap[] =
"<relation><property>0</property><value>0-Stop</value></relation>"
"<relation><property>1</property><value>1-Take Siding</value></relation>"
"<relation><property>2</property><value>2-Stop Orders</value></relation>"
"<relation><property>3</property><value>3-Stop Procede</value></relation>"
"<relation><property>4</property><value>4-Restricting</value></relation>"
"<relation><property>5</property><value>5-Permissive</value></relation>"
"<relation><property>6</property><value>6-Slow-Approach</value></relation>"
"<relation><property>7</property><value>7-Slow</value></relation>"
"<relation><property>8</property><value>8-Slow-Medium</value></relation>"
"<relation><property>9</property><value>9-Slow-Limited</value></relation>"
"<relation><property>10</property><value>10-Slow-Clear</value></relation>"
"<relation><property>11</property><value>11-Medium-Approach</value></relation>"
"<relation><property>12</property><value>12-Medium-Slow</value></relation>"
"<relation><property>13</property><value>13-Medium</value></relation>"
"<relation><property>14</property><value>14-Medium-Clear</value></relation>"
"<relation><property>15</property><value>15-Medium-Limited</value></relation>"
"<relation><property>16</property><value>16-Limited-Approach</value></relation>"
"<relation><property>17</property><value>17-Limited-Slow</value></relation>"
"<relation><property>18</property><value>18-Limited-Medium</value></relation>"
"<relation><property>19</property><value>19-Limited</value></relation>"
"<relation><property>20</property><value>20-Limited-Clear</value></relation>"
"<relation><property>21</property><value>21-Approach</value></relation>"
"<relation><property>22</property><value>22-Advance-Approach</value></relation>"
"<relation><property>23</property><value>23-Approach-Slow</value></relation>"
"<relation><property>24</property><value>24-Advance-Approach-Slow</value></relation>"
"<relation><property>25</property><value>25-Approach-Medium</value></relation>"
"<relation><property>26</property><value>26-Advance-Approach-Medium</value></relation>"
"<relation><property>27</property><value>27-Approach-Limited</value></relation>"
"<relation><property>28</property><value>28-Advance-Approach-Limited</value></relation>"
"<relation><property>29</property><value>29-Clear</value></relation>"
"<relation><property>30</property><value>30-Cab Speed</value></relation>"
"<relation><property>31</property><value>31-Dark</value></relation>";

#ifdef EFFECTS
static const char EffectsMap[] = 
"<relation><property>0</property><value>None</value></relation>"
"<relation><property>1</property><value>Transition down</value></relation>"
"<relation><property>2</property><value>H2 Red Flash</value></relation>"
"<relation><property>3</property><value>Strobe</value></relation>";
#endif

/// CDI Configuration for a @ref Rule
CDI_GROUP(RuleConfig);
CDI_GROUP_ENTRY(name,openlcb::Uint8ConfigEntry,Name("Name"),
                Default(0),MapValues(RuleNamesMap));
CDI_GROUP_ENTRY(speed,openlcb::Uint8ConfigEntry,
                Name("Track Speed (on approach to signal)"),
                Default(0),MapValues(TrackSpeedMap));
CDI_GROUP_ENTRY(eventsets,openlcb::EventConfigEntry,
                Name("(C) Event to Set Aspect. Note: Aspects are cleared automatically by the logic."));
CDI_GROUP_ENTRY(eventset,openlcb::EventConfigEntry,
                Name("(P) Send this event when the Aspect is set."));
CDI_GROUP_ENTRY(eventclear,openlcb::EventConfigEntry,
                Name("(P) Send this event when the Aspect clears."));
CDI_GROUP_ENTRY(lamps,LampGroup,Name("Appearance"),
                Description("Individual Aspect Lamps"),
                RepName("Lamp"));
#ifdef EFFECTS
CDI_GROUP_ENTRY(effects,openlcb::Uint8ConfigEntry,
                Name("Appearance Effects"),Default(0),
                MapValues(EffectsMap));
CDI_GROUP_ENTRY(effectslamp,openlcb::Uint8ConfigEntry,
                Name("Effects Lamp"),Default(0),
                MapValues(LampSelectMap));
#endif
CDI_GROUP_END();

using RulesGroup = openlcb::RepeatedGroup<RuleConfig, RULESCOUNT>;



#endif // __RULECONFIG_HXX

