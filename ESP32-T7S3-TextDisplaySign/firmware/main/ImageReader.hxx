// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 22 13:13:23 2024
//  Last Modified : <240423.1634>
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
/// @file ImageReader.hxx
/// @author Robert Heller
/// @date Mon Apr 22 13:13:23 2024
///
/// Adapted from Adafruit's ImageReader library for Arduino. 
/// Originally written by Phil "PaintYourDragon" Burgess for Adafruit Industries.
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __IMAGEREADER_HXX
#define __IMAGEREADER_HXX

#include <string>
#include "Adafruit_GFX.h"

class ImageReader
{
public:
    ImageReader(std::string filename);
    ~ImageReader();
    void draw(Adafruit_GFX *display,int x, int y, int maxwidth=160, int maxheight=40);
    bool returnDimensions( int &width, int &height );
private:
    /** Image formats returned by loadBMP() */
    enum ImageFormat {
        IMAGE_NONE, // No image was loaded; IMAGE_ERR_* condition
              IMAGE_1,    // GFXcanvas1 image (NOT YET SUPPORTED)
              IMAGE_8,    // GFXcanvas8 image (NOT YET SUPPORTED)
              IMAGE_16    // GFXcanvas16 image (SUPPORTED)
          };
    
    int fd_;
    union {                  // Single pointer, only one variant is used:
        GFXcanvas1 *canvas1;   ///< Canvas object if 1bpp format
        GFXcanvas8 *canvas8;   ///< Canvas object if 8bpp format
        GFXcanvas16 *canvas16; ///< Canvas object if 16bpp
    } canvas;                ///< Union of different GFXcanvas types
    uint16_t *palette;       ///< Color palette for 8bpp image (or NULL)
    uint8_t format;          ///< Canvas bundle type in use
    uint16_t readLE16(void);
    uint32_t readLE32(void);
};

#endif // __IMAGEREADER_HXX

