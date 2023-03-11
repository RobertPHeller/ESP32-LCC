// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Mar 11 10:57:52 2023
//  Last Modified : <230311.1603>
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

#ifndef __NEOPIXELCONSUMER_HXX
#define __NEOPIXELCONSUMER_HXX

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
#include "NeoPixelConsumerConfig.hxx"
#include "Esp32NeoPixel.hxx"
#include <esp_err.h>
#include <driver/gpio.h>
#include <esp_idf_version.h>

namespace neopixelloops
{
class NeoPixelLoop;
}

class NeoPixelConsumer : public ConfigUpdateListener,
                         public openlcb::SimpleEventHandler
{
public:
    NeoPixelConsumer(openlcb::Node *node, const NeoPixelConsumerConfig &cfg, 
                     ActiveTimers *timers, gpio_num_t pin);
    ~NeoPixelConsumer();
    void factory_reset(int fd) OVERRIDE;
    virtual UpdateAction apply_configuration(int fd,
                                             bool initial_load,
                                             BarrierNotifiable *done) override;
    void handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                openlcb::EventReport *event, BarrierNotifiable *done);
    void handle_identify_producer(const openlcb::EventRegistryEntry &registry_entry,
                                  openlcb::EventReport *event, 
                                  BarrierNotifiable *done);
    void handle_event_report(const openlcb::EventRegistryEntry &entry,
                             openlcb::EventReport *event,
                             BarrierNotifiable *done);
    void LoopDone();
private:
    void SendAllConsumersIdentified(openlcb::EventReport *event,BarrierNotifiable *done);
    void SendConsumerIdentified(openlcb::EventReport *event,BarrierNotifiable *done);
    void unregister_handler();
    void register_handler();
    openlcb::Node *node_;
    const NeoPixelConsumerConfig cfg_;
    ActiveTimers *timers_;
    gpio_num_t pin_;
    openlcb::EventId on_;
    openlcb::EventId off_;
    uint8_t pattern_;
    Esp32NeoPixel *pixel_;
    neopixelloops::NeoPixelLoop *loop_;
    
    
};

#endif // __NEOPIXELCONSUMER_HXX

