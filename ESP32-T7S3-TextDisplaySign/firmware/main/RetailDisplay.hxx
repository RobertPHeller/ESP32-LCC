// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Apr 20 09:25:53 2024
//  Last Modified : <240420.2153>
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
/// @file RetailDisplay.hxx
/// @author Robert Heller
/// @date Sat Apr 20 09:25:53 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __RETAILDISPLAY_HXX
#define __RETAILDISPLAY_HXX

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

class PriceDisplay : public DefaultConfigUpdateListener
{
public:
    PriceDisplay(openlcb::Node *node, const PriceConfig &cfg,
                 Adafruit_GFX *display, int xpos, int ypos)
                : node_(node)
          , cfg_(cfg)
          , display_(display)
          , xpos_(xpos)
          , ypos_(ypos)
    {
    }
    UpdateAction apply_configuration(int fd, bool initial_load, 
                                     BarrierNotifiable* done) override
    {
        AutoNotify n(done);
        product_ = cfg_.product().read(fd);
        productColor_ = cfg_.productColor().read(fd);
        currency_ = cfg_.currency().read(fd);
        price_ = cfg_.price().read(fd);
        suffix_ = cfg_.suffix().read(fd);
        priceColor_= cfg_.priceColor().read(fd);
        updateDisplay();
        if (initial_load)
        {
            return REINIT_NEEDED;
        }
        else
        {
            return UPDATED;
        }
    }
    void factory_reset(int fd) override
    {
        cfg_.product().write(fd,"");
        CDI_FACTORY_RESET(cfg_.productColor);
        CDI_FACTORY_RESET(cfg_.currency);
        cfg_.price().write(fd,"");
        CDI_FACTORY_RESET(cfg_.suffix);
        CDI_FACTORY_RESET(cfg_.priceColor);
    }
private:
    void updateDisplay();
    openlcb::Node *node_;
    const PriceConfig cfg_;
    Adafruit_GFX *display_;
    int xpos_;
    int ypos_;
    std::string product_;
    std::string price_;
    uint8_t currency_;
    uint8_t suffix_;
    uint16_t productColor_;
    uint16_t priceColor_;
};

class TimeOfDayMessage : public DefaultConfigUpdateListener, 
                         public openlcb::SimpleEventHandler
{
public:
    TimeOfDayMessage(openlcb::Node *node, const TODConfig &cfg,
                     Adafruit_GFX *display, int xpos, int ypos)
                : node_(node)
          , cfg_(cfg) 
          , display_(display) 
          , xpos_(xpos)
          , ypos_(ypos)
          , oneventid_(0)
          , offeventid_(0)
    {
    }
private:
    openlcb::Node *node_;
    const PriceConfig cfg_;
    Adafruit_GFX *display_;
    int xpos_;
    int ypos_;
    uint64_t oneventid_;
    uint64_t offeventid_;
    std::string message_;
    uint16_t color_;
};
    
class BacklightControl : public openlcb::SimpleEventHandler
{
public:
    BacklightControl(openlcb::Node *node, PWM *backlight, 
                     uint16_t brightness, openlcb::EventId oneventid, 
                     openlcb::EventId offeventid)
                : node_(node)
          , backlight_(backlight)
          , brightness_(brightness)
          , oneventid_(oneventid)
          , offeventid_(offeventid)
    {
        register_handler(oneventid_,offeventid_);
    }
    ~BacklightControl()
    {
        unregister_handler();
    }
    /// Queries producers and acquires the current state of the bit.
    void SendQuery(openlcb::WriteHelper *writer, BarrierNotifiable *done);
    void handle_event_report(const openlcb::EventRegistryEntry &entry, 
                             openlcb::EventReport *event,BarrierNotifiable *done) override;
    void handle_identify_global(const openlcb::EventRegistryEntry &entry,
                                openlcb::EventReport *event,
                                BarrierNotifiable *done) override;
    void handle_identify_consumer(const openlcb::EventRegistryEntry &entry,
                                  openlcb::EventReport *event,
                                  BarrierNotifiable *done) override;
private:
    enum {EVENT_ON = 1, EVENT_OFF = 2};
    void register_handler(openlcb::EventId oneventid, openlcb::EventId offeventid);
    void unregister_handler();
    openlcb::Node *node_;
    PWM *backlight_;
    uint16_t brightness_;
    openlcb::EventId oneventid_;
    openlcb::EventId offeventid_;
};

