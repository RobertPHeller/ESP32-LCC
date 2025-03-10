// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Feb 6 09:47:06 2023
//  Last Modified : <250310.1125>
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

#ifndef __SEQUENCE_HXX
#define __SEQUENCE_HXX

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

#define BRIGHNESSHUNDRETHSPERCENT(b) ((b)*.0001)

class Output : public ConfigUpdateListener, public Timer {
public:
    enum OutputID {Unused, Buffer1_, Buffer2_, Buffer3_, Buffer4_, Buffer5_, 
              Buffer6_, Buffer7_, Buffer8_};
    enum OutputMode {On, Off, FadeOn, FadeOff, Flicker};
    Output(const OutputConfig &cfg, ActiveTimers *timers) 
                : Timer(timers)
          ,cfg_(cfg)
    {
        running_ = false;
        outputid_ = Unused;
        mode_ = Off;
        brightness_ = 5000;
        currentbrightness_ = 0;
        currentstate_ = off;
        ConfigUpdateService::instance()->register_update_listener(this);
    }
    void factory_reset(int fd) OVERRIDE
    {
        CDI_FACTORY_RESET(cfg_.selection);
        CDI_FACTORY_RESET(cfg_.mode);
        CDI_FACTORY_RESET(cfg_.brightness);
    }
    virtual UpdateAction apply_configuration(int fd,
                                             bool initial_load,
                                             BarrierNotifiable *done) override
    {
        AutoNotify n(done);
        outputid_ = (OutputID) cfg_.selection().read(fd);
        //if (outputid_ > Buffer8_) outputid_ = Unused;
        mode_ = (OutputMode) cfg_.mode().read(fd);
        //if (mode_ > Flicker) mode_ = Off;
        brightness_ = cfg_.brightness().read(fd);
        return UPDATED;
    }
    PWM* Pin() const       {return pinlookup_[(int)outputid_];}
    const OutputMode Mode() const {return mode_;}
    static PWM* PinLookup(OutputID id) 
    {
        return pinlookup_[(int)id];
    }
    void StartOutput()
    {
        if (outputid_ == Unused) return;
        PWM * p = Pin();
        if (p == nullptr) return;
        switch (mode_)
        {
        case On:
            currentbrightness_ = brightness_;
            currentstate_ = on;
            break;
        case Off:
            currentbrightness_ = 0;
            currentstate_ = off;
            break;
        case FadeOn:
            if (currentstate_ != fadeup && currentbrightness_ < brightness_)
            {
                currentstate_ = fadeup;
                startDelay(500*1000000ULL); // 500ms
            }
            break;
        case FadeOff:
            if (currentstate_ != fadedown && currentbrightness_ > 0)
            {
                currentstate_ = fadedown;
                startDelay(500*1000000ULL); // 500ms
            }
            break;
        case Flicker:
            if (currentstate_ != flickering)
            {
                currentstate_ = flickering;
                currentbrightness_ = ((random()&0x01FF)+128)*10;
                startDelay(((random()&0x01FF)+128)*1000000ULL); // random 128-640 ms
            }
            break;
        }
        p->set_duty((uint32_t)(BRIGHNESSHUNDRETHSPERCENT(currentbrightness_)*p->get_period()));
    }
    static void PinLookupInit(openmrn_arduino::Esp32Ledc &ledc)
    {
        pinlookup_[(uint)Unused] = nullptr;
        for (int i=0; i < OUTPUTCOUNT; i++)
        {
            pinlookup_[i+1] = ledc.get_channel(i);
        }
    }
private:
    void startDelay(long long time) {
        if (running_) {
            return;
        }
        start(time);
        running_ = true;
    }
    long long timeout() override
    {
        running_ = false;
        if (outputid_ == Unused) return NONE;
        PWM * p = Pin();
        if (p == nullptr) return NONE; 
        switch (currentstate_)
        {
        case fadeup:
            if (currentbrightness_ < brightness_)
            {
                currentbrightness_ += 50;
                if (currentbrightness_ > brightness_) 
                {
                    currentbrightness_ = brightness_;
                }
                p->set_duty((uint32_t)(BRIGHNESSHUNDRETHSPERCENT(currentbrightness_)*p->get_period()));
                if (currentbrightness_ < brightness_)
                {
                    running_ = true;
                    return 500*1000000ULL; // 500ms
                }
                else
                {
                    currentstate_ = on;
                    return NONE;
                }
            }
            else
            {
                currentstate_ = on;
                return NONE;
            }
            break;
        case fadedown:
            if (currentbrightness_ > 0)
            {
                if (currentbrightness_ > 50)
                {
                    currentbrightness_ -= 50;
                }
                else
                {
                    currentbrightness_ = 0;
                }
                p->set_duty((uint32_t)(BRIGHNESSHUNDRETHSPERCENT(currentbrightness_)*p->get_period()));
                if (currentbrightness_ > 0)
                {
                    running_ = true;
                    return 500*1000000ULL; // 500ms
                }
                else
                {
                    currentstate_ = off;
                    return NONE;
                }
            }
            else
            {
                currentstate_ = off;
                return NONE;
            }
            break;
        case flickering:
            currentbrightness_ = ((random()&0x01FF)+128)*10;
            p->set_duty((uint32_t)(BRIGHNESSHUNDRETHSPERCENT(currentbrightness_)*p->get_period()));
            running_ = true;
            return ((random()&0x01FF)+128)*1000000ULL; // random 128-640ms
            break;
        default:
            break;
        }
        return NONE;
    }
    
            
    const OutputConfig cfg_;
    OutputID outputid_;
    OutputMode mode_;
    uint16_t brightness_;
    bool running_;
    uint16_t currentbrightness_;
    enum OutputState {on, off, fadeup, fadedown, flickering} currentstate_;
    static PWM* pinlookup_[OUTPUTCOUNT+1];
};

