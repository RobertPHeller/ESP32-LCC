// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Apr 4 11:39:20 2023
//  Last Modified : <230414.0831>
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
/// @file AzatraxRIR4PC.hxx
/// @author Robert Heller
/// @date Tue Apr 4 11:39:20 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __AZATRAXRIR4PC_HXX
#define __AZATRAXRIR4PC_HXX

#include "openlcb/Node.hxx"
#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "openlcb/RefreshLoop.hxx"
#include "Azatrax.hxx"

/// CDI Configuration for a @ref AzatraxDector.
CDI_GROUP(AzatraxDetectorConfig);
/// Allows the user to assign a name for this AzatraxDetector.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, //
                Name("Description"), 
                Description("User name of this Detector."));
/// Event produced (sent) when a AzatraxDetector is occupied.
CDI_GROUP_ENTRY(occupied, openlcb::EventConfigEntry,
                Name("Occupied"),
                Description("(P) This event is produced when a detector is occupied."));
/// Event produced (sent) when a AzatraxDetector is vacant.
CDI_GROUP_ENTRY(vacant, openlcb::EventConfigEntry,
                Name("Vacant"),
                Description("(P) This event is produced when a detector is vacant."));
/// Threshold setting.
CDI_GROUP_ENTRY(threshold, openlcb::Uint8ConfigEntry,
                Default(0x18),Name("Threshold"),
                Description("Sensor threshold value, 0-255."));
CDI_GROUP_END();

#define NUM_DETECTORS 4

using AllDetectors = openlcb::RepeatedGroup<AzatraxDetectorConfig, NUM_DETECTORS>;

class AzatraxDetector : public DefaultConfigUpdateListener,
                      public openlcb::SimpleEventHandler,
                      public openlcb::Polling
{
public:
    /// Constructor:
    /// @param node LCC Node object.
    /// @param cfg Configuration for this AzatraxDetector.
    /// @param rir4 Azatrax instance
    /// @param index Detector index (1-4).
    AzatraxDetector(openlcb::Node *node, const AzatraxDetectorConfig &cfg,
                    azatrax::Azatrax *rir4, uint8_t index)
                : DefaultConfigUpdateListener()
          , node_(node)
          , cfg_(cfg)
          , rir4_(rir4)
          , index_(index)
          , occupied_(0)
          , vacant_(0)
          , was_occupied_(false)
    {
        HASSERT(index >= 1 && index <= 4);
    }
    /// Destructor:
    ~AzatraxDetector()
    {
    }
    /// Apply a configuration update.
    /// @param fd File description into the configuration.
    /// @param initial_load True if this is the first time.
    /// @param done Notification object.
    /// @returns the update action, either REINIT_NEEDED or UPDATED.
    UpdateAction apply_configuration(int fd, 
                                     bool initial_load, 
                                     BarrierNotifiable *done) OVERRIDE
    {
        AutoNotify n(done);
        const openlcb::EventId cfg_occupied = cfg_.occupied().read(fd);
        const openlcb::EventId cfg_vacant = cfg_.vacant().read(fd);
        uint8_t cfg_threshold = cfg_.threshold().read(fd);
        rir4_->setThreshold(index_,cfg_threshold);
        if (cfg_occupied != occupied_ || 
            cfg_vacant != vacant_)
        {
            if (!initial_load) unregister_event_handler();
            occupied_ = cfg_occupied;
            vacant_ = cfg_vacant;
            register_event_handler();
            return REINIT_NEEDED;
        }
        return UPDATED;
    }
    /// Factory reset.
    /// @param fd File descriptor into the configuration.
    /// @returns nothing.
    void factory_reset(int fd) OVERRIDE
    {
        cfg_.description().write(fd, "");
        CDI_FACTORY_RESET(cfg_.threshold);
    }
    /// Polling function
    /// Polls the sensor and when it changes, send an event report.
    /// @param helper Write helper for sending event reports.
    /// @param done Notifiable to be notified when we are done with the 
    /// write helper.
    void poll_33hz(openlcb::WriteHelper *helper, Notifiable *done) OVERRIDE
    {
        if (was_occupied_)
        {
            if (rir4_->detVacant(index_))
            {
                sendEventReport(vacant_,helper,done);
                was_occupied_ = false;
            }
            else
            {
                done->notify();
            }
        }
        else
        {
            if (rir4_->detOccupied(index_))
            {
                sendEventReport(occupied_,helper,done);
                was_occupied_ = true;
            }
            else
            {
                done->notify();
            }
        }
    }
    /// Handle identify global.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                openlcb::EventReport *event, 
                                BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendProducerIdentified(event,done);
        done->maybe_done();
    }
    /// Handle identify producer.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_producer(const openlcb::EventRegistryEntry &registry_entry, 
                                  openlcb::EventReport *event, 
                                  BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendProducerIdentified(event,done);
        done->maybe_done();
    }
