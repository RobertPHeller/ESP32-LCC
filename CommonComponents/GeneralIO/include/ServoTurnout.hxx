// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Feb 14 09:35:57 2023
//  Last Modified : <231125.2054>
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
/// @file ServoTurnout.hxx
/// @author Robert Heller 
/// @date Tue Feb 14 09:35:57 2023 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVOTURNOUT_HXX
#define __SERVOTURNOUT_HXX

#if defined(ARDUINO) || defined(ESP32) || defined(ESP_PLATFORM)
#include "freertos_drivers/arduino/DummyGPIO.hxx"
#include "freertos_drivers/arduino/PWM.hxx"
#else
#include "freertos_drivers/common/DummyGPIO.hxx"
#include "freertos_drivers/common/PWM.hxx"
#endif
#include "VetoBitEventInterface.hxx"                                            
#include "ServoTurnoutConfig.hxx"
#include "os/MmapGpio.hxx"
#include <memory>

class ServoTurnout : public DefaultConfigUpdateListener
{
public:
    ServoTurnout(Node *node, const ServoTurnoutConfig &cfg,
                 const uint32_t pwmCountPerMs, PWM *pwm)
                : DefaultConfigUpdateListener()
          , pwmCountPerMs_(pwmCountPerMs)
          , pwm_(pwm)        // save for apply_config, where we actually use it.
          , pwmGpo_(nullptr) // not initialized until apply_config 
          , gpioImpl_(node, 0, 0, 0, 0, DummyPinWithRead())
          , consumer_(&gpioImpl_) // don't connect consumer to PWM yet
          , cfg_(cfg)
    {
    }
    UpdateAction apply_configuration(
        int fd, bool initial_load, BarrierNotifiable *done) OVERRIDE
    {
        AutoNotify n(done);

        const openlcb::EventId cfg_event_normal = cfg_.event_normal().read(fd);
        const openlcb::EventId cfg_event_reversed = cfg_.event_reversed().read(fd);
        const openlcb::EventId cfg_veto_on = cfg_.veto_on().read(fd);
        const openlcb::EventId cfg_veto_off = cfg_.veto_off().read(fd);
        const int16_t servo_normal_pct = cfg_.servo_normal_percent().read(fd);
        const int16_t cfg_servo_reversed_pct = cfg_.servo_reversed_percent().read(fd);

        // 1ms duty cycle
        const uint32_t servo_ticks_0 = pwmCountPerMs_ * 1;
        // 2ms duty cycle
        const uint32_t servo_ticks_180 = pwmCountPerMs_ * 2;

        // Use a weighted average to determine num ticks for max/min.
        const uint32_t cfg_srv_ticks_min =
            ((100 - servo_normal_pct) * servo_ticks_0 +
                servo_normal_pct * servo_ticks_180) /
            100;
        const uint32_t cfg_srv_ticks_max =
            ((100 - cfg_servo_reversed_pct) * servo_ticks_0 +
                cfg_servo_reversed_pct * servo_ticks_180) /
            100;

        // Defaults to CLR at startup.
        const bool was_set = pwmGpo_ && (pwmGpo_->read() == Gpio::SET);

        if (!pwmGpo_ || //
            cfg_event_normal != gpioImpl_.event_on() ||
            cfg_event_reversed != gpioImpl_.event_off() ||
            cfg_veto_on != gpioImpl_.veto_on() ||
            cfg_veto_off != gpioImpl_.veto_off() ||
            cfg_srv_ticks_min != pwmGpo_->get_on_counts() ||
            cfg_srv_ticks_max != pwmGpo_->get_off_counts())
        {
            auto saved_node = gpioImpl_.node();

            consumer_.~VetoBitEventConsumer();
            gpioImpl_.~VetoGPIOBit();

            pwmGpo_.reset(new PWMGPO(pwm_,
                /*on_counts=*/cfg_srv_ticks_max,
                /*off_counts=*/cfg_srv_ticks_min));
            pwmGpo_->write(was_set ? Gpio::SET : Gpio::CLR);

            new (&gpioImpl_) VetoGPIOBit(saved_node, 
                                     cfg_event_normal, cfg_event_reversed, 
                                     cfg_veto_on, cfg_veto_off, pwmGpo_.get());
            new (&consumer_) VetoBitEventConsumer(&gpioImpl_);

            return REINIT_NEEDED;
        }

        return UPDATED;
    }

    void factory_reset(int fd) OVERRIDE
    {
        cfg_.description().write(fd, "");
        CDI_FACTORY_RESET(cfg_.servo_normal_percent);
        CDI_FACTORY_RESET(cfg_.servo_reversed_percent);
    }

private:
    /// Used to compute PWM ticks for max/min servo rotation.
    const uint32_t pwmCountPerMs_;

    /// timer channel. not owned; lives forever
    PWM *pwm_;

    /// all the rest are owned and must be reset on config change.
    /// pwmGpo_ heap-allocated because it's nullptr until first config.
    std::unique_ptr<PWMGPO> pwmGpo_; // has PWM* and on/off counts

    VetoGPIOBit gpioImpl_;          /// has on/off events, Node*, and Gpio*
    VetoBitEventConsumer consumer_; /// has GPIOBit*
    const ServoTurnoutConfig cfg_;
};

    


#endif // __SERVOTURNOUT_HXX

