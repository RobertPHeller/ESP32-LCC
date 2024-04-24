// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 22 16:47:37 2024
//  Last Modified : <240423.1722>
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
/// @file ImageReader.cpp
/// @author Robert Heller
/// @date Mon Apr 22 16:47:37 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";


#include <string>
#include <fcntl.h>
#include "Adafruit_GFX.h"
#include "ImageReader.hxx"

#define BUFPIXELS 200 ///< 200 * 5 = 1000 bytes


ImageReader::ImageReader(std::string filename)
      : fd_(-1)
    , palette(NULL), format(IMAGE_NONE)
{
    canvas.canvas1 = NULL;
    uint32_t offset;                           // Start of image data in file
    uint32_t headerSize;                       // Indicates BMP version
    int bmpWidth, bmpHeight;                   // BMP width & height in pixels
    uint8_t planes;                            // BMP planes
    uint8_t depth;                             // BMP bit depth
    uint32_t compression = 0;                  // BMP compression mode
    uint32_t colors = 0;                       // Number of colors in palette
    uint16_t *quantized = NULL;                // 16-bit 5/6/5 color palette
    uint32_t rowSize;                          // >bmpWidth if scanline padding
    uint8_t sdbuf[3 * BUFPIXELS];              // BMP read buf (R+G+B/pixel)
    uint16_t srcidx = sizeof sdbuf;
    uint32_t destidx = 0;
    uint8_t *dest1 = NULL;     // Dest ptr for 1-bit BMPs to img
    uint16_t *dest = NULL;     // Dest ptr for 24-bit BMPs to img
    bool flip = true;          // BMP is stored bottom-to-top
    uint32_t bmpPos = 0;       // Next pixel position in file
    int loadWidth, loadHeight, // Region being loaded (clipped)
          loadX, loadY;          // "
    int row, col;              // Current pixel pos.
    uint8_t r, g, b, e;           // Current pixel color
    uint8_t bitIn = 0;         // Bit number for 1-bit data in
    uint8_t bitOut = 0;        // Column mask for 1-bit data out
    
    // Open requested file on SD card
    fd_ = open(filename.c_str(), O_RDONLY);
    if (fd_ < 0) return;
    
    // Parse BMP header. 0x4D42 (ASCII 'BM') is the Windows BMP signature.
    // There are other values possible in a .BMP file but these are super
    // esoteric (e.g. OS/2 struct bitmap array) and NOT supported here!
    if (readLE16() == 0x4D42) { // BMP signature
        (void)readLE32();         // Read & ignore file size
        (void)readLE32();         // Read & ignore creator bytes
        offset = readLE32();      // Start of image data
        // Read DIB header
        headerSize = readLE32();
        bmpWidth = readLE32();
        bmpHeight = readLE32();
        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
            bmpHeight = -bmpHeight;
            flip = false;
        }
        planes = readLE16();
        depth = readLE16(); // Bits per pixel
        // Compression mode is present in later BMP versions (default = none)
        if (headerSize > 12) {
            compression = readLE32();
            (void)readLE32();    // Raw bitmap data size; ignore
            (void)readLE32();    // Horizontal resolution, ignore
            (void)readLE32();    // Vertical resolution, ignore
            colors = readLE32(); // Number of colors in palette, or 0 for 2^depth
            (void)readLE32();    // Number of colors used (ignore)
            // File position should now be at start of palette (if present)
        }
        if (!colors)
            colors = 1 << depth;
        
        loadWidth = bmpWidth;
        loadHeight = bmpHeight;
        loadX = 0;
        loadY = 0;
        
        if ((planes == 1) && (compression == 0)) { // Only uncompressed is handled
            
            // BMP rows are padded (if needed) to 4-byte boundary
            rowSize = ((depth * bmpWidth + 31) / 32) * 4;
            
            if ((depth == 24) || (depth == 1)) { // BGR or 1-bit bitmap format
                
                // Loading to RAM -- allocate GFX 16-bit canvas type
                if (depth == 24) {
                    if ((canvas.canvas16 = new GFXcanvas16(bmpWidth, bmpHeight))) {
                        dest = canvas.canvas16->getBuffer();
                    }
                } else {
                    if ((canvas.canvas1 = new GFXcanvas1(bmpWidth, bmpHeight))) {
                        dest1 = canvas.canvas1->getBuffer();
                    }
                }
                // Future: handle other depths.
                
                if (dest || dest1) { // Supported format, alloc OK, etc.
                    
                    if ((loadWidth > 0) && (loadHeight > 0)) { // Clip top/left
                        if (depth == 1) {
                            format = IMAGE_1; // Is a GFX 1-bit canvas type
                        } else {
                            format = IMAGE_16; // Is a GFX 16-bit canvas type
                        }
                
                        
                        if ((depth >= 16) ||
                            (quantized = (uint16_t *)malloc(colors * sizeof(uint16_t)))) {
                            if (depth < 16) {
                                // Load and quantize color table
                                for (uint16_t c = 0; c < colors; c++) {
                                    read(fd_, &b, sizeof(b));
                                    read(fd_, &g, sizeof(g));
                                    read(fd_, &r, sizeof(r));
                                    read(fd_, &e, sizeof(e)); // Ignore 4th byte
                                    quantized[c] =
                                          ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                                }
                            }
                            
                            for (row = 0; row < loadHeight; row++) { // For each scanline...
                                // Seek to start of scan line.  It might seem labor-intensive
                                // to be doing this on every line, but this method covers a
                                // lot of gritty details like cropping, flip and scanline
                                // padding. Also, the seek only takes place if the file
                                // position actually needs to change (avoids a lot of cluster
                                // math in SD library).
                                if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
                                    bmpPos = offset + (bmpHeight - 1 - (row + loadY)) * rowSize;
                                else // Bitmap is stored top-to-bottom
                                    bmpPos = offset + (row + loadY) * rowSize;
                                if (depth == 24) {
                                    bmpPos += loadX * 3;
                                } else {
                                    bmpPos += loadX / 8;
                                    bitIn = 7 - (loadX & 7);
                                    bitOut = 0x80;
                                }
                                if (lseek(fd_, 0, SEEK_CUR) != bmpPos) { // Need seek?
                                    lseek(fd_, bmpPos, SEEK_SET);     // Seek = SD transaction
                                    srcidx = sizeof sdbuf; // Force buffer reload
                                }
                                for (col = 0; col < loadWidth; col++) { // For each pixel...
                                    if (srcidx >= sizeof sdbuf) {         // Time to load more?
                                        read(fd_, sdbuf, sizeof(sdbuf)); // just load sdbuf
                                        srcidx = 0;                       // Reset bmp buf index
                                    }
                                    if (depth == 24) {
                                        // Convert each pixel from BMP to 565 format, save in dest
                                        b = sdbuf[srcidx++];
                                        g = sdbuf[srcidx++];
                                        r = sdbuf[srcidx++];
                                        dest[destidx++] =
                                              ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                                    } else {
                                        // Extract 1-bit color index
                                        uint8_t n = (sdbuf[srcidx] >> bitIn) & 1;
                                        if (!bitIn) {
                                            srcidx++;
                                            bitIn = 7;
                                        } else {
                                            bitIn--;
                                        }
                                        // Store bit in canvas1 buffer (ignore palette)
                                        if (n)
                                            dest1[destidx] |= bitOut;
                                        else
                                            dest1[destidx] &= ~bitOut;
                                        bitOut >>= 1;
                                        if (!bitOut) {
                                            bitOut = 0x80;
                                            destidx++;
                                        }
                                    }
                                }                // end pixel loop
                            } // end scanline loop
                            palette = quantized; // Keep palette with img
                        } // end depth>24 or quantized malloc OK
                    }   // end top/left clip
                }     // end malloc check
            }       // end depth check
        }         // end planes/compression check
    }           // end signature
    
    close(fd_);
}