private:
    /// Register event handlers.
    void register_event_handler()
    {
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,occupied_), 0);
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,vacant_), 0);
    }
    /// Unregister event handlers.
    void unregister_event_handler()
    {
        openlcb::EventRegistry::instance()->unregister_handler(this);
    }
    void sendEventReport(const openlcb::EventId event,
                         openlcb::WriteHelper *helper, 
                         Notifiable *done)
    {
        helper->WriteAsync(node_, openlcb::Defs::MTI_EVENT_REPORT,
                           openlcb::WriteHelper::global(), 
                           openlcb::eventid_to_buffer(event), done);
    }
    void sendProducerIdentified(openlcb::EventReport *event,
                                BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
        if (was_occupied_)
        {
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(occupied_),
                  done->new_child());
        }
        else
        {
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(vacant_),
                  done->new_child());
        }
        mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID;
        if (!was_occupied_)
        {
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(occupied_),
                  done->new_child());
        }
        else
        {
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(vacant_),
                  done->new_child());
        }
    }
    /// Node.
    openlcb::Node *node_;
    /// Configuration.
    const AzatraxDetectorConfig cfg_;
    /// Sensor chip
    azatrax::Azatrax *rir4_;
    uint8_t index_;
    openlcb::EventId occupied_;
    openlcb::EventId vacant_;
    bool was_occupied_;
};

/// CDI Configuration for a @ref AzatraxStopwatch
CDI_GROUP(AzatraxStopwatchConfig);
/// Allows the user to assign a name for this AzatraxStopwatch.
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, //
                Name("Description"),
                Description("User name of this Stopwatch."));
/// Event produced (sent) when a Stopwatch stops.
CDI_GROUP_ENTRY(stopped, openlcb::EventConfigEntry,
                Name("Stopped"),
                Description("(P) This event is produced when a Stopwatch stops."));
/// Event produced (sent) when a Stopwatch is running "left to right" (1=>2 or 3=>4).
CDI_GROUP_ENTRY(leftright, openlcb::EventConfigEntry,
                Name("Left to Right"),
                Description("(P) This event is produced when a Stopwatch starts running when triggered by the lower sensor number (1 or 3)."));
/// Event produced (sent) when a Stopwatch is running "right to left" (2=>1 or 4=>3).
CDI_GROUP_ENTRY(rightleft, openlcb::EventConfigEntry,
                Name("Right to Left"),
                Description("(P) This event is produced when a Stopwatch starts running when triggered by the higher sensor number (2 or 4)."));
/// Event Consumed (received) to reset (stop) the Stopwatch.
CDI_GROUP_ENTRY(reset, openlcb::EventConfigEntry,
                Name("Reset"),
                Description("(C) This event is consumed to reset the Stopwatch."));
CDI_GROUP_END();

#define NUM_STOPWATCH 2

using AllStopwatches = openlcb::RepeatedGroup<AzatraxStopwatchConfig, NUM_STOPWATCH>;

