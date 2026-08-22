// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Aug 19 21:18:05 2026
//  Last Modified : <260822.1419>
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

#include "SoundLoopProcess.hxx"
#include "SoundData.hxx"
#include "AudioMixer.hxx"

void SoundLoopProcess::run()
{
    AudioMixer mixer("/dev/mixer");
    int soundFp = open("/dev/i2s/i2s0",O_WRONLY);
    int engineChannel = open("/dev/mixer", O_WRONLY);
    int hornChannel = open("/dev/mixer", O_WRONLY);
    int bellChannel = open("/dev/mixer", O_WRONLY);
    
    
    while (true)
    {
        if (engine_type_ != NoEngine)
        {
            SoundData::EngineSound(engineChannel,((uint8_t)engine_type_)-1,current_speed_);
        }
        if (horn_)
        {
            if (horn_type_ != NoHorn)
            {
                SoundData::HornSound(hornChannel,((uint8_t)horn_type_)-1);
            }
        }
        if (bell_)
        {
            if (bell_type_ != NoBell)
            {
                SoundData::BellSound(bellChannel,((uint8_t)bell_type_)-1);
            }
        }
        mixer.FlushToI2S(soundFp);
    }
}
