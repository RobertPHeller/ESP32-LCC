// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Feb 24 14:51:54 2019
//  Last Modified : <230323.1659>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2019  Robert Heller D/B/A Deepwoods Software
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
/// @file Turnout.hxx
/// @author Robert Heller 
/// @date Sun Feb 24 14:51:54 2019 
//////////////////////////////////////////////////////////////////////////////

#ifndef _TURNOUT_HXX_
#define _TURNOUT_HXX_

#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "openlcb/RefreshLoop.hxx"
#include "VetoBitEventInterface.hxx"
#include "TurnoutConfig.hxx"

/// OpenLCB Consumer class integrating a simple CDI-based configuration for two
/// event IDs, and an output GPIO object that will be turned on or off
/// depending on the incoming event notifications. This is usually the most
/// important object for a simple IO node.
class Turnout : public ConfigUpdateListener
{
public:
    using Impl = VetoGPIOBit;

    Turnout(openlcb::Node *node, const TurnoutConfig &cfg, const Gpio *gpio)
        : impl_(node, 0, 0, 0, 0, gpio)
        , consumer_(&impl_)
        , cfg_(cfg)
    {
        ConfigUpdateService::instance()->register_update_listener(this);
    }

    template <class HW>
    Turnout(openlcb::Node *node, const TurnoutConfig &cfg, const HW &, const Gpio* g = HW::instance())
        : impl_(node, 0, 0, 0, 0, g)
        , consumer_(&impl_)
        , cfg_(cfg)
    {
        ConfigUpdateService::instance()->register_update_listener(this);
    }

    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable *done) OVERRIDE
    {
        AutoNotify n(done);
        openlcb::EventId cfg_event_on = cfg_.normal().read(fd);
        openlcb::EventId cfg_event_off = cfg_.reversed().read(fd);
        openlcb::EventId cfg_veto_on = cfg_.veto_on().read(fd);
        openlcb::EventId cfg_veto_off = cfg_.veto_off().read(fd);
        if (cfg_event_off != impl_.event_off() ||
            cfg_event_on != impl_.event_on() ||
            cfg_veto_on != impl_.veto_on() ||
            cfg_veto_off != impl_.veto_off())
        {
            auto saved_gpio = impl_.gpio_;
            auto saved_node = impl_.node();
            // Need to reinitialize the consumer. We do this with in-place
            // destruction and construction.
            consumer_.~VetoBitEventConsumer();
            impl_.Impl::~Impl();
            new (&impl_)
                Impl(saved_node, cfg_event_on, cfg_event_off, cfg_veto_on, cfg_veto_off, saved_gpio);
            new (&consumer_) VetoBitEventConsumer(&impl_);
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
    VetoBitEventConsumer consumer_;
    const TurnoutConfig cfg_;
};


#endif // _TURNOUT_HXX_
