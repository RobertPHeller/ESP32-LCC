// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Mar 11 09:46:05 2023
//  Last Modified : <230311.1613>
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

static const char rcsid[] = "@(#) : $Id$";

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
#include "NeoPixelConsumer.hxx"

namespace neopixelloops
{
class NeoPixelLoop {
public:
    NeoPixelLoop(NeoPixelConsumer *parent) 
                : parent_(parent)
          , stop_(false)
          , running_(true)
    {
    }
    void Stop()
    {
        stop_ = true;
    }
    bool StopWanted() const {return stop_;}
    bool isRunning() const {return running_;}
    void Done()
    {
        running_ = false;
        parent_->LoopDone();
    }
private:
    NeoPixelConsumer *parent_;
    bool stop_;
    bool running_;
};

class ColorWipe : public NeoPixelLoop, public Timer
{
public:
    ColorWipe(NeoPixelConsumer *parent, ActiveTimers *timers, Esp32NeoPixel* neopixel, uint32_t color, 
              int wait)
                : NeoPixelLoop(parent)
          , Timer(timers)
          , pixel_(neopixel)
          , color_(color)
          , wait_(wait)
          , i_(0)
    {
        start(wait_*1000000LL);
    }
private:
    virtual long long timeout()
    {
        if (StopWanted())
        {
            pixel_->clear();
            pixel_->show();
            Done();
            return NONE;
        }
        if (i_ >= pixel_->numPixels())
        {
            i_ = 0;
            pixel_->clear();
        }
        pixel_->setPixelColor(i_,color_);
        pixel_->show();
        i_++;
        return wait_*1000000LL;
    }
    Esp32NeoPixel* pixel_;
    uint32_t color_;
    int wait_;
    int i_;
};
          
class TheaterChase : public NeoPixelLoop, public Timer
{
public:
    TheaterChase(NeoPixelConsumer *parent, ActiveTimers *timers, Esp32NeoPixel* neopixel, 
                 uint32_t color, int wait)
                :  NeoPixelLoop(parent)
          , Timer(timers)
          , pixel_(neopixel)
          , color_(color)
          , wait_(wait)
          , b_(0)
    {
        start(wait_*1000000LL);
    }
private:
    virtual long long timeout()
    {
        if (StopWanted())
        {
            pixel_->clear();
            pixel_->show();
            Done();
            return NONE;
        }
        pixel_->clear();
        for(int c=b_; c<pixel_->numPixels(); c += 3) 
        {
            pixel_->setPixelColor(c, color_); // Set pixel 'c' to value 'color'
        }
        pixel_->show(); // Update strip with new contents
        b_++;
        if (b_ >= 3)
        {
            b_ = 0;
        }
        return wait_*1000000LL;
    }
    Esp32NeoPixel* pixel_;
    uint32_t color_;
    int wait_;
    int b_;
};

class Rainbow : public NeoPixelLoop, public Timer
{
public: 
    Rainbow(NeoPixelConsumer *parent, ActiveTimers *timers, Esp32NeoPixel* neopixel, int wait)
                :  NeoPixelLoop(parent)
          , Timer(timers)
          , pixel_(neopixel)
          , wait_(wait)
          , firstPixelHue_(0)
    {
        start(wait_*1000000LL);
    }
private:
    virtual long long timeout()
    {
        if (StopWanted())
        {
            pixel_->clear();
            pixel_->show();
            Done();
            return NONE;
        }
        pixel_->rainbow(firstPixelHue_);
        firstPixelHue_ += 256;
        return wait_*1000000LL;
    }
    Esp32NeoPixel* pixel_;
    int wait_;
    uint16_t firstPixelHue_;
};

class TheaterChaseRainbow : public NeoPixelLoop, public Timer
{
public:
    TheaterChaseRainbow(NeoPixelConsumer *parent, ActiveTimers *timers, Esp32NeoPixel* neopixel,
                        int wait)
                : NeoPixelLoop(parent)
          , Timer(timers)
          , pixel_(neopixel)
          , wait_(wait)
          , b_(0)
          , firstPixelHue_(0)
    {
        start(wait_*1000000LL);
    }
private:
    virtual long long timeout()
    {
        if (StopWanted())
        {
            pixel_->clear();
            pixel_->show();
            Done();
            return NONE;
        }
        pixel_->clear();
        for(int c=b_; c<pixel_->numPixels(); c += 3)
        {
            int      hue   = firstPixelHue_ + c * 65536L / pixel_->numPixels();
            uint32_t color = pixel_->gamma32(pixel_->ColorHSV(hue)); // hue -> RGB
            pixel_->setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        pixel_->show();
        firstPixelHue_ += 65536 / 90;
        b_++;
        if (b_ >= 3)
        {
            b_ = 0;
        }
        return wait_*1000000LL;
    }
    Esp32NeoPixel* pixel_;
    int wait_;
    int b_;
    uint16_t firstPixelHue_; 
};

}

NeoPixelConsumer::NeoPixelConsumer(openlcb::Node *node, 
                                   const NeoPixelConsumerConfig &cfg,
                                   ActiveTimers *timers, 
                                   gpio_num_t pin)
      : node_(node)
, cfg_(cfg)
, timers_(timers)
, pin_(pin)
, on_(0)
, off_(0)
, pattern_(0)
, loop_(nullptr)
{
    ConfigUpdateService::instance()->register_update_listener(this);
}


NeoPixelConsumer::~NeoPixelConsumer()
{
    if (loop_ != nullptr)
    {
        if (loop_->isRunning())
        {
            loop_->Stop();
        }
        while (loop_->isRunning())
        {
            usleep(10000);
        }
        delete loop_;
        loop_ = nullptr;
    }
    if (pixel_ != nullptr)
    {
        delete pixel_;
        pixel_ = nullptr;
    }
    ConfigUpdateService::instance()->unregister_update_listener(this);
}

void NeoPixelConsumer::factory_reset(int fd)
{
    cfg_.description().write(fd, "");
    CDI_FACTORY_RESET(cfg_.length);
    CDI_FACTORY_RESET(cfg_.type);
    CDI_FACTORY_RESET(cfg_.speed);
    CDI_FACTORY_RESET(cfg_.pattern);
}

static neoPixelType PixelTypeMapTable[] = {
    NEO_RGB, NEO_RBG, NEO_GRB, NEO_GBR, NEO_BRG, NEO_BGR, NEO_WRGB, NEO_WRBG,
    NEO_WGRB, NEO_WGBR, NEO_WBRG, NEO_WBGR, NEO_RWGB, NEO_RWBG, NEO_RGWB,
    NEO_RGBW, NEO_RBWG, NEO_RBGW, NEO_GWRB, NEO_GWBR, NEO_GRWB, NEO_GRBW,
    NEO_GBWR, NEO_GBRW, NEO_BWRG, NEO_BWGR, NEO_BRWG, NEO_BRGW, NEO_BGWR,
    NEO_BGRW};

ConfigUpdateListener::UpdateAction NeoPixelConsumer::apply_configuration(int fd,
                                                                         bool initial_load,
                                                                         BarrierNotifiable *done)
{
    AutoNotify n(done);
    openlcb::EventId on_cfg = cfg_.event_on().read(fd);
    openlcb::EventId off_cfg = cfg_.event_off().read(fd);
    uint8_t length_cfg = cfg_.length().read(fd);
    uint8_t type_cfg = cfg_.type().read(fd);
    uint8_t speed_cfg = cfg_.speed().read(fd);
    pattern_ = cfg_.pattern().read(fd);
    if (loop_ != nullptr)
    {
        if (loop_->isRunning())
        {
            loop_->Stop();
        }
        while (loop_->isRunning())
        {
            usleep(10000);
        }
        delete loop_;
        loop_ = nullptr;
    }
    if (pixel_ != nullptr)
    {
        delete pixel_;
    }
    neoPixelType speed;
    if (speed_cfg == 0)
    {
        speed = NEO_KHZ800;
    }
    else
    {
        speed = NEO_KHZ400;
    }
    pixel_ = new Esp32NeoPixel(length_cfg,pin_,PixelTypeMapTable[type_cfg]+speed);
    if (on_cfg != on_ || off_cfg != off_)
    {
        if (!initial_load) unregister_handler();
        on_ = on_cfg;
        off_ = off_cfg;
        register_handler();
        return REINIT_NEEDED; // Causes events identify.
    }
    return UPDATED;
}

void NeoPixelConsumer::register_handler()
{
    openlcb::EventRegistry::instance()->register_handler(
        openlcb::EventRegistryEntry(this, on_), 0);
    openlcb::EventRegistry::instance()->register_handler(
        openlcb::EventRegistryEntry(this, off_), 0);
}

void NeoPixelConsumer::unregister_handler()
{
    openlcb::EventRegistry::instance()->unregister_handler(this);
}

void NeoPixelConsumer::handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                              openlcb::EventReport *event, BarrierNotifiable *done)
{
}

