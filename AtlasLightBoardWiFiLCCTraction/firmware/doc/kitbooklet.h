// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-29 16:45:46
//  Last Modified : <251202.0912>
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
/// @file kitbooklet.h
/// @author Robert Heller
/// @date 2025-11-29 16:45:46
/// 
///
//////////////////////////////////////////////////////////////////////////////

/** @page 00kitContents Kit Contents
 * This kit just contains the node PCB.
 * @image html AtlasLightBoardWiFiLCCTraction_Top3D_Thumb.png
 * @image latex AtlasLightBoardWiFiLCCTraction_Top3D_Thumb.png width=1in
 * @page 01assembly Assembly
 * The PCB is fully assembled and ready to install.  It is designed to be
 * installed on top of an Atlas motor.  Note the orientation: there is a small
 * "F" near the end meant to be towards the front of the locomotive.
 * @page 02wiring General Wiring Notes
 * The PCB can support up to 6 LED lights, including front and read headlights.
 * There are through hole solder terminals for functions 1 (front headlight)
 * and 2 (rear headlight),  There are surface pads for functions 3 through 6
 * near the front end of the board.  These four functions share a common "C"
 * pad.  All 6 function outputs have on-board load resistors and are designed
 * to directly drive LEDs. See the figure below for how to wire the board.
 * @image html AtlasLightBoardWiFiLCCTraction_Top3D_Annotated.png
 * @image latex AtlasLightBoardWiFiLCCTraction_Top3D_Annotated.png width=5in
 * If the locomotive operates in reverse when you select the forward direction
 * this can be fixed by swapping the motor connections.
 * @page 03initialConfig Initial Configuration
 * Before putting your locomotive on your layout, there are some initial
 * configuration tasks that are needed.
 * 
 * The LCC node id needs to be set and the WiFi credintials need to be set. 
 * This is done using a terminal program and a USB-C cable. Connect a USB-C 
 * cable between the node and a computer. Start the terminal program (the 
 * Arduino IDE Serial Monitor will work), Press the Reset button and when the 
 * message @c "[BootPauseHelper] starting...", press any key. You should get a 
 * @c >>> prompt. At this point you send one of these commands:
 * 
 * - @c N This sets the node id. Follow the N with the node id as 6 pairs of 
 * hexadecimal digits, separated by colons or periods. For example 
 * 05:01:01:01:22:00. You can either get a node id range at 
 * [https://registry.openlcb.org/requestuniqueidrange](https://registry.openlcb.org/requestuniqueidrange)
 * or you can use the DCC address mapping range: 06:01:00:00:xx:yy, where 
 * xx:yy is the DCC address in hex (eg DCC address 1024 would be 
 * 06:01:00:00:04:00).
 * - @c S This sets the WiFi SSID. Follow the S with your WiFi network name.
 * - @c P This sets the WiFi password. Follow the P with your WiFi password.
 * - @c R This exits the boot setup loop and resumes the boot process.
 * 
 * After the node connects to the WiFi access point it will connect to a GC 
 * hub using mDNS to find an available hub. You should either be running the 
 * JMRI LCC hub, running the OpenMRN hub application, or running a hub on a 
 * LCC/DCC command station (like the TCS CS-105). Once the node connects to 
 * the GC Hub it is possible to either just run the locomotive or and use a CDI
 * configuration tool (eg JMRI) to change configuration settings, as described
 * in the following chapters.
 * @page 04OperationNotes Operation Notes
 * In addition to the basic locomotive operations (speed and direction), 
 * there are seven functions.  Function number 0 is a "virtual" output for the
 * headlight.  If it is set to "On", it will turn Function 1 (front headlight)
 * or Function 2 (rear headlight) "On" or "Off" depending on the current
 * locomotive direction.  Functions 1 through 6 can be configured for various
 * effects: Steady on or blinking at one of three rates and two phases.  The
 * brightness can also be adjusted.  Function 1 is normally the front headlight
 * and Function 2 is the rear headlight.  Functions 3 through 6 can be used for
 * any other lights, such as ditch lights, marker lights, or a mars light.
 */
