// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Oct 14 15:16:50 2018
//  Last Modified : <230323.1653>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2018  Robert Heller D/B/A Deepwoods Software
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
/// @file Points.hxx
/// @author Robert Heller 
/// @date Sun Oct 14 15:16:50 2018 
//////////////////////////////////////////////////////////////////////////////

#ifndef __POINTS_HXX
#define __POINTS_HXX

#include "openlcb/PolledProducer.hxx"
#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "PointsConfig.hxx"


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


class Points : public ConfigUpdateListener
{
public:
    using Impl = openlcb::GPIOBit;
    using ProducerClass = PolledProducerNoDebouncer<Impl>;

    Points(openlcb::Node *node, const PointsConfig &cfg, const Gpio *gpio)
        : producer_(node, 0, 0, gpio)
        , cfg_(cfg)
    {
        ConfigUpdateService::instance()->register_update_listener(this);
    }

    template <class HW>
    Points(openlcb::Node *node, const PointsConfig &cfg, const HW &,
                       const Gpio *g = HW::instance())
        : producer_(node, 0, 0, g)
        , cfg_(cfg)
    {
        ConfigUpdateService::instance()->register_update_listener(this);
    }

    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable *done) override
    {
        AutoNotify n(done);
        openlcb::EventId cfg_event_on = cfg_.normal().read(fd);
        openlcb::EventId cfg_event_off = cfg_.reversed().read(fd);
        if (cfg_event_off != producer_.event_off() ||
            cfg_event_on != producer_.event_on())
        {
            auto saved_gpio = producer_.gpio_;
            auto saved_node = producer_.node();
            // Need to reinitialize the producer. We do this with in-place
            // destruction and construction.
            producer_.ProducerClass::~ProducerClass();
            new (&producer_) ProducerClass(
                saved_node,
                cfg_event_on, cfg_event_off, saved_gpio);
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
    
    openlcb::EventState get_current_state()
    {
        return producer_.get_current_state();
    }
private:
    ProducerClass producer_;
    const PointsConfig cfg_;
};



#endif // __POINTS_HXX

