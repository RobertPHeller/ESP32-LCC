// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Feb 6 15:24:56 2023
//  Last Modified : <250109.1315>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
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

#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "openlcb/RefreshLoop.hxx"
#include "openlcb/SimpleStack.hxx"
#include "executor/Timer.hxx"
#include "executor/Notifiable.hxx"
#include <stdio.h>
#include <stdlib.h>
#include "utils/logging.h"
#include <string>
#include "OutputConfigGroup.hxx"
#include "StepConfigGroup.hxx"
#include "SequenceConfigGroup.hxx"
#include <freertos_drivers/esp32/Esp32Ledc.hxx>
#include "Sequence.hxx"

void Step::StartStep()
{
    for (int i=0; i < OUTPUTCOUNT; i++)
    {
        outputs_[i]->StartOutput();
    }
    SendEventReport(&write_helpers[0],start_);
    started_ = true;
    parent_->StepStarted();
    ended_ = false;
    StartDelay();
}

long long Step::timeout()
{
    running_ = false;
    SendEventReport(&write_helpers[1],end_);
    started_ = false;
    ended_ = true;
    parent_->StepEnded();
    switch (nextMode_)
    {
    case Last: 
        parent_->LastStep();
        break;
    case Next: 
        if (next_ != nullptr) 
        {
            next_->StartStep(); 
        }
        else
        {
            parent_->LastStep();
        }
        break;
    case First: 
        if (parent_->StopP()) break;
        first_->StartStep(); 
        break;
    }
    return NONE;
}

PWM* Output::pinlookup_[OUTPUTCOUNT+1];
