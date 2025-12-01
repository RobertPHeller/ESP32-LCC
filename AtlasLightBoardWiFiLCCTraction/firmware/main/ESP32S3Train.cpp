// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-30 12:19:45
//  Last Modified : <251201.0905>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2025  Robert Heller D/B/A Deepwoods Software
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
/// @file ESP32S3Train.cpp
/// @author Robert Heller
/// @date 2025-11-30 12:19:45
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";


#include "executor/StateFlow.hxx"
#include "freertos_drivers/esp32/Esp32Ledc.hxx"
#include "freertos_drivers/esp32/Esp32Gpio.hxx"
#include "freertos_drivers/arduino/PWM.hxx"
#include "openlcb/TractionTrain.hxx"
#include "openlcb/TrainInterface.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"

#include "hardware.hxx"
#include "FunctionConfig.hxx"
#include "MotorConfig.hxx"
#include "ESP32S3Train.hxx"

const char ESP32_FDI[] = 
R"(<?xml version='1.0' encoding='UTF-8'?>
<?xml-stylesheet type='text/xsl' href='xslt/fdi.xsl'?>
<fdi xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://openlcb.org/trunk/prototypes/xml/schema/fdi.xsd'>
<segment space='249'><group><name/>
<function size='1' kind='binary'>
<name>Headlights</name>
<number>0</number>
</function>
<function size='1' kind='binary'>
<name>Function 1</name>
<number>1</number>
</function>
<function size='1' kind='binary'>
<name>Function 2</name>
<number>2</number>
</function>
<function size='1' kind='binary'>
<name>Function 3</name>
<number>3</number>
</function>
<function size='1' kind='binary'>
<name>Function 4</name>
<number>4</number>
</function>
<function size='1' kind='binary'>
<name>Function 5</name>
<number>5</number>
</function>
<function size='1' kind='binary'>
<name>Function 6</name>
<number>6</number>
</function>
</group></segment></fdi>)";

StateFlowBase::Action ESP32SpeedController::entry()
{
    if (req()->emergencyStop_)
    {
        motorpwm_->get_channel(0)->set_duty(100);
        motorpwm_->get_channel(1)->set_duty(100);
        release();
        return sleep_and_call(&timer_, MSEC_TO_NSEC(1), STATE(eoff_enablelow));
    }
    // Check if we need to change the direction.
    bool desired_dir =
          (req()->speed_.direction() == openlcb::SpeedType::FORWARD);
    if (lastDirMotAHi_ != desired_dir)
    {
        motorpwm_->get_channel(0)->set_duty(100);
        motorpwm_->get_channel(1)->set_duty(100);
        return sleep_and_call(&timer_, MSEC_TO_NSEC(1), STATE(do_speed));
    }
    return call_immediately(STATE(do_speed));
}

StateFlowBase::Action ESP32SpeedController::eoff_enablelow()
{
    motorpwm_->get_channel(0)->set_duty(0);
    motorpwm_->get_channel(1)->set_duty(0);
    return exit();
}

StateFlowBase::Action ESP32SpeedController::do_speed()
{
    // We set the pins explicitly for safety
    bool desired_dir =
          (req()->speed_.direction() == openlcb::SpeedType::FORWARD);
    int lo_pin;
    if (desired_dir)
    {
        motorpwm_->get_channel(1)->set_duty(100);
        lo_pin = 0;
    }
    else
    {
        motorpwm_->get_channel(0)->set_duty(100);
        lo_pin = 1;
    }
    double fill_rate = req()->speed_.mph();
    if (fill_rate >= 128) fill_rate = 128;
    int fill = (fill_rate / 128.0) * 100;
    motorpwm_->get_channel(lo_pin)->set_duty(fill);
    lastDirMotAHi_ = desired_dir;
    return release_and_exit();    
}

ConfigUpdateListener::UpdateAction 
      ESP32SpeedController::apply_configuration(int fd, 
                                                bool initial_load,
                                                BarrierNotifiable *done)
{
    AutoNotify an(done);
    auto config_freq = mpar_.pwm_frequency().read(fd);
    printf("pwm freq = %d\n", config_freq);
    period_ = 1000000000 / config_freq;
    motorpwm_->get_channel(0)->set_period(period_);
    return UPDATED;
}

void ESP32SpeedController::factory_reset(int fd)
{
    mpar_.pwm_frequency().write(
        fd, mpar_.pwm_frequency_options().defaultvalue());
}

