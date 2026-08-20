// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Aug 19 20:45:17 2026
//  Last Modified : <260819.2117>
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

#ifndef __SOUNDLOOPPROCESS_HXX
#define __SOUNDLOOPPROCESS_HXX

#include "executor/Executor.hxx"
#include "executor/Executable.hxx"

class SoundLoopProcess : public Executable
{
public:
    enum Engine_t {NoEngine = 0, EMD576_8, EMD576_12, EMD576_16, EMD645_8, EMD645_12,
              EMD645_16, EMD645T_12, EMD645T_16, EMD645T_20};
    enum Horn_t {NoHorn = 0, Leslie_RS3L, Nathan_AirChime};
    enum Bell_t {NoBell = 0, Standard};
    SoundLoopProcess()
                : current_speed_(0)
          , horn_(false)
          , bell_(false)
          , engine_type_(NoEngine)
          , horn_type_(NoHorn)
          , bell_type_(NoBell)
    {
    }
    
    ~SoundLoopProcess()
    {
    }
    
    void SetSpeed(uint16_t newspeed)
    {
        current_speed_ = newspeed;
    }
    void HornOn()
    {
        horn_ = true;
    }
    void HornOff()
    {
        horn_ = false;
    }
    void BellOn()
    {
        bell_ = true;
    }
    void BellOff()
    {
        bell_ = false;
    }
    void SetEngineType(Engine_t engine_type)
    {
        engine_type_ = engine_type;
    }
    void SetHornType(Horn_t horn_type)
    {
        horn_type_ = horn_type;
    }
    void SetBellType(Bell_t bell_type)
    {
        bell_type_ = bell_type;
    }
    virtual void run();
private:
    uint16_t current_speed_;
    bool horn_;
    bool bell_;
    Engine_t engine_type_;
    Horn_t horn_type_;
    Bell_t bell_type_;
    
};

#endif // __SOUNDLOOPPROCESS_HXX

