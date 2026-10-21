// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 12 12:29:25 2023
//  Last Modified : <230412.1519>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
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
/// @file StallConsumer.hxx
/// @author Robert Heller
/// @date Wed Apr 12 12:29:25 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __STALLCONSUMER_HXX
#define __STALLCONSUMER_HXX

#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "StallConsumerConfig.hxx"

class StallConsumer : public DefaultConfigUpdateListener
{
public:
    using Impl = openlcb::GPIOBit;
    
    StallConsumer(openlcb::Node *node, const StallConsumerConfig &cfg, const Gpio *gpio)
                : DefaultConfigUpdateListener()
          , impl_(node, 0, 0, gpio)
          , consumer_(&impl_)
          , cfg_(cfg)
    {
    }
    template <class HW>
          StallConsumer(openlcb::Node *node, const StallConsumerConfig &cfg,
                        const HW &, const Gpio* g = HW::instance(), decltype(HW::instance)* = 0)
                : DefaultConfigUpdateListener()
          , impl_(node, 0, 0, g)
          , consumer_(&impl_)
          , cfg_(cfg)
    {
    }
    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable *done) OVERRIDE
    {
        AutoNotify n(done);
        openlcb::EventId cfg_event_up = cfg_.event_up().read(fd);
        openlcb::EventId cfg_event_down = cfg_.event_down().read(fd);
        if (cfg_event_up  != impl_.event_on() ||
            cfg_event_down != impl_.event_off())
        {
            auto saved_gpio = impl_.gpio_;
            auto saved_node = impl_.node();
            // Need to reinitialize the consumer. We do this with in-place
            // destruction and construction.
            consumer_.~BitEventConsumer();
            impl_.Impl::~Impl();
            new (&impl_)
                  Impl(saved_node, cfg_event_up, cfg_event_down, saved_gpio);
            new (&consumer_) openlcb::BitEventConsumer(&impl_);
            return REINIT_NEEDED; // Causes events identify.
        }
        return UPDATED;
    }
    
    void factory_reset(int fd) OVERRIDE
    {
        cfg_.description().write(fd, "");
    }
    
private:
    Impl impl_;
    openlcb::BitEventConsumer consumer_;
    const StallConsumerConfig cfg_;
};


#endif // __STALLCONSUMER_HXX

