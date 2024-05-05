// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Fri Dec 16 12:40:48 2022
//  Last Modified : <240505.1619>
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
/// @file NodeIdConfigurationGroup.hxx
/// @author Robert Heller 
/// @date Fri Dec 16 12:40:48 2022
//////////////////////////////////////////////////////////////////////////////

#ifndef __NODEIDCONFIGURATIONGROUP_HXX
#define __NODEIDCONFIGURATIONGROUP_HXX
#include <openlcb/ConfigRepresentation.hxx>

#include "sdkconfig.h"

/** @page NodeIdConfig Node id configuration
 * 
 * This is the identifier to use for this device. NOTE: Changing this value 
 * will force a factory reset.
 * 
 * The initial default value is a placeholder value and should be changed
 * the first time the node is powered up.
 * 
 * A node id range can be acquired at 
 * https://registry.openlcb.org/requestuniqueidrange#new_tab
 * 
 * @section NodeIdOpts Configuration Options
 * 
 * There is one configuration option.  It is the string representation of the
 * node id, in the form xx.xx.xx.xx.xx.xx, where each xx is a 2 digit hex
 * number representing one 8-bit byte (00 to ff).
 * 
 * Updating this option will cause the node to reboot with a factory reset
 * configuration (except for the node id).  The node id is stored in a separate
 * persistent storage area.
 */

namespace nvsmanager
{

CDI_GROUP(NodeIdConfig, Segment(CONFIG_OLCB_NODEID_MEMORY_SPACE_ID),
          Offset(CONFIG_OLCB_NODEID_MEMORY_SPACE_OFFSET));
CDI_GROUP_ENTRY(node_id, openlcb::StringConfigEntry<32>, Name("Node ID"),
                Description(
                            R"!^!(Identifier to use for this device.
NOTE: Changing this value will force a factory reset.)!^!"))
CDI_GROUP_END();

} // namespace nvsmanager


#endif // __NODEIDCONFIGURATIONGROUP_HXX

