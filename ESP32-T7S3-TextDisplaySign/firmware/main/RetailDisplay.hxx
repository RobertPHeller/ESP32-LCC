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
//  Last Modified : <240423.1706>
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
#include "ImageReader.hxx"

#include "RetailDisplayConfig.hxx"

class RetailDisplay;

class PriceDisplay : public DefaultConfigUpdateListener
{
public:
    PriceDisplay(openlcb::Node *node, const PriceConfig &cfg,
                 Adafruit_GFX *display, int xpos=0, int ypos=0, 
                 int w=0, int h=0)
                : node_(node)
          , cfg_(cfg)
          , display_(display)
          , xpos_(xpos)
          , ypos_(ypos)
          , w_(w)
          , h_(h)
    {
    }
    UpdateAction apply_configuration(int fd, bool initial_load, 
                                     BarrierNotifiable* done) override
    {
        AutoNotify n(done);
        product_ = cfg_.product().read(fd);
        productColor_ = cfg_.productColor().read(fd);
        currency_ = (Currency_t) cfg_.currency().read(fd);
        price_ = cfg_.price().read(fd);
        suffix_ = (Suffix_t) cfg_.suffix().read(fd);
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
protected:
    friend class RetailDisplay;
    void updateDisplay();
    void updateWindow(int xpos, int ypos, int w, int h, uint16_t bg)
    {
        xpos_ = xpos;
        ypos_ = ypos;
        w_ = w;
        h_ = h;
        bg_ = bg;
    }
private:
    openlcb::Node *node_;
    const PriceConfig cfg_;
    Adafruit_GFX *display_;
    int xpos_;
    int ypos_;
    int w_;
    int h_;
    std::string product_;
    std::string price_;
    enum Currency_t {NOCURRENCY=0, DOLLAR=1, POUND=2, EURO=3} currency_;
    enum Suffix_t {NOSUFFIX=0, NINETENTHS=1, EACH=2, HOUR=3} suffix_;
    uint16_t productColor_;
    uint16_t priceColor_;
    uint16_t bg_;
};

class TimeOfDayMessage : public DefaultConfigUpdateListener, 
                         public openlcb::SimpleEventHandler
{
public:
    TimeOfDayMessage(openlcb::Node *node, const TODConfig &cfg,
                     Adafruit_GFX *display, RetailDisplay *parent,
                     int xpos=0, int ypos=0,
                     int w=0,int h=0)
                : node_(node)
          , cfg_(cfg) 
          , display_(display)
          , parent_(parent)
          , xpos_(xpos)
          , ypos_(ypos)
          , w_(w)
          , h_(h)
          , oneventid_(0)
          , state_(openlcb::EventState::INVALID)
    {
        register_handler(oneventid_);
    }
    ~TimeOfDayMessage()
    {
        unregister_handler();
    }
    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable* done) override 
    {
        AutoNotify n(done);
        
        message_ = cfg_.message().read(fd);
        color_ = cfg_.messageColor().read(fd);
        if (state_ == openlcb::EventState::VALID)
        {
            updateDisplay();
        }
        openlcb::EventId cfg_onevent = cfg_.onevent().read(fd);
        if (cfg_onevent != oneventid_)
        {
            unregister_handler();
            oneventid_ = cfg_onevent;
            register_handler(oneventid_);
            return REINIT_NEEDED;
        }
        return UPDATED;
    }
    void factory_reset(int fd) override
    {
        cfg_.message().write(fd,"");
        CDI_FACTORY_RESET(cfg_.messageColor);
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
protected:
    friend class RetailDisplay;
    void updateDisplay();
    void updateWindow(int xpos, int ypos, int w, int h, uint16_t bg)
    {
        xpos_ = xpos;
        ypos_ = ypos;
        w_ = w;
        h_ = h;
        bg_ = bg;
    }
    void turnOff()
    {
        if (state_ != openlcb::EventState::INVALID)
            display_->fillRect(xpos_,ypos_,w_,h_,bg_);
        state_ = openlcb::EventState::INVALID;
    }
private:
    void register_handler(openlcb::EventId oneventid);
    void unregister_handler();
    openlcb::Node *node_;
    const TODConfig cfg_;
    Adafruit_GFX *display_;
    RetailDisplay *parent_;
    int xpos_;
    int ypos_;
    int w_;
    int h_;
    openlcb::EventId oneventid_;
    std::string message_;
    uint16_t color_;
    openlcb::EventState state_;
    uint16_t bg_;
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
          , orient_(Portrait)
          , backlight_(backlight)
          , background_(0x0000)
          , logofile_("")
          , mod_("")
          , modColor_(0x07FF)
          , displayTime_(false)
          , timeColor_(0xF800)
          , clock_(clock)
          , logoImage_(nullptr)
    {
        memset(&tm_,0,sizeof(tm_));
        int i;
        if (backlight != NULL)
        {
            backlightCtl_ = new BacklightControl(node_,backlight,5000,0,0);
        }
        for (i=0;i<NUM_PRICES;i++)
        {
            prices_.push_back(new PriceDisplay(node_,cfg_.prices().entry(i),
                                               display_));
        }
        for (i=0;i<NUM_TOD;i++)
        {
            timedofdaymessages_.push_back(
                 new TimeOfDayMessage(node_,
                                      cfg_.timedofdaymessages().entry(i),
                                      display_,this));
        }
        alarm_ = NULL;
    }
    UpdateAction apply_configuration(int fd, bool initial_load, 
                                     BarrierNotifiable* done) override
    {
        AutoNotify n(done);
        bool redisplay = initial_load;
        if (backlight_ != NULL)
        {
            delete backlightCtl_;
            uint16_t bright = cfg_.brightness().read(fd);
            openlcb::EventId signon = cfg_.signon().read(fd);
            openlcb::EventId signoff = cfg_.signoff().read(fd);
            backlightCtl_ = new BacklightControl(node_,backlight_,bright,signon,signoff);
        }
        enum Orientation_t oldorient = orient_;
        orient_ = (enum Orientation_t) cfg_.orient().read(fd);
        redisplay = redisplay || (oldorient != orient_);
        uint16_t oldback = background_;
        background_ = cfg_.background().read(fd);
        redisplay = redisplay || (oldback != background_);
        std::string oldlogo = logofile_;
        logofile_ = cfg_.logofile().read(fd);
        if (oldlogo != logofile_)
        { 
            if (logoImage_)
            {
                delete logoImage_;
                logoImage_ = nullptr;
            }
            redisplay = true;
        }
        std::string oldmod = mod_;
        mod_ = cfg_.mod().read(fd);
        redisplay = redisplay || (mod_ != oldmod);
        uint16_t oldmodcolor = modColor_;
        modColor_= cfg_.modColor().read(fd);
        redisplay = redisplay || (oldmodcolor != modColor_);
        bool olddisptime = displayTime_;
        displayTime_ = cfg_.displayTime().read(fd) != 0;
        if (olddisptime != displayTime_)
        {
            if (!displayTime_ && alarm_)
            {
                delete alarm_;
                alarm_ = nullptr;
            }
            else if (displayTime_ && !alarm_)
            {
                alarm_ = new openlcb::BroadcastTimeAlarmMinute(node_,clock_,
                                                               [&](BarrierNotifiable *done)
                                                           {
                                                               auto* tm = clock_->gmtime_get();
                                                               updateTime(tm);
                                                               done->notify();
                                                           });
            }
            redisplay = true;
        }
        uint16_t oldtimecolor = timeColor_;
        timeColor_ = cfg_.timeColor().read(fd);
        redisplay = redisplay || (oldtimecolor != timeColor_);
        if (redisplay) updateDisplay();
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
protected:
    friend class TimeOfDayMessage;
    void clearTimeOfDayMessage()
    {
        for (auto imessage=timedofdaymessages_.begin();
             imessage!=timedofdaymessages_.end();
             imessage++)
        {
            (*imessage)->turnOff();
        }
    }
private:
    void updateDisplay();
    void updateTime(const struct tm *tm);
    openlcb::Node *node_;
    const RetailDisplayConfig cfg_;
    Adafruit_GFX *display_;
    enum Orientation_t {Landscape=0, Portrait=1, Seascape=2, UpsideDown=3} orient_;
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
    struct tm tm_;
    ImageReader *logoImage_;
};

#endif // __RETAILDISPLAY_HXX

