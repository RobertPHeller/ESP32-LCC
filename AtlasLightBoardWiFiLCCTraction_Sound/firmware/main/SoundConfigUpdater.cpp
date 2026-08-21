// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Aug 19 19:17:48 2026
//  Last Modified : <260820.0850>
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

#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "SoundConfig.hxx"
#include "SoundConfigUpdater.hxx"

ConfigUpdateListener::UpdateAction 
      SoundConfigUpdater::apply_configuration(int fd, bool initial_load,
                                              BarrierNotifiable *done)
{
    AutoNotify an(done);
    auto engineSound = cfg_.engine_sound().read(fd);
    slp_->SetEngineType((SoundLoopProcess::Engine_t)engineSound);
    auto hornSound = cfg_.horn_sound().read(fd);
    slp_->SetHornType((SoundLoopProcess::Horn_t)hornSound);
    auto bellType = cfg_.bell_type().read(fd);
    slp_->SetBellType((SoundLoopProcess::Bell_t)bellType);
    return UPDATED;
}

void SoundConfigUpdater::factory_reset(int fd)
{
    cfg_.engine_sound().write(fd,0);
    cfg_.horn_sound().write(fd,0);
    cfg_.bell_type().write(fd,0);
}