void ESP32S3Train::set_speed(openlcb::SpeedType speed)
{
    lastSpeed_ = speed;
    estop = false;
    if (speed_controller_ == nullptr) return;
    speed_controller_->call_speed(speed);
    if (f0)
    {
        if (speed.direction() == openlcb::SpeedType::FORWARD)
        {
            set_fn(2,0);
            set_fn(1,1);
        }
        else
        {
            set_fn(1,0);
            set_fn(2,1);
        }
    }
}

void ESP32S3Train::set_emergencystop()
{
    estop = true;
    lastSpeed_.set_mph(0); // keeps direction
    if (speed_controller_ == nullptr) return;
    speed_controller_->call_estop();
}

void ESP32S3Train::set_fn(uint32_t address, uint16_t value)
{
    switch (address)
    {
    case 0:
        f0 = value;
        if (!value)
        {
            set_fn(1,0);
            set_fn(2,0);
        }
        else if (lastSpeed_.direction() == openlcb::SpeedType::FORWARD)
        {
            set_fn(1,1);
            set_fn(2,0);
        }
        else
        {
            set_fn(1,0);
            set_fn(2,1);
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        {
            int index = address - 1;
            states[index] = value != 0;
            if (!states[index])
            {
                functionpwm_->get_channel(index)->set_duty(0);
            }
            else
            {
                switch (functionConfig_[index].phase)
                {
                case Steady:
                    functionpwm_->get_channel(index)->set_duty(functionConfig_[index].brightness);
                    break;
                case SlowA:
                case MediumA:
                case FastA:
                case SlowB:
                case MediumB:
                case FastB:
                    break;
                }
            }
        }
        break;
    }
}

void ESP32S3Train::blink(bool AFast, bool AMedium, bool ASlow)
{
    for (int i = 0; i < NUM_FUNCTIONS; i++)
    {
        if (states[i])
        {
            switch (functionConfig_[i].phase)
            {
            case Steady: break;
            case SlowA:
                if (ASlow)
                {
                    functionpwm_->get_channel(i)->set_duty(functionConfig_[i].brightness);
                }
                else
                {
                    functionpwm_->get_channel(i)->set_duty(0);
                }
                break;
            case MediumA:
                if (AMedium)
                {
                    functionpwm_->get_channel(i)->set_duty(functionConfig_[i].brightness);
                }
                else
                {
                    functionpwm_->get_channel(i)->set_duty(0);
                }
                break;
            case FastA:
                if (AFast)
                {
                    functionpwm_->get_channel(i)->set_duty(functionConfig_[i].brightness);
                }
                else
                {
                    functionpwm_->get_channel(i)->set_duty(0);
                }
                break;
            case SlowB:
                if (!ASlow)
                {
                    functionpwm_->get_channel(i)->set_duty(functionConfig_[i].brightness);
                }
                else
                {
                    functionpwm_->get_channel(i)->set_duty(0);
                }
                break;
            case MediumB:
                if (!AMedium)
                {
                    functionpwm_->get_channel(i)->set_duty(functionConfig_[i].brightness);
                }
                else
                {
                    functionpwm_->get_channel(i)->set_duty(0);
                }
                break;
            case FastB:
                if (!AFast)
                {
                    functionpwm_->get_channel(i)->set_duty(functionConfig_[i].brightness);
                }
                else
                {
                    functionpwm_->get_channel(i)->set_duty(0);
                }
                break;
            }
        }
    }
}

uint16_t ESP32S3Train::get_fn(uint32_t address)
{
    switch (address)
    {
    case 0:
        return f0 ? 1 : 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        {
            int index = address -1;
            return states[index] ? 1 : 0;
        }
        break;
    }
    return 0;
}

uint32_t ESP32S3Train::legacy_address()
{
    return 883;
}

dcc::TrainAddressType ESP32S3Train::legacy_address_type()
{
    return dcc::TrainAddressType::DCC_LONG_ADDRESS;
}


ConfigUpdateListener::UpdateAction 
      ESP32S3Train::apply_configuration(int fd, bool initial_load,
                                        BarrierNotifiable *done)
{
    AutoNotify an(done);
    for (int i = 0; i < NUM_FUNCTIONS; i++)
    {
        FunctionConsumerConfig func = functions_.entry(i);
        functionConfig_[i].phase = (PhaseType) func.phase().read(fd);
        functionConfig_[i].brightness = func.brightness().read(fd);
    }
    return UPDATED;
}
void ESP32S3Train::factory_reset(int fd)
{
    for (int i = 0; i < NUM_FUNCTIONS; i++)
    {
        FunctionConsumerConfig func = functions_.entry(i);
        func.phase().write(fd, func.phase_options().defaultvalue());
        func.brightness().write(fd, func.brightness_options().defaultvalue());
    }
}

