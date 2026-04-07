// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 6 20:53:43 2026
//  Last Modified : <260407.1232>
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

#ifndef __DEPARTUREBOARD_HXX
#define __DEPARTUREBOARD_HXX

#include "openlcb/BroadcastTimeDefs.hxx"
#include "openlcb/BroadcastTimeClient.hxx"
#include "openlcb/BroadcastTimeAlarm.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "DepartureBoardConfig.hxx"
#include "Adafruit_SSD1306.h"
#include "ParseXML.hxx"

#include <string.h>

class DepartureBoard : private DefaultConfigUpdateListener
{
public:
    DepartureBoard(openlcb::Node *node,const DepartureBoardConfig &cfg)
                : DefaultConfigUpdateListener()
          , node_(node)
          , cfg_(cfg)
          , display_(SSD1306_LCDWIDTH,SSD1306_LCDHEIGHT)
          , alarm_(nullptr)
          , clock_(nullptr)
          , use_fast_clock_(false)
          , schedule_file_("")
          , parsedSched_(nullptr)
    {
        display_.begin("/dev/i2c",SSD1306_SWITCHCAPVCC,0x3C);
        display_.clearDisplay();
        display_.display();
    }
    ~DepartureBoard()
    {
        if (alarm_ != nullptr) delete alarm_;
        if (clock_ != nullptr) delete clock_;
        if (parsedSched_ != nullptr) delete parsedSched_;
    }
private:
    /** Apply a the configuration settings.
     *      * @param fd Config file descriptor.
     *      * @param initial_load Initial load flag.
     *      * @param done Notifiable.
     *      */
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    /** Factory reset.
     *      * @param fd Config file descriptor. 
     *      */
    virtual void factory_reset(int fd);
    void UpdateBoard_(BarrierNotifiable *done);
    openlcb::Node *node_;
    const DepartureBoardConfig cfg_;
    Adafruit_SSD1306 display_;
    openlcb::BroadcastTimeAlarmMinute *alarm_;
    openlcb::BroadcastTimeClient *clock_;
    bool use_fast_clock_;
    string schedule_file_;
    ParseXML::ParseXML *parsedSched_;
};

#endif // __DEPARTUREBOARD_HXX