class RetailDisplay : public DefaultConfigUpdateListener
{
public:
    RetailDisplay(openlcb::Node *node, const RetailDisplayConfig &cfg, 
                  Adafruit_GFX *display, 
                  openlcb::BroadcastTime *clock, 
                  PWM* backlight = NULL)
                : node_(node)
          , cfg_(cfg)
          , display_(display)
          , orient_(1)
          , backlight_(backlight)
          , background_(0x0000)
          , logofile_("")
          , mod_("")
          , modColor_(0x07FF)
          , displayTime_(false)
          , timeColor_(0xF800)
          , clock_(clock)
    {
        int i;
        if (backlight != NULL)
        {
            backlightCtl_ = new BacklightControl(node_,backlight,5000,0,0);
        }
        for (i=0;i<NUM_PRICES;i++)
        {
            prices_.push_back(new PriceDisplay(node_,cfg_.prices().entry(i),
                                               display_,PRICE_MARGIN,
                                               PRICES_YOFF+(i*PRICE_HEIGHT)));
        }
        for (i=0;i<NUM_TOD;i++)
        {
            //timedofdaymessages_.push_back(
            //     new TimeOfDayMessage(node_,cfg_.timedofdaymessages().entry(i),
            //                          display_,TOD_MARGIN,
            //                          TOD_YOFF+(i*TOD_HEIGHT)));
        }
        alarm_ = NULL;
    }
    UpdateAction apply_configuration(int fd, bool initial_load, 
                                     BarrierNotifiable* done) override
    {
        AutoNotify n(done);
        if (backlight_ != NULL)
        {
            delete backlightCtl_;
            uint16_t bright = cfg_.brightness().read(fd);
            openlcb::EventId signon = cfg_.signon().read(fd);
            openlcb::EventId signoff = cfg_.signoff().read(fd);
            backlightCtl_ = new BacklightControl(node_,backlight_,bright,signon,signoff);
        }
        orient_ = cfg_.orient().read(fd);
        background_ = cfg_.background().read(fd);
        logofile_ = cfg_.logofile().read(fd);
        mod_ = cfg_.mod().read(fd);
        modColor_= cfg_.modColor().read(fd);
        if (displayTime_ && alarm_ != NULL) 
        {
            delete alarm_;
            alarm_ = NULL;
        }
        displayTime_ = cfg_.displayTime().read(fd) != 0;
        if (displayTime_)
        {
            alarm_ = new openlcb::BroadcastTimeAlarmMinute(node_,clock_,
                                                           [&](BarrierNotifiable *done)
                                                       {
                                                           auto* tm = clock_->gmtime_get();
                                                           updateTime(tm);
                                                           done->notify();
                                                       });
        }
        timeColor_ = cfg_.timeColor().read(fd);
        updateDisplay();
        if (initial_load)
        {
            return REINIT_NEEDED;
        }
        else
        {
            return UPDATED;
        }
    }
    void factory_reset(int fd) override
    {
        cfg_.description().write(fd,"");
        CDI_FACTORY_RESET(cfg_.orient);
        CDI_FACTORY_RESET(cfg_.brightness);
        CDI_FACTORY_RESET(cfg_.background);
        cfg_.logofile().write(fd,"");
        cfg_.mod().write(fd,"");
        CDI_FACTORY_RESET(cfg_.modColor);
        CDI_FACTORY_RESET(cfg_.displayTime);
        CDI_FACTORY_RESET(cfg_.timeColor);
    }
private:
    enum {
        PRICE_MARGIN = 5,
        PRICES_YOFF = 50,
        PRICE_HEIGHT = 20
    };
    void updateDisplay();
    void updateTime(const struct tm *tm);
    openlcb::Node *node_;
    const RetailDisplayConfig cfg_;
    Adafruit_GFX *display_;
    uint8_t orient_;
    PWM * backlight_;
    uint16_t background_;
    std::string logofile_;
    std::vector<PriceDisplay *> prices_;
    std::string mod_;
    uint16_t modColor_;
    bool displayTime_;
    uint16_t timeColor_;
    std::vector<TimeOfDayMessage *> timedofdaymessages_;
    BacklightControl *backlightCtl_;
    openlcb::BroadcastTime *clock_;
    openlcb::BroadcastTimeAlarmMinute *alarm_;
        
};

#endif // __RETAILDISPLAY_HXX

