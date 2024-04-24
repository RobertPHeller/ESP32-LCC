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
//  Last Modified : <240423.1710>
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
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#define PROGMEM
#include "Fonts/FreeMonoBold18pt7b.h"
#include "Fonts/FreeSans18pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "Fonts/TomThumb.h"

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
                 openlcb::EventRegistryEntry(this, oneventid, 0), 0);
    openlcb::EventRegistry::instance()->register_handler(
                 openlcb::EventRegistryEntry(this, offeventid, 0), 0);
}
void BacklightControl::unregister_handler()
{
    openlcb::EventRegistry::instance()->unregister_handler(this);
}


void PriceDisplay::updateDisplay()
{
    display_->fillRect(xpos_,ypos_,w_,h_,bg_);
    if (product_.empty() && price_.empty()) return;
    display_->setFont(&FreeMonoBold18pt7b);
    display_->setTextWrap(false);
    display_->setCursor(xpos_,ypos_);
    display_->print(product_.c_str());
    display_->print(" ");
    uint16_t saveX, saveY;
    switch (currency_)
    {
    case DOLLAR:
        saveX = display_->getCursorX();
        saveY = display_->getCursorY();
        display_->setFont(&TomThumb);
        display_->write('$');
        display_->setFont(&FreeMonoBold18pt7b);
        display_->setCursor(saveX,saveY);
        display_->print(" ");
        break;
    case POUND:
        saveX = display_->getCursorX();
        saveY = display_->getCursorY();
        display_->setFont(&TomThumb);
        display_->write(0x81);
        display_->setFont(&FreeMonoBold18pt7b);
        display_->setCursor(saveX,saveY);
        display_->print(" ");
        break;
    case EURO:
        saveX = display_->getCursorX();
        saveY = display_->getCursorY();
        display_->setFont(&TomThumb); 
        display_->write(0xEA);
        display_->setFont(&FreeMonoBold18pt7b);
        display_->setCursor(saveX,saveY);
        display_->print(" ");
        break;
    default:
        display_->print(" ");
        break;
    }
    display_->print(price_.c_str());
    switch (suffix_)
    {
    case NINETENTHS:
        saveX = display_->getCursorX();
        saveY = display_->getCursorY();
        display_->setFont(&TomThumb);
        display_->print("9/10");
        display_->setFont(&FreeMonoBold18pt7b);
        display_->setCursor(saveX,saveY);
        display_->print(" ");
        break;
    case EACH:
        saveX = display_->getCursorX();
        saveY = display_->getCursorY();
        display_->setFont(&TomThumb);
        display_->print("ea.");
        display_->setFont(&FreeMonoBold18pt7b);
        display_->setCursor(saveX,saveY);
        display_->print(" ");
        break; 
    case HOUR:
        saveX = display_->getCursorX();
        saveY = display_->getCursorY();
        display_->setFont(&TomThumb);
        display_->print("hr.");
        display_->setFont(&FreeMonoBold18pt7b);
        display_->setCursor(saveX,saveY);
        display_->print(" ");
        break; 
    default:
        display_->print(" ");
        break;
    }
}

void TimeOfDayMessage::SendQuery(openlcb::WriteHelper *writer, BarrierNotifiable *done)
{
    writer->WriteAsync(node_, openlcb::Defs::MTI_PRODUCER_IDENTIFY,
                       openlcb::WriteHelper::global(),
                       openlcb::eventid_to_buffer(oneventid_), done);
                       
}
void TimeOfDayMessage::handle_event_report(const openlcb::EventRegistryEntry &entry, 
                                           openlcb::EventReport *event,BarrierNotifiable *done)
{
    if (event->event == oneventid_)
    {
        parent_->clearTimeOfDayMessage();
        state_ = openlcb::EventState::VALID;
        updateDisplay();
    }
    done->notify();
}
void TimeOfDayMessage::handle_identify_global(const openlcb::EventRegistryEntry &entry,
                                openlcb::EventReport *event,
                                              BarrierNotifiable *done)
{
        if (event->dst_node && event->dst_node != node_)
    {
        return done->notify();
    }
    openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID + state_;
    event->event_write_helper<3>()->WriteAsync(node_,mti,
                                               openlcb::WriteHelper::global(), 
                                               openlcb::eventid_to_buffer(oneventid_),
                                               done->new_child());
}

void TimeOfDayMessage::handle_identify_consumer(const openlcb::EventRegistryEntry &entry,
                                  openlcb::EventReport *event,
                                                BarrierNotifiable *done)
{
    openlcb::Defs::MTI mti = openlcb::Defs::MTI_CONSUMER_IDENTIFIED_VALID + state_;
    if (event->src_node.id == node_->node_id())
    {
        // We don't respond to queries from our own node. This is not nice, but
        // we
        // want to avoid to answering our own Query command.
        done->notify();
        return;
    }
    if (event->event != oneventid_)
    {
        done->notify();
        return;
    }
    event->event_write_helper<1>()->WriteAsync(node_, mti,
                                               openlcb::WriteHelper::global(), 
                                               openlcb::eventid_to_buffer(event->event), 
                                               done);
}
void TimeOfDayMessage::register_handler(openlcb::EventId oneventid)
{
    openlcb::EventRegistry::instance()->register_handler(
                 openlcb::EventRegistryEntry(this, oneventid, 0), 0);
}
void TimeOfDayMessage::unregister_handler()
{
    openlcb::EventRegistry::instance()->unregister_handler(this);
}