void NeoPixelConsumer::handle_identify_producer(const openlcb::EventRegistryEntry &registry_entry,
                                                openlcb::EventReport *event, 
                                                BarrierNotifiable *done)
{
}

void NeoPixelConsumer::handle_event_report(const openlcb::EventRegistryEntry &entry,
                                           openlcb::EventReport *event,
                                           BarrierNotifiable *done)
{
    if (event->event == on_)
    {
        if (loop_ != nullptr)
        {
            if (loop_->isRunning())
            {
                done->maybe_done();
                return;
            }
            delete loop_;
        }
        switch (pattern_) {
        case 0: // White Chase
            loop_ = new neopixelloops::TheaterChase(this, timers_,pixel_,
                                                    pixel_->Color(127, 127, 127), 50);
            break;
        case 1: // Red Chase
            loop_ = new neopixelloops::TheaterChase(this, timers_,pixel_,
                                                    pixel_->Color(127,   0,   0), 50);
            break;
        case 2: // Green Chase
            loop_ = new neopixelloops::TheaterChase(this, timers_,pixel_,
                                                    pixel_->Color(  0, 127,   0), 50);
            break;
        case 3: // Blue Chase
            loop_ = new neopixelloops::TheaterChase(this, timers_,pixel_,
                                                    pixel_->Color(  0,   0, 127), 50);
            break;
        case 4: // Rainbow Chase
            loop_ = new neopixelloops::TheaterChaseRainbow(this, timers_,pixel_,50);
            break; 
        case 5: // Red Wipe
            loop_ = new neopixelloops::ColorWipe(this, timers_,pixel_,
                                                 pixel_->Color(255,   0,   0), 50);
            break;
        case 6: // Green Wipe
            loop_ = new neopixelloops::ColorWipe(this, timers_,pixel_,
                                                 pixel_->Color(  0, 255,   0), 50);
            break;
        case 7: // Blue Wipe
            loop_ = new neopixelloops::ColorWipe(this, timers_,pixel_,
                                                 pixel_->Color(  0,   0, 255), 50);
            break;
        case 8: // Rainbow
            loop_ = new neopixelloops::Rainbow(this, timers_,pixel_,10);
            break;
        default:
            break;
        }
    }
    else if (event->event == off_)
    {
        if (loop_ != nullptr)
        {
            loop_->Stop();
        }
        
    }
    done->maybe_done();
}

void NeoPixelConsumer::SendAllConsumersIdentified(openlcb::EventReport *event,BarrierNotifiable *done)
{
}

void NeoPixelConsumer::SendConsumerIdentified(openlcb::EventReport *event,BarrierNotifiable *done)
{
}

void NeoPixelConsumer::LoopDone()
{
    delete loop_;
    loop_ = nullptr;
}

