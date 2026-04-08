// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 6 21:22:28 2026
//  Last Modified : <260408.0815>
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


#include "openlcb/BroadcastTimeDefs.hxx"
#include "openlcb/BroadcastTimeClient.hxx"
#include "openlcb/BroadcastTimeAlarm.hxx"
#include "openlcb/BroadcastTimeAlarm.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "DepartureBoardConfig.hxx"
#include "DepartureBoard.hxx"
#include "Adafruit_SSD1306.h"
#include "ParseXML.hxx"

#include <fcntl.h>
#include <unistd.h>

ConfigUpdateListener::UpdateAction DepartureBoard::apply_configuration(int fd, 
                                                                       bool initial_load,
                                                                       BarrierNotifiable *done)
{
    AutoNotify an(done);
    string scheduleFile_cfg = cfg_.scheduleFile().read(fd);
    bool use_fast_clock_cfg = cfg_.fastclock().read(fd) != 0;
    if (initial_load)
    {
        schedule_file_ = scheduleFile_cfg;
        use_fast_clock_ = use_fast_clock_cfg;
    } else 
    {
        if (schedule_file_ != scheduleFile_cfg)
        {
            if (parsedSched_ != nullptr)
            {
                delete parsedSched_;
                parsedSched_ = nullptr;
            }
            schedule_file_ = scheduleFile_cfg;
        }
        if (use_fast_clock_ != use_fast_clock_cfg)
        {
            if (alarm_ != nullptr)
            {
                delete alarm_;
                alarm_ = nullptr;
            }
            if (clock_ != nullptr)
            {
                delete clock_;
                clock_ = nullptr;
            }
            use_fast_clock_ = use_fast_clock_cfg;
        }
    }
    if (schedule_file_ != "" && parsedSched_ == nullptr)
    {
        int sfd = open(schedule_file_.c_str(),O_RDONLY);
        parsedSched_ = new ParseXML::ParseXML(sfd);
        close(sfd);
    }
    if (schedule_file_ != "" && alarm_ == nullptr && clock_ == nullptr)
    {
        clock_= new openlcb::BroadcastTimeClient(node_,
                                                 use_fast_clock_?
                                                 openlcb::BroadcastTimeDefs::DEFAULT_FAST_CLOCK_ID:
                                                 openlcb::BroadcastTimeDefs::DEFAULT_REALTIME_CLOCK_ID);
        alarm_ = new openlcb::BroadcastTimeAlarmMinute(node_,clock_,
                                                       std::bind(&DepartureBoard::UpdateBoard_,
                                                                 this,std::placeholders::_1));
    }
    return UPDATED;
}

void DepartureBoard::factory_reset(int fd)
{
    cfg_.scheduleFile().write(fd, "");
    cfg_.fastclock().write(fd,cfg_.fastclock_options().defaultvalue());
}

void DepartureBoard::UpdateBoard_(BarrierNotifiable *done)
{
    AutoNotify an(done);
    if (clock_ == nullptr || alarm_ == nullptr || parsedSched_ == nullptr) 
    {
        return;
    }
    time_t now_secs = clock_->time();
    uint16_t currentTime = (now_secs / 60) % 1440; // 1440 == 60 * 24 (minutes in a day)
    display_.clearDisplay();
    int16_t y = 0;
    auto departures = parsedSched_->GetElementsByTagName("departure");
    for (auto d = departures.begin(); d != departures.end(); d++)
    {
        auto field = (*d)->GetElementsByTagName("time");
        if (field.size() == 1)
        {
            uint16_t departTime = atoi(field.front()->Data().c_str());
            if (departTime < currentTime) continue;
            uint8_t hours = departTime / 60;
            uint8_t hours12 = hours % 12;
            bool pm = hours >= 12;
            if (hours12 == 0) hours12 = 12;
            uint8_t minutes = departTime % 60;
            if (hours12 < 10)
            {
                display_.drawChar(0,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            else
            {
                display_.drawChar(0,y,'0'+(hours12 / 10),SSD1306_WHITE,SSD1306_BLACK,1);
            }
            display_.drawChar(6,y,'0'+(hours12 % 10),SSD1306_WHITE,SSD1306_BLACK,1);
            display_.drawChar(12,y,':',SSD1306_WHITE,SSD1306_BLACK,1);
            display_.drawChar(18,y,'0'+(minutes / 10),SSD1306_WHITE,SSD1306_BLACK,1); 
            display_.drawChar(24,y,'0'+(minutes % 10),SSD1306_WHITE,SSD1306_BLACK,1);
            if (pm) 
            {
                display_.drawChar(30,y,'P',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            else
            {
                display_.drawChar(30,y,'A',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            display_.drawChar(36,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
        }
        field = (*d)->GetElementsByTagName("number");
        if (field.size() == 1)
        {
            string number = field.front()->Data();
            if (number.length() < 4)
            {
                display_.drawChar(42,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            else
            {
                display_.drawChar(42,y,number[0],SSD1306_WHITE,SSD1306_BLACK,1);
            }
            if (number.length() < 3)
            {
                display_.drawChar(48,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            else
            {
                display_.drawChar(48,y,number[1],SSD1306_WHITE,SSD1306_BLACK,1);
            }
            if (number.length() < 2)
            {
                display_.drawChar(54,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            else
            {
                display_.drawChar(54,y,number[2],SSD1306_WHITE,SSD1306_BLACK,1);
            }
            if (number.length() < 1)
            {
                display_.drawChar(60,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
            }
            else
            {
                display_.drawChar(60,y,number[3],SSD1306_WHITE,SSD1306_BLACK,1);
            }
            display_.drawChar(66,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
        }
        field = (*d)->GetElementsByTagName("destination");
        if (field.size() == 1)
        {
            string dest = field.front()->Data();
            for (size_t i = 0; i < 6; i++)
            {
                display_.drawChar(72+(i*6),y,dest[i],SSD1306_WHITE,SSD1306_BLACK,1);
            }
            display_.drawChar(96,y,' ',SSD1306_WHITE,SSD1306_BLACK,1);
        }
        field = (*d)->GetElementsByTagName("platform");
        if (field.size() == 1)
        {
            string plat = field.front()->Data();
            for (size_t i = 0; i < 4; i++)
            {
                display_.drawChar(102+(i*6),y,plat[i],SSD1306_WHITE,SSD1306_BLACK,1);
            }
        }
        y += 8;
        if (y >= 32) break;
    }
    display_.display();
}
