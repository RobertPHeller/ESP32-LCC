// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Thu Aug 20 07:28:47 2026
//  Last Modified : <260820.1338>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2026  Robert Heller D/B/A Deepwoods Software
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

#ifndef __SOUNDDATA_HXX
#define __SOUNDDATA_HXX

class SoundData
{
public:
    struct SoundFileEntry {
        const uint16_t *pcmData;
        const size_t   pcmBytes;
        SoundFileEntry(const uint16_t *pcm_data, size_t pcm_bytes)
                    : pcmData(pcm_data)
              , pcmBytes(pcm_bytes)
        {
        }
    };
    static constexpr size_t COMPRESSION_BUFFER_SIZE = 2048;
    static void EngineSound(int i2s_fp, uint8_t engineIndex, uint16_t speed);
    static void HornSound(int i2s_fp, uint8_t hornIndex);
    static void BellSound(int i2s_fp, uint8_t bellIndex);
};


#endif // __SOUNDDATA_HXX

