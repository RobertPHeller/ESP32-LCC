// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun May 5 12:53:24 2024
//  Last Modified : <240508.1513>
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
/// @file kitbooklet.h
/// @author Robert Heller
/// @date Sun May 5 12:53:24 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __KITBOOKLET_H
#define __KITBOOKLET_H

/** @page 00kitContents Kit Contents
 * This kit contains:
 * -# This booklet.
 * -# The Display node and display PCB
 * @image html ESP32-T7S3-TextDisplaySign_thumb.png
 * @image latex ESP32-T7S3-TextDisplaySign_thumb.png  height=1in 
 * -# 2 2x10 socket headers 
 * @image html 90151-2220_SPL.jpg
 * @image latex 90151-2220_SPL.jpg height=1in
 * -# 2 RJ45 connectors
 * @image html WR-MJ_SPL.jpg 
 * @image latex WR-MJ_SPL.jpg height=1in
 * -# 2 2-position 2.54 pitch screw terminals
 * @image html ITP_538-39773-0002_2.jpg 
 * @image latex ITP_538-39773-0002_2.jpg height=1in
 * -# 1 2x2 2.54 pitch pin header
 * @image html 87227-2.jpg
 * @image latex 87227-2.jpg height=1in
 * -# 2 2x10 2.54 pitch pin headers 
 * @image html ITP_653-XG8W-2031_t.jpg
 * @image latex ITP_653-XG8W-2031_t.jpg height=1in 
 * -# 1 2x5 Shrouded 2.54 pitch pin header
 * @image html 15-47-7610_SPL.jpg
 * @image latex 15-47-7610_SPL.jpg height=1in
 * -# 1 1x10 right angle 2.54 pitch pin header
 * @image html 102974-2_SPL.jpg
 * @image latex 102974-2_SPL.jpg height=1in
 * -# 1 1x10 socket header
 * @image html 90147-1110_SPL.jpg
 * @image latex 90147-1110_SPL.jpg height=1in
 * -# 1 1x10 socket connector
 * @image html 1-86427-1_SPL.jpg
 * @image latex 1-86427-1_SPL.jpg height=1in
 * -# 1 2x5 IDC plug
 * @image html 622-1041LF_DSL.jpg
 * @image latex 622-1041LF_DSL.jpg height=1in 
 * -# 3 feet of 10 conductor ribbon cable
 * -# 1 small piece of strip board
 * @page 01assembly Assembly
 * 
 * 
 * The first step is to separate the node board from the display board.  This
 * is done by cutting the two boards apart. This can be done with a razor saw
 * or a jewelry saw.  Carefully sand the cut edges smooth.  
 * 
 * @image html ESP32-T7S3-TextDisplaySign-cut.png "Cutting the two boards apart"
 * @image latex ESP32-T7S3-TextDisplaySign-cut.png "Cutting the two boards apart" width=5in
 *
 * Assembly is straight forward.  The SMD parts are already soldered,
 * so only the through hole parts need to be soldered to the board.
 * Start with the shortest parts and work towards the tallest. Their are 
 * one 2x2 and two 2x10 headers.  The 2x2 header is for the termination header 
 * and the two 2x10 will go in the T7-S3 board (supplied separately). Note the
 * orientation of the 2x5 shrouded header and the orientation of the screw
 * terminals.
 * 
 * You will probably want to use some sheet styrene to dress up the display 
 * panel. Using textured styrene sheets can be used to simulate brick, stone,
 * or other materials.  There are two options to provide a way to connect the 
 * ribbon cable to the display board.  The small piece of strip board and the
 * single in line header is one option, the other is the free hanging single 
 * in line socket is the other.
 * 
 * @image html DisplayBoard.png "Using styrene sheet (3/32in/2.4mm) to dress up the display panels."
 * @image latex DisplayBoard.png "Using styrene sheet (3/32in/2.4mm) to dress up the display panels." height=4in
 * 
 * @page 02wiring General Wiring Notes
 * Wiring the board is simply connecting the LCC CAN network and the display.
 * 
 * There are screw terminals for optionally connecting either a power supply to
 * inject power into the CAN network or to pick power off the CAN network for 
 * local use.
 * 
 * There is a header for CAN network termination. Shorting jumpers can be added
 * to set network termination. They can be added parallel to the board edge
 * for simple termination, or at right angles to the board edge for center
 * tapped termination.  If no jumper are installed, then there is no 
 * termination.
 * @section connectingNet Connecting the network
 * There are two RJ45 jacks for connecting to the CAN network.
 * @section connectingDisplay Connecting the display
 * There is a 2x5 shrouded pin header for connecting to the display. A 2x5 IDC
 * plug is included in the kit.
 * @page 03initialConfig Initial Configuration
 * The first time the node is started, it is necessary to set the node id.
 * See \ref NodeIdConfig for information about this.
 * ****************************************************************************/


#endif // __KITBOOKLET_H

