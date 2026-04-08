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
//  Last Modified : <260407.2209>
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
 * This kit contains: 
 * -# This booklet.
 * -# The T7S3 Mini Display PCB
 * @image html T7S3MiniDisplay_thumb.png
 * @image latex T7S3MiniDisplay_thumb.png height=1in
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
 * -# 1 Adafruit Monochrome 0.91" 128x32 I2C OLED Display - STEMMA QT / Qwiic
 * @image html 4440-07.jpg
 * @image latex 4440-07.jpg height=1in
 * -# 1 STEMMA QT / Qwiic JST SH 4-pin Cable - 100mm Long
 * @image html 4210-00.jpg
 * @image latex 4210-00.jpg height=1in 
 * @page 01assembly Assembly
 * Assembly is straight forward.  The SMD parts are already soldered,
 * so only the through hole parts need to be soldered to the board.
 * Start with the shortest parts and work towards the tallest. Their are 
 * one 2x2 and two 2x10 headers.  The 2x2 header is for the termination header 
 * and the two 2x10 will go in the T7-S3 board (supplied separately). Note the
 * orientation of the screw terminals.
 * @page 02wiring General Wiring Notes  
 * There is a little JST connector (Qwiic) for the Adafruit display, Use the 
 * Qwiic JST SH 4-pin Cable to connect the node board to the display board.
 * @page 03initialConfig Initial Configuration
 * The first time the node is started, it is necessary to set the node id.
 * See \ref NodeIdConfig for information about this.
 * @page 04OperationNotes Operation Notes
 * 
 */
