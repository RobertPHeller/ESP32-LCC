// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 17 09:40:58 2024
//  Last Modified : <251129.2010>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
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
/// @file cdi.hxx
/// @author Robert Heller
/// @date Wed Apr 17 09:40:58 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __CDI_HXX
#define __CDI_HXX
#include "sdkconfig.h"
#include <openlcb/ConfigRepresentation.hxx>
#include "openlcb/ConfiguredConsumer.hxx"
#include "openlcb/ConfiguredProducer.hxx"
#include "openlcb/MemoryConfig.hxx"
#include "NodeIdConfigurationGroup.hxx"
#include "freertos_drivers/esp32/Esp32WiFiConfiguration.hxx"
#include "WiFiConfigurationGroup.hxx"
#include "FunctionConfig.hxx"

using FunctionConsumers = openlcb::RepeatedGroup<FunctionConsumerConfig, NUM_FUNCTIONS>;

#include "Revision.hxxout"

namespace AtlasLightBoardWiFiLCCTraction
{
/// Defines the main segment in the configuration CDI. This is laid out at
/// origin 128 to give space for the ACDI user data at the beginning.
CDI_GROUP(IoBoard, Segment(openlcb::MemoryConfigDefs::SPACE_CONFIG),
          Offset(128));
/// Each entry declares the name of the current entry, then the type and then
/// optional arguments list.
CDI_GROUP_ENTRY(internal_config, openlcb::InternalConfigData);
CDI_GROUP_ENTRY(functions,FunctionConsumers,Name("Functions"),
                RepName("Function"),
                Description("Functions: headlights, etc."));
#ifdef CONFIG_ESP32_WIFI_ENABLED
CDI_GROUP_ENTRY(olbcwifi, openmrn_arduino::WiFiConfiguration, Name("OLBC WiFi Configuration"));
#endif
CDI_GROUP_END();

/// This segment is only needed temporarily until there is program code to set
/// the ACDI user data version byte.
CDI_GROUP(VersionSeg, Segment(openlcb::MemoryConfigDefs::SPACE_CONFIG),
          Name("Version information"));
CDI_GROUP_ENTRY(acdi_user_version, openlcb::Uint8ConfigEntry,
                Name("ACDI User Data version"), Description("Set to 2 and do not change."));
CDI_GROUP_ENTRY(buildrevisions,BuildRevisions);
CDI_GROUP_END();

/// The main structure of the CDI. ConfigDef is the symbol we use in main.cxx
/// to refer to the configuration defined here.
CDI_GROUP(ConfigDef, MainCdi());
/// Adds the <identification> tag with the values from SNIP_STATIC_DATA above.
CDI_GROUP_ENTRY(ident, openlcb::Identification);
/// Adds an <acdi> tag.
CDI_GROUP_ENTRY(acdi, openlcb::Acdi);
/// Adds a segment for changing the values in the ACDI user-defined
/// space. UserInfoSegment is defined in the system header.
CDI_GROUP_ENTRY(userinfo, openlcb::UserInfoSegment, Name("User Info"));
/// Adds the main configuration segment.
CDI_GROUP_ENTRY(seg, IoBoard, Name("Board Configuration"));
CDI_GROUP_ENTRY(node, nvsmanager::NodeIdConfig, Name("Node ID"));
#if defined(CONFIG_ESP32_WIFI_ENABLED)
CDI_GROUP_ENTRY(wifi, nvsmanager::WiFiConfiguration, Name("WiFi Configuration"));
#endif
/// Adds the versioning segment.
CDI_GROUP_ENTRY(version, VersionSeg);
CDI_GROUP_END();

};

#endif // __CDI_HXX