ImageReader::~ImageReader()
{
    if (format == IMAGE_1) {
        if (canvas.canvas1) {
            delete canvas.canvas1;
            canvas.canvas1 = NULL;
        }
    } else if (format == IMAGE_8) {
        if (canvas.canvas8) {
            delete canvas.canvas8;
            canvas.canvas8 = NULL;
        }
    } else if (format == IMAGE_16) {
        if (canvas.canvas16) {
            delete canvas.canvas16;
            canvas.canvas16 = NULL;
        }
    }
    if (palette) {
        delete[] palette;
        palette = NULL;
    }
    format = IMAGE_NONE;
}

bool ImageReader::returnDimensions( int &width, int &height )
{
    if (format != IMAGE_NONE) // Image allocated?
    {
        if (format == IMAGE_1)
        {
            width = canvas.canvas1->width();
            height = canvas.canvas1->height();
        } 
        else if (format == IMAGE_8)
        {
            width = canvas.canvas8->width();
            height = canvas.canvas8->height();
        }
        else if (format == IMAGE_16)
        {
            width = canvas.canvas16->width(); 
            height = canvas.canvas16->height(); 
        }
        return true;
    }
    else
    {
        return false;
    }
}

void ImageReader::draw(Adafruit_GFX *display,int x, int y, int maxwidth, 
                       int maxheight)
{  
    if (format == IMAGE_1) {
        uint16_t foreground, background;
        if (palette) {
            foreground = palette[1];
            background = palette[0];
        } else {
            foreground = 0xFFFF;
            background = 0x0000;
        }
        display->drawBitmap(x, y, canvas.canvas1->getBuffer(), 
                            canvas.canvas1->width(),
                            canvas.canvas1->height(), foreground, background);
    } else if (format == IMAGE_8) {
    } else if (format == IMAGE_16) {
        display->drawRGBBitmap(x, y, canvas.canvas16->getBuffer(),
                               canvas.canvas16->width(), 
                               canvas.canvas16->height());
    }
}

uint16_t ImageReader::readLE16()
{
    uint8_t buff[2];
    read(fd_,buff,sizeof(buff));
    return buff[0] | ((uint16_t)buff[1] << 8);
}

uint32_t ImageReader::readLE32(void)
{
    uint8_t buff[4];
    read(fd_,buff,sizeof(buff));
    return buff[0] | ((uint32_t)buff[1] << 8) | ((uint32_t)buff[2] << 16) |
          ((uint32_t)buff[3] << 24);
}