class AzatraxStopwatch : public DefaultConfigUpdateListener,
                         public openlcb::SimpleEventHandler,
                         public openlcb::Polling
{
public:
    /// Constructor:
    /// @param node LCC Node object.
    /// @param cfg Configuration for this AzatraxStopwatch
    /// @param rir4 Azatrax instance
    /// @param index Stopwatch  index (1-2).
    AzatraxStopwatch(openlcb::Node *node, const AzatraxStopwatchConfig &cfg,
                     azatrax::Azatrax *rir4, uint8_t index)
                : DefaultConfigUpdateListener()
          , node_(node)
          , cfg_(cfg)
          , rir4_(rir4)
          , index_(index)
          , stopped_(0)
          , leftright_(0)
          , rightleft_(0)
          , reset_(0)
          , dir_(0)
    {
        HASSERT(index >= 1 && index <= 2);
    }
    /// Destructor:
    ~AzatraxStopwatch()
    {
    }
    /// Apply a configuration update.
    /// @param fd File description into the configuration.
    /// @param initial_load True if this is the first time.
    /// @param done Notification object.
    /// @returns the update action, either REINIT_NEEDED or UPDATED.
    UpdateAction apply_configuration(int fd, 
                                     bool initial_load, 
                                     BarrierNotifiable *done) OVERRIDE
    {
        AutoNotify n(done);
        const openlcb::EventId cfg_stopped   = cfg_.stopped().read(fd);
        const openlcb::EventId cfg_leftright = cfg_.leftright().read(fd);
        const openlcb::EventId cfg_rightleft = cfg_.rightleft().read(fd);
        const openlcb::EventId cfg_reset     = cfg_.reset().read(fd);
        if (cfg_stopped != stopped_ ||
            cfg_leftright != leftright_ ||
            cfg_rightleft != rightleft_ ||
            cfg_reset != reset_)
        {
            if (!initial_load) unregister_event_handler();
            stopped_ = cfg_stopped;
            leftright_ = cfg_leftright;
            rightleft_ = cfg_rightleft;
            reset_ = cfg_reset;
            register_event_handler();
            return REINIT_NEEDED;
        }
        return UPDATED;
    }
    /// Factory reset.
    /// @param fd File descriptor into the configuration.
    /// @returns nothing.
    void factory_reset(int fd) OVERRIDE
    {
        cfg_.description().write(fd, "");
    }
    /// Polling function -- checks the state of the stopwatch and sends
    /// an event report when the state of the stopwatch changes.
    /// @param helper Write helper for sending events,
    /// @param done Notifiable to be notified when the helper is done with.
    void poll_33hz(openlcb::WriteHelper *helper, Notifiable *done) OVERRIDE
    {
        byte dir = rir4_->stopwatchDir(index_);
        if (dir_ == dir)
        {
            done->notify();
        }
        else
        {
            switch (dir)
            {
            case 0:
                sendEventReport(stopped_,helper,done);
                break;
            case 1:
            case 3:
                sendEventReport(leftright_,helper,done);
                break;
            case 2:
            case 4:
                sendEventReport(rightleft_,helper,done);
                break;
            default: // should not get here
                break;
            }
            dir_ = dir;
        }
    }
    /// Handle event report.
    /// Sends a PNET Control message.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_event_report(const openlcb::EventRegistryEntry &registry_entry, 
                             openlcb::EventReport *event, 
                             BarrierNotifiable *done) override
    {
        if (event->event == reset_)
        {
            rir4_->stopwatchReset(index_);
            dir_ = 0;
        }
    }
    /// Handle identify global.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                openlcb::EventReport *event, 
                                BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendProducerIdentified(event,done);
        sendConsumerIdentified(event,done);
        done->maybe_done();
    }
    /// Handle identify producer.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_producer(const openlcb::EventRegistryEntry &registry_entry, 
                                  openlcb::EventReport *event, 
                                  BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendProducerIdentified(event,done);
        done->maybe_done();
    }
    /// Handle identify consumer.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_consumer(const openlcb::EventRegistryEntry &registry_entry, 
                                  openlcb::EventReport *event, 
                                  BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendConsumerIdentified(event,done);
        done->maybe_done();
    }
