// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Thu Aug 20 07:39:39 2026
//  Last Modified : <260821.0917>
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

static const char rcsid[] = "@(#) : $Id$";

#include <fcntl.h>
#include <unistd.h>
#include "utils/logging.h"

#include "SoundData.hxx"

#include "PCMDATA/EMD576_16.pcmdat"
#include "PCMDATA/EMD710G3.pcmdat"
//#include "PCMDATA/EMD576_8.pcmdat"
//#include "PCMDATA/EMD576_12.pcmdat"
//#include "PCMDATA/EMD645_8.pcmdat"
//#include "PCMDATA/EMD645_12.pcmdat"
//#include "PCMDATA/EMD645_16.pcmdat"
//#include "PCMDATA/EMD645T_12.pcmdat"
//#include "PCMDATA/EMD645T_16.pcmdat"
//#include "PCMDATA/EMD645T_20.pcmdat"

static SoundData::SoundFileEntry EngineData[] = {
    {EMD576_16_PCM, EMD576_16_BYTES},
    {EMD710G3_PCM, EMD710G3_BYTES},
    //{EMD576_8_PCM, EMD576_8_BYTES},
    //{EMD576_12_PCM, EMD576_12_BYTES},
    //{EMD645_8_PCM, EMD645_8_BYTES},
    //{EMD645_12_PCM, EMD645_12_BYTES},
    //{EMD645_16_PCM, EMD645_16_BYTES},
    //{EMD645T_12_PCM, EMD645T_12_BYTES},
    //{EMD645T_16_PCM, EMD645T_16_BYTES},
    //{EMD645T_20_PCM, EMD645T_20_BYTES},
    {NULL, 0}
};
#define EngineDataSize (sizeof(EngineData) / sizeof(EngineData[0]))


void SoundData::EngineSound(int i2s_fp, uint8_t engineIndex, uint16_t speed)
{
    LOG(INFO, "[SoundData::EngineSound] i2s_fp=%d, engineIndex=%d, speed=%d", i2s_fp,engineIndex,speed);
    if (engineIndex >= EngineDataSize) return;
    //double compression = speed / 50.0;
    //static uint16_t compressed_pcm[COMPRESSION_BUFFER_SIZE];
    //size_t wordCount = EngineData[engineIndex].pcmBytes/2;
    write(i2s_fp,EngineData[engineIndex].pcmData,EngineData[engineIndex].pcmBytes);
}

//#include "PCMDATA/Leslie_RS3L.pcmdat"
//#include "PCMDATA/NathanAirChime.pcmdat"

static SoundData::SoundFileEntry HornData[] = {
    //{Leslie_RS3L_PCM, Leslie_RS3L_BYTES},
    //{NathanAirChime_PCM, NathanAirChime_BYTES},
    {NULL, 0}
};
#define HornDataSize (sizeof(HornData) / sizeof(HornData[0])) 

void SoundData::HornSound(int i2s_fp, uint8_t hornIndex)
{
    LOG(INFO, "[SoundData::HornSound] i2s_fp=%d, hornIndex=%d",i2s_fp,hornIndex);
    if (hornIndex >= HornDataSize) return;
    write(i2s_fp,HornData[hornIndex].pcmData,HornData[hornIndex].pcmBytes);
}

//#include "PCMDATA/StandardBell.pcmdat"

static SoundData::SoundFileEntry BellData[] = {
    //{StandardBell_PCM, StandardBell_BYTES},
    {NULL, 0}
};
#define BellDataSize (sizeof(BellData) / sizeof(BellData[0])) 

void SoundData::BellSound(int i2s_fp, uint8_t bellIndex)
{
    LOG(INFO, "[SoundData:BellSound] i2s_fp=%d, bellIndex=%d",i2s_fp,bellIndex);
    if (bellIndex >= BellDataSize) return;
    write(i2s_fp,BellData[bellIndex].pcmData,BellData[bellIndex].pcmBytes);
}

