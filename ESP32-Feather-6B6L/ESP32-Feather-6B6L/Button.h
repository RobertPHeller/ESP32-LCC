// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Feb 24 14:51:54 2019
//  Last Modified : <241213.1224>
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
/// @file Button.hxx
/// @author Robert Heller
/// @date Sun Feb 24 14:51:54 2019
//////////////////////////////////////////////////////////////////////////////

#ifndef __BUTTON_HXX
#define __BUTTON_HXX

#include "openlcb/PolledProducer.hxx"
#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "utils/Debouncer.hxx"
#include "ButtonConfig.h"

template <class BaseBit> class PolledProducerNoDebouncer : public BaseBit, public openlcb::Polling
{
public:
    template <typename... Fields>
    PolledProducerNoDebouncer(Fields... bit_args)
                : BaseBit(bit_args...)
          , producer_(this)
    {
        old_state = BaseBit::get_current_state();
    }
    openlcb::EventState get_current_state() OVERRIDE
    {
        return BaseBit::get_current_state();
    }

    void poll_33hz(openlcb::WriteHelper *helper, Notifiable *done) OVERRIDE
    {
        if (old_state != BaseBit::get_current_state()) {
            old_state = BaseBit::get_current_state();
            producer_.SendEventReport(helper, done);
        }
        else
        {
            done->notify();
        }
    }
private:
    openlcb::BitEventProducer producer_;
    openlcb::EventState old_state;
};

/// OpenLCB Producer class integrating a simple CDI-based configuration for two
/// event IDs, and an input GPIO object whose value will determine when to
/// produce events. This is usually the most important object for a simple IO
/// node.  (Specialized CDI for ocupancy detectors.)
///
/// Usage: Must be called repeatedly via the Polling implementation exposed by
/// @ref polling(). Use for example the @ref RefreshLoop class and supply the
/// polling argument at the constructor to it:
/// 
/// openlcb::RefreshLoop loop(
///    stack.node(), {producer_sw1.polling(), producer_sw2.polling()});
class Button : public ConfigUpdateListener
{
public:
    using Impl = openlcb::GPIOBit;
    using ProducerClass = PolledProducerNoDebouncer<Impl>;

    Button(openlcb::Node *node, const ButtonConfig &cfg, const Gpio *gpio)
        : producer_(node, 0, 0, gpio)
        , cfg_(cfg)
    {
        ConfigUpdateService::instance()->register_update_listener(this);
    }

    template <class HW>
    Button(openlcb::Node *node, const ButtonConfig &cfg, const HW &,
        const Gpio *g = HW::instance(), decltype(HW::instance) * = 0)
        : producer_(node, 0, 0, g)
        , cfg_(cfg)
    {
        ConfigUpdateService::instance()->register_update_listener(this);
    }

    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable *done) override
    {
        AutoNotify n(done);
        openlcb::EventId cfg_event_released = cfg_.event_released().read(fd);
        openlcb::EventId cfg_event_pressed = cfg_.event_pressed().read(fd);
        if (cfg_event_pressed != producer_.event_off() ||
            cfg_event_released != producer_.event_on())
        {
            auto saved_gpio = producer_.gpio_;
            auto saved_node = producer_.node();
            // Need to reinitialize the producer. We do this with in-place
            // destruction and construction.
            producer_.ProducerClass::~ProducerClass();
            new (&producer_) ProducerClass(
                saved_node,
                cfg_event_released, cfg_event_pressed, saved_gpio);
            return REINIT_NEEDED; // Causes events identify.
        }
        return UPDATED;
    }

    void factory_reset(int fd) OVERRIDE
    {
        cfg_.description().write(fd, "");
    }

    openlcb::Polling *polling()
    {
        return &producer_;
    }

private:
    ProducerClass producer_;
    const ButtonConfig cfg_;
};





#endif // __BUTTON_HXX