private:
    /// Register event handlers.
    void register_event_handler()
    {
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,stopped_), 0);
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,leftright_), 0);
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,rightleft_), 0);
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,reset_), 0);
    }
    /// Unregister event handlers.
    void unregister_event_handler()
    {
        openlcb::EventRegistry::instance()->unregister_handler(this);
    }
    void sendEventReport(const openlcb::EventId event,
                         openlcb::WriteHelper *helper, 
                         Notifiable *done)
    {
        helper->WriteAsync(node_, openlcb::Defs::MTI_EVENT_REPORT,
                           openlcb::WriteHelper::global(), 
                           openlcb::eventid_to_buffer(event), done);
    }
    void sendProducerIdentified(openlcb::EventReport *event,
                                BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
        switch (dir_) {
        case 0:
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(stopped_),
                  done->new_child());
            break;
        case 1:
        case 3:
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(leftright_),
                  done->new_child());
            break;
        case 2:
        case 4:
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(rightleft_),
                  done->new_child());
            break;
        default:
            break;
        }
        mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID;
        switch (dir_) {
        case 0:
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(leftright_),
                  done->new_child());
            event->event_write_helper<3>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(rightleft_),
                  done->new_child());
            break;
        case 1:
        case 3:
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(stopped_),
                  done->new_child());
            event->event_write_helper<3>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(rightleft_),
                  done->new_child());
            break;
        case 2:
        case 4:
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(stopped_),
                  done->new_child());
            event->event_write_helper<3>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(leftright_),
                  done->new_child());
            break;
        default:
            break;
        }
    }
    void sendConsumerIdentified(openlcb::EventReport *event,
                                BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID;
        if (dir_ != 0)
        {
            mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_INVALID;
        }
        event->event_write_helper<4>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(reset_),
                  done->new_child());
    }
    /// Node.
    openlcb::Node *node_;
    /// Configuration.
    const AzatraxStopwatchConfig cfg_;
    /// Sensor chip
    azatrax::Azatrax *rir4_;
    uint8_t index_;
    openlcb::EventId stopped_;
    openlcb::EventId leftright_;
    openlcb::EventId rightleft_;
    openlcb::EventId reset_;
    uint8_t dir_;
};

/// CDI Configuration for a @ref AzatraxRIR4.
CDI_GROUP(AzatraxRIR4Config);
/// Detectors (4)
CDI_GROUP_ENTRY(detectors,AllDetectors,Name("Detectors"),RepName("Detector"),
                Description("Azatrax RIR4 Detectors"));
CDI_GROUP_ENTRY(stopwatches,AllStopwatches,Name("Stopwatches"),
                RepName("Stopwatch"),
                Description("Azatrax RIR4 Stopwatches"));
CDI_GROUP_END();


/// Wrapper class for one AzatraxRIR4 shield.  Contains 4 detectors and 2
/// stopwatches.  Allocates the detector and stopwatch instances.
/// See @ref AzatraxDetector and @ref AzatraxStopwatch for more information
/// about these instances.
class AzatraxRIR4 
{
public:
    /// Constructor:
    /// @param node LCC Node object.
    /// @param cfg Configuration for this AzatraxRIR4.
    /// @param rir4 Azatrax instance
    ///
    /// Allocates the detector and stopwatch instances for one AzatraxRIR4 
    /// shield.
    AzatraxRIR4(openlcb::Node *node, const AzatraxRIR4Config &cfg,
                azatrax::Azatrax *rir4)
                : node_(node)
          , cfg_(cfg)
          , rir4_(rir4)
          , refreshloop_(node_,{})
    {
        unsigned indx;
        for (indx = 0; indx < 4; indx++)
        {
            detectors_[indx] = 
                  new AzatraxDetector(node_,
                                      cfg_.detectors().entry(indx),
                                      rir4_,indx+1);
            refreshloop_.add_member(detectors_[indx]);
        }
        for (indx = 0; indx < 2; indx++)
        {
            stopwatches_[indx] = 
              new AzatraxStopwatch(node_,
                                   cfg_.stopwatches().entry(indx),
                                   rir4_,indx+1);
            refreshloop_.add_member(stopwatches_[indx]);
        }
    }
    ~AzatraxRIR4()
    {
        unsigned indx;
        for (indx = 0; indx < 4; indx++)
        {
            delete detectors_[indx];
        }
        for (indx = 0; indx < 2; indx++)
        {
            delete stopwatches_[indx];
        }
    }
private:
    openlcb::Node *node_;
    const AzatraxRIR4Config cfg_;
    azatrax::Azatrax *rir4_;
    openlcb::RefreshLoop refreshloop_;
    AzatraxDetector *detectors_[4];
    AzatraxStopwatch *stopwatches_[2];
};
    


#endif // __AZATRAXRIR4PC_HXX

