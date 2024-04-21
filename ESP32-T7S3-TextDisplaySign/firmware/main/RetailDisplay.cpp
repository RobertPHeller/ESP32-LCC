// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Apr 20 17:51:02 2024
//  Last Modified : <240420.2156>
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
/// @file RetailDisplay.cpp
/// @author Robert Heller
/// @date Sat Apr 20 17:51:02 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";


#include <string>
#include <vector>
#include "openlcb/PolledProducer.hxx"
#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "openlcb/BroadcastTime.hxx"
#include "openlcb/BroadcastTimeClient.hxx"
#include "Adafruit_GFX.h"
#include "freertos_drivers/arduino/PWM.hxx"

#include "RetailDisplayConfig.hxx"
#include "RetailDisplay.hxx"

void BacklightControl::SendQuery(openlcb::WriteHelper *writer, 
                                 BarrierNotifiable *done)
{
    writer->WriteAsync(node_, openlcb::Defs::MTI_PRODUCER_IDENTIFY,
                       openlcb::WriteHelper::global(),
                       openlcb::eventid_to_buffer(oneventid_), done);
                       
}
void BacklightControl::handle_event_report(const openlcb::EventRegistryEntry &entry, 
                                           openlcb::EventReport *event,
                                           BarrierNotifiable *done)
{
    if (event->event == oneventid_)
    {
        backlight_->set_duty((uint32_t)((brightness_*.0001)*backlight_->get_period()));
    }
    else if (event->event == offeventid_)
    {
        backlight_->set_duty(0);
    }
    done->notify();
}
void BacklightControl::handle_identify_global(const openlcb::EventRegistryEntry &entry,
                                              openlcb::EventReport *event,
                                              BarrierNotifiable *done)
{
    if (event->dst_node && event->dst_node != node_)
    {
        return done->notify();
    }
    openlcb::EventState state = (backlight_->get_duty() != 0) 
          ? openlcb::EventState::VALID : openlcb::EventState::INVALID;
    openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID + state;
    event->event_write_helper<3>()->WriteAsync(node_,mti,
                                               openlcb::WriteHelper::global(), 
                                               openlcb::eventid_to_buffer(oneventid_),
                                               done->new_child());
    mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID + openlcb::invert_event_state(state);
    event->event_write_helper<4>()->WriteAsync(node_,mti,
                                               openlcb::WriteHelper::global(), 
                                               openlcb::eventid_to_buffer(offeventid_),
                                               done->new_child());
    done->maybe_done();
}
void BacklightControl::handle_identify_consumer(const openlcb::EventRegistryEntry &entry,
                                                openlcb::EventReport *event,
                                                BarrierNotifiable *done)
{
    openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID;
    if (event->src_node.id == node_->node_id())
    {
        // We don't respond to queries from our own node. This is not nice, but
        // we
        // want to avoid to answering our own Query command.
        done->notify();
        return;
    }
    openlcb::EventState active;
    if (event->event == oneventid_)
    {
        active =  (backlight_->get_duty() != 0) 
              ? openlcb::EventState::VALID : openlcb::EventState::INVALID;
    }
    else if (event->event == offeventid_)
    {
        active =  (backlight_->get_duty() == 0) 
              ? openlcb::EventState::VALID : openlcb::EventState::INVALID;
    }
    else
    {
        done->notify();
        return;
    }
    mti = mti + active;
    event->event_write_helper<1>()->WriteAsync(node_, mti,
                                               openlcb::WriteHelper::global(), 
                                               openlcb::eventid_to_buffer(event->event), 
                                               done);
}
void BacklightControl::register_handler(openlcb::EventId oneventid, 
                                        openlcb::EventId offeventid)
{
    openlcb::EventRegistry::instance()->register_handler(
                 openlcb::EventRegistryEntry(this, oneventid, EVENT_ON), 0);
    openlcb::EventRegistry::instance()->register_handler(
                 openlcb::EventRegistryEntry(this, offeventid, EVENT_OFF), 0);
}
void BacklightControl::unregister_handler()
{
    openlcb::EventRegistry::instance()->unregister_handler(this);
}



void PriceDisplay::updateDisplay()
{
}

void RetailDisplay::updateDisplay()
{
}

void RetailDisplay::updateTime(const struct tm *tm)
{
}