void TimeOfDayMessage::updateDisplay()
{
    if (state_ != openlcb::EventState::VALID) return;
    display_->fillRect(xpos_,ypos_,w_,h_,bg_);
    display_->setFont(&FreeSans18pt7b);
    display_->setTextWrap(false);
    display_->setCursor(xpos_,ypos_);
    display_->print(message_.c_str());
}

#include "_0.xbm"
#include "_1.xbm"
#include "_2.xbm"
#include "_3.xbm"
#include "_4.xbm"
#include "_5.xbm"
#include "_6.xbm"
#include "_7.xbm"
#include "_8.xbm"
#include "_9.xbm"
#include "colon.xbm"

// The "traditional" 7-Segment display lookup table.
static struct {
    /** The bitmap itself. */
    unsigned char *bits;
    /** The width of the bitmap. */
    int  width;
    /** The height of the bitmap. */
    int  height; 
} digitBitmaps[] = {
    {_0_bits, _0_width, _0_height},
    {_1_bits, _1_width, _1_height},
    {_2_bits, _2_width, _2_height},
    {_3_bits, _3_width, _3_height},
    {_4_bits, _4_width, _4_height},
    {_5_bits, _5_width, _5_height},
    {_6_bits, _6_width, _6_height},
    {_7_bits, _7_width, _7_height},
    {_8_bits, _8_width, _8_height},
    {_9_bits, _9_width, _9_height}
};

static void drawdigit(Adafruit_GFX *display, int x, int y, int digit,
                      uint16_t color)
{
    display->drawXBitmap(x,y,digitBitmaps[digit].bits,
                         digitBitmaps[digit].width,
                         digitBitmaps[digit].height,color);
}

static void drawcolon(Adafruit_GFX *display, int x, int y, uint16_t color)
{
    display->drawXBitmap(x,y,colon_bits,colon_width,colon_height,color);
}

static void displayTime(Adafruit_GFX *display, int hours, int minutes, int x, int y, uint16_t color)
{
    // Compute each of the digits.
    if (hours > 13)
    {
        hours -= 12;
    }
    else if (hours == 0)
    {
        hours = 12;
    }
    else if (hours == 12)
    {
    }
    int hHigh = hours / 10;
    int hLow  = hours % 10;
    int mHigh = minutes / 10;
    int mLow  = minutes % 10;
    
    if (hHigh != 0) {
        drawdigit(display,x,y,hHigh,color);
    }
    drawdigit(display,x+12,y,hLow,color);
    drawcolon(display,x+24,y,color);
    drawdigit(display,x+28,y,mHigh,color);
    drawdigit(display,x+40,y,mLow,color);
}

void RetailDisplay::updateDisplay()
{
    int x=0, y;
    display_->setRotation(orient_);
    display_->fillScreen(background_);
    if (!logofile_.empty() && !logoImage_)
    {
        std::string filename = "/sdcard/";
        filename += logofile_;
        logoImage_ = new ImageReader(filename);
    }
    if (logoImage_)
    {
        logoImage_->draw(display_,0,0,display_->width(),(display_->height()==128)?32:40);
    }
    if (display_->height()==128)
    {
        y = 32;
    }
    else
    {
        y = 40;
    }
    
    if (displayTime_)
    {
        x = display_->width()-70/2;
        int hours = tm_.tm_hour;
        int minutes = tm_.tm_min;
        displayTime(display_,x,y,hours,minutes,timeColor_);
        y += 20;
    }
    for (auto iprice=prices_.begin();iprice != prices_.end(); iprice++)
    {
        
        (*iprice)->updateWindow(0,y,display_->width(),20,background_);
        (*iprice)->updateDisplay();
        y += 20;
    }
    for (auto imessage=timedofdaymessages_.begin();
         imessage!=timedofdaymessages_.end();
         imessage++)
    {
        (*imessage)->updateWindow(0,y,display_->width(),20,background_);
        (*imessage)->updateDisplay();
    }
    y += 20;
    display_->setFont(&FreeSansBold18pt7b);
    display_->setTextWrap(true);
    display_->setCursor(0,y);
    display_->print(mod_.c_str());
}


void RetailDisplay::updateTime(const struct tm *tm)
{
    tm_ = *tm;
    int x, y;
    if (display_->width() == 128)
    {
        y = 40;
        x = 128-70/2;
    }
    else
    {
        y = 32;
        x = 160-70/2;
    }
    int hours = tm_.tm_hour;
    int minutes = tm_.tm_min;
    displayTime(display_,x,y,hours,minutes,timeColor_);
}

