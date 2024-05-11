// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Thu May 9 10:00:29 2024
//  Last Modified : <240511.0934>
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
/// @date Thu May 9 10:00:29 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __KITBOOKLET_H
#define __KITBOOKLET_H

/** @mainpage Introduction
 * 
 * This board provides 8 PWM output buffers that can drive LEDs used as 
 * structure lighting, lighted signs, etc.  Not only can brightness be
 * controled, but lights can be turned on and off in sequence (for animated
 * signs) and a "flickering" effect can be used to simulated "broken" neon
 * signs or campfires.  Events can be used to turn lights on or off.
 * 
 * @page 00kitContents Kit Contents
 * This kit contains:
 * -# This booklet.
 * -# The OctalBuffer PCB
 * @image html ESP32-Mini32-OctalBuffer_thumb.png
 * @image latex ESP32-Mini32-OctalBuffer_thumb.png height=1in
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
 * -# 1 2-position 3.5mm pitch screw terminals
 * @image html 41927_1000_int_04.jpg
 * @image latex 41927_1000_int_04.jpg height=1in
 * -# 1 9-position 3.5mm pitch screw terminals
 * @image html 1727049_SPL.jpg
 * @image latex 1727049_SPL.jpg height=1in
 * @page 01assembly Assembly
 * Assembly is straight forward.  The SMD parts are already soldered,
 * so only the through hole parts need to be soldered to the board.
 * Start with the shortest parts and work towards the tallest. Their are 
 * one 2x2 and two 2x10 headers.  The 2x2 header is for the termination header 
 * and the two 2x10 will go in the T7-S3 board (supplied separately). Note the
 * orientation of the screw terminals.
 * @page 02wiring General Wiring Notes
 * 
 * There is a large 2-position terminal block to supply power for the 
 * buffered outputs. It is marked for 12V, but any voltage upto 50V will work.
 * The buffer chip on the board can handle as much as 400ma on a single channel
 * but somewhat less if all channels are on, depending on the duty cycle. A 
 * typical LED draws upto about 20ma, but can generally be driven at 10ma.
 * 
 * The 9-position terminal block contains a common (C) which is tied to the
 * positive terminal, so it is a common cathode circuit.
 * 
 * @page 03initialConfig Initial Configuration
 * The first time the node is started, it is necessary to set the node id.
 * See \ref NodeIdConfig for information about this.
 * @page 04applications Application Examples
 *
 * @section eightballsign "8 Ball Club Sign"
 * 
 * This board can be use to light "8 Ball Club Sign", available separately.
 * A ribbon cable can be used to connect the sign panel to the driver board.
 * A sequence can be configured to light the sign's segements in turn, creating
 * an animated, colorfuly lighted sign for your model pool hall. 
 *
 * @image html 8ballsignhookup.png "Ribbon cable hookup to an 8 Ball Sign board"
 * @image latex 8ballsignhookup.png "Ribbon cable hookup to an 8 Ball Sign board" width=4in
 * 
 * @subsection eightballsignConf Configuration for the 8 ball sign
 * 
 * The configuration for the 8 ball sign contains these steps:
 * 
 * -# Appearence: Output 1: steady on, Step Time: 1000, Next step: Next
 * -# Appearence: Output 1 and 2: steady on, Step Time: 1000, Next step: Next
 * -# Appearence: Output 1, 2, and 3: steady on, Step Time: 1000, Next step: Next
 * -# Appearence: Output 1, 2, 3 and 4: steady on, Step Time: 1000, Next step: Next
 * -# Appearence: Output 1, 2, 3, 4, and 5: steady on, Step Time: 1000, Next step: Next
 * -# Appearence: Output 1, 2, 3, 4, and 5: off, Step Time: 1000, Next step: First
 *    
 ****************************************************************************/



#endif // __KITBOOKLET_H