class Sequence;

class Step : public ConfigUpdateListener, 
             public Timer, public openlcb::SimpleEventHandler 
{
public:
    enum NextMode {Last, Next, First};
    Step(openlcb::Node *node, const StepConfig &cfg, ActiveTimers *timers, 
         Sequence *parent)
                : Timer(timers)
          , node_(node)
          , cfg_(cfg)
          , parent_(parent)
    {
        running_ = false;
        nextMode_ = Last;
        time_ = 0ULL;
        start_ = 0ULL;
        end_ = 0ULL;
        started_ = false;
        ended_ = false;
        for (int i = 0; i < OUTPUTCOUNT; i++)
        {
            outputs_[i] = new Output(cfg_.outputs().entry(i), timers);
        }
        ConfigUpdateService::instance()->register_update_listener(this);
    }
    void PointerInit(Step *first, Step *next)
    {
        first_ = first;
        next_ =next;
    }

    virtual UpdateAction apply_configuration(int fd,
                                             bool initial_load,
                                             BarrierNotifiable *done) override
    {
        AutoNotify n(done);
        time_ = cfg_.time().read(fd);
        nextMode_ = (NextMode) cfg_.next().read(fd);
        openlcb::EventId cfg_start = cfg_.start().read(fd);
        openlcb::EventId cfg_end = cfg_.end().read(fd);
        if (cfg_start != start_ ||
            cfg_end != end_)
        {
            if (!initial_load) 
            {
                unregister_handler();
            }
            start_ = cfg_start;
            end_ = cfg_end;
            register_handler();
            return REINIT_NEEDED; // Causes events identify.
        }
        return UPDATED;
    }
    virtual void factory_reset(int fd) override
    {
        CDI_FACTORY_RESET(cfg_.time);
        CDI_FACTORY_RESET(cfg_.next);
    }
    void handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                openlcb::EventReport *event, BarrierNotifiable *done)
    {
        if (event->dst_node && event->dst_node != node_)
        {
            done->notify();
            return;
        }
        SendAllProducersIdentified(event,done);
        done->maybe_done();
    }
    void handle_identify_producer(const openlcb::EventRegistryEntry &registry_entry,
                                  openlcb::EventReport *event, 
                                  BarrierNotifiable *done)
    {
        SendProducerIdentified(event,done);
        done->maybe_done();
    }
    void StartStep();
private:
    void register_handler()
    {
        openlcb::EventRegistry::instance()->register_handler(
           openlcb::EventRegistryEntry(this, start_), 0);
        openlcb::EventRegistry::instance()->register_handler(
           openlcb::EventRegistryEntry(this, end_), 0);
    }
    void unregister_handler()
    {
        openlcb::EventRegistry::instance()->unregister_handler(this);
    }
    void SendAllProducersIdentified(openlcb::EventReport *event,BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti_started = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID,
              mti_ended = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID;
        if (started_) 
        {
            mti_started = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
        }
        if (ended_)
        {
            mti_ended = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
        }
        event->event_write_helper<1>()->WriteAsync(node_,
                                                   mti_started,
                                                   openlcb::WriteHelper::global(),
                                                   openlcb::eventid_to_buffer(start_),
                                                   done->new_child());
        event->event_write_helper<2>()->WriteAsync(node_,
                                                   mti_ended,
                                                   openlcb::WriteHelper::global(),
                                                   openlcb::eventid_to_buffer(end_),
                                                   done->new_child());
    }
    void SendProducerIdentified(openlcb::EventReport *event,BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_UNKNOWN;
        if (event->event == start_)
        {
            if (started_) mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
            else mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID;
        }
        else if (event->event == end_)
        {
            if (ended_) mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
            else mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID;
        }
        event->event_write_helper<1>()->WriteAsync(node_, mti,
                                                   openlcb::WriteHelper::global(),
                                                   openlcb::eventid_to_buffer(event->event),
                                                   done->new_child());
    }
    void StartDelay()
    {
        if (running_) {
            return;
        }
        long long p = time_ * 1000000ULL;
        start(p);
        running_ = true;
    }
    long long timeout() override;
    void notify() override {
        // ** nothing here -- just to make WriteAsync happy.
        LOG(ALWAYS,"*** Step::notify()");
    }
    void SendEventReport(openlcb::WriteHelper *helper,openlcb::EventId event)
    {
        LOG(ALWAYS,"*** Step::SendEventReport(%p,0X%016llX)",helper,event);
        //bn_.reset(this);
        helper->WriteAsync(node_,
                           openlcb::Defs::MTI_EVENT_REPORT,
                           openlcb::WriteHelper::global(),
                           openlcb::eventid_to_buffer(event),
                           this);
        //bn_.maybe_done();
    }
    
    openlcb::Node *node_;
    const StepConfig cfg_;
    Sequence *parent_;
    Step *first_;
    Step *next_;
    bool running_;
    NextMode nextMode_;
    unsigned long time_;
    openlcb::EventId start_;
    openlcb::EventId end_;
    bool started_;
    bool ended_;
    Output *outputs_[OUTPUTCOUNT];
    openlcb::WriteHelper write_helpers[2];
    BarrierNotifiable bn_;
};
            
class Sequence : public ConfigUpdateListener, 
                 public openlcb::SimpleEventHandler 
{
public:
    Sequence(openlcb::Node *node, const SequenceConfig &cfg, ActiveTimers *timers)
                : node_(node)
          , cfg_(cfg)
    {
        enabled_ = false;
        start_ = 0ULL;
        stepRunning_ = false;
        stopped_ = true;
        for (int i = 0; i < STEPSCOUNT; i++)
        {
            steps_[i] = new Step(node_,cfg_.steps().entry(i),timers,this);
        }
        for (int i = 0; i < STEPSCOUNT; i++)
        {
            if ((i+1)<STEPSCOUNT)
            {
                steps_[i]->PointerInit(steps_[0],steps_[i+1]);
            }
            else
            {
                steps_[i]->PointerInit(steps_[0],nullptr);
            }
        }
        ConfigUpdateService::instance()->register_update_listener(this);
    }
    void factory_reset(int fd) OVERRIDE
    {
        cfg_.name().write(fd,"");
        CDI_FACTORY_RESET(cfg_.enabled);
    }
    UpdateAction apply_configuration(int fd, 
                                     bool initial_load,
                                     BarrierNotifiable *done)
    {
        AutoNotify n(done);
        enabled_ = cfg_.enabled().read(fd);
        openlcb::EventId cfg_start = cfg_.start().read(fd);
        openlcb::EventId cfg_stop = cfg_.stop().read(fd);
        if (cfg_start != start_ || cfg_stop != stop_)
        {
            if (!initial_load)
            {
                unregister_handler();
            }
            start_ = cfg_start;
            stop_ = cfg_stop;
            register_handler();
            return REINIT_NEEDED; // Causes events identify. 
        }
        return UPDATED;
    }
    void handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                openlcb::EventReport *event, BarrierNotifiable *done)
    {
        if (event->dst_node && event->dst_node != node_)
        {
            done->notify();
            return;
        }
        SendAllConsumersIdentified(event,done);
        done->maybe_done(); 
    }
    void handle_identify_consumer(const openlcb::EventRegistryEntry &registry_entry,
                                  openlcb::EventReport *event,
                                  BarrierNotifiable *done)
    {
        SendConsumerIdentified(event,done);
        done->maybe_done();
    }
    void handle_event_report(const openlcb::EventRegistryEntry &entry,
                             openlcb::EventReport *event,
                             BarrierNotifiable *done)
    {
        AutoNotify n(done);
        if (event->event == stop_)
        {
            stopped_ = true;
        }
        else
        {
            if (stepRunning_) return;
            if (!enabled_) return;
            stopped_ = false;
            steps_[0]->StartStep();
        }
    }
    void StepStarted()
    {
        stepRunning_ = true;
    }
    void StepEnded()
    {
        stepRunning_ = false;
    }
    bool StopP()
    {
        return stopped_;
    }
    void LastStep()
    {
        stopped_ = true;
    }
private:
    void SendAllConsumersIdentified(openlcb::EventReport *event,BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_INVALID;
        if (stepRunning_) mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID;
        event->event_write_helper<1>()->WriteAsync(node_, mti,
                                                   openlcb::WriteHelper::global(),
                                                   openlcb::eventid_to_buffer(start_),
                                                   done->new_child());
    }
    void SendConsumerIdentified(openlcb::EventReport *event,BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_UNKNOWN;
        if (event->event == start_)
        {
            if (stepRunning_) 
                mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID;
            else
                mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_INVALID;
            event->event_write_helper<2>()->WriteAsync(node_, mti, 
                                                       openlcb::WriteHelper::global(),
                                                       openlcb::eventid_to_buffer(event->event),
                                                       done->new_child());
        }
    }
    void unregister_handler()
    {
        openlcb::EventRegistry::instance()->unregister_handler(this);
    }
    void register_handler()
    {
        openlcb::EventRegistry::instance()->register_handler(
           openlcb::EventRegistryEntry(this, start_), 0);
    }
    openlcb::Node *node_;
    const SequenceConfig cfg_;
    bool enabled_;
    openlcb::EventId start_;
    openlcb::EventId stop_;
    bool stepRunning_;
    bool stopped_;
    Step *steps_[STEPSCOUNT];
};
        
        
    
#endif // __SEQUENCE_HXX

