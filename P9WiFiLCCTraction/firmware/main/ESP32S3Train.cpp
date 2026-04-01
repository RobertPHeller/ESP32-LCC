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
//  Last Modified : <260401.1504>
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
#include "freertos_drivers/common/PWM.hxx"
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
    if (directionMode_ == Reversed) 
    {
        if (lo_pin == 0)
        {
            lo_pin = 1;
        }
        else
        {
            lo_pin = 0;
        }
    }
    double fill_rate = req()->speed_.mph();
    if (fill_rate >= 128) fill_rate = 128;
    int fill = (fill_rate / 128.0) * 100;
    if (speedMode_ == Basic)
    {
        fill = compute_basic_fill_(fill);
    }
    else
    {
        fill = compute_table_fill_(fill);
    }
    motorpwm_->get_channel(lo_pin)->set_duty(fill);
    lastDirMotAHi_ = desired_dir;
    LOG(INFO,"[ESP32SpeedController] do_speed(): fill = %d, desired_dir = %d",fill,desired_dir);
    return release_and_exit();    
}

int ESP32SpeedController::compute_basic_fill_(int rawfill)
{
    double x1,y1,x2,y2,x;
    x = rawfill;
    LOG(INFO,"[ESP32SpeedController] compute_basic_fill_(): x = %f",x);
    /* use: vstart_, vmid_, and vhigh_ */
    if (rawfill >= 50)
    {
        /* between vmid_ and vhigh_ */
        x1 = 50.0;
        y1 = vmid_;
        x2 = 100.0;
        y2 = vhigh_;
    }
    else
    {
        /* between vstart_ and vmid_ */
        x1 = 0.0;
        y1 = vstart_;
        x2 = 50.0;
        y2 = vmid_;
    }
    double slope = (y2 - y1) / (x2 - x1);
    double y = (x-x1) * slope + y1;
    LOG(INFO,"[ESP32SpeedController] compute_basic_fill_(): slope = %f, y = %f",slope,y);
    return round((y/255.0)*100);
}

int ESP32SpeedController::compute_table_fill_(int rawfill)
{
    /* use: speed_table_[0] ... speed_table_[27] */
    double x1,y1,x2,y2,x;
    x = rawfill;
    size_t ix = (x / 100.0) *  27.0;
    if (x == 0.0) 
    {
        return (speed_table_[0] / 255.0)*100;
    }
    else if (ix == 27)
    {
        return (speed_table_[27] / 255.0)*100;
    }
    else
    {
        x1 = (ix / 27.0) * 100.0;
        y1 = speed_table_[ix];
        x2 = ((ix + 1) / 27.0) * 100.0;
        y2 = speed_table_[ix+1];
        double slope = (y2 - y1) / (x2 - x1);
        double y = (x-x1) * slope + y1;
        return round((y/255.0)*100);
    }
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
    if (mpar_.direction_mode().read(fd) == 0)
    {
        directionMode_ = Normal;
    }
    else
    {
        directionMode_ = Reversed;
    }
    if (mpar_.speed_mode().read(fd) == 0)
    {
        speedMode_ = Basic;
    }
    else
    {
        speedMode_ = Table;
    }
    vstart_ = mpar_.basic().vstart().read(fd);
    vmid_ = mpar_.basic().vmid().read(fd);
    vhigh_ = mpar_.basic().vhigh().read(fd);
    speed_table_[0] = mpar_.table().bar0().read(fd);
    speed_table_[1] = mpar_.table().bar1().read(fd);
    speed_table_[2] = mpar_.table().bar2().read(fd);
    speed_table_[3] = mpar_.table().bar3().read(fd);
    speed_table_[4] = mpar_.table().bar4().read(fd);
    speed_table_[5] = mpar_.table().bar5().read(fd);
    speed_table_[6] = mpar_.table().bar6().read(fd);
    speed_table_[7] = mpar_.table().bar7().read(fd);
    speed_table_[8] = mpar_.table().bar8().read(fd);
    speed_table_[9] = mpar_.table().bar9().read(fd);
    speed_table_[10] = mpar_.table().bar10().read(fd);
    speed_table_[11] = mpar_.table().bar11().read(fd);
    speed_table_[12] = mpar_.table().bar12().read(fd);
    speed_table_[13] = mpar_.table().bar13().read(fd);
    speed_table_[14] = mpar_.table().bar14().read(fd);
    speed_table_[15] = mpar_.table().bar15().read(fd);
    speed_table_[16] = mpar_.table().bar16().read(fd);
    speed_table_[17] = mpar_.table().bar17().read(fd);
    speed_table_[18] = mpar_.table().bar18().read(fd);
    speed_table_[19] = mpar_.table().bar19().read(fd);
    speed_table_[20] = mpar_.table().bar20().read(fd);
    speed_table_[21] = mpar_.table().bar21().read(fd);
    speed_table_[22] = mpar_.table().bar22().read(fd);
    speed_table_[23] = mpar_.table().bar23().read(fd);
    speed_table_[24] = mpar_.table().bar24().read(fd);
    speed_table_[25] = mpar_.table().bar25().read(fd);
    speed_table_[26] = mpar_.table().bar26().read(fd);
    speed_table_[27] = mpar_.table().bar27().read(fd);
    return UPDATED;
}

void ESP32SpeedController::factory_reset(int fd)
{
    mpar_.pwm_frequency().write(
        fd, mpar_.pwm_frequency_options().defaultvalue());
    mpar_.direction_mode().write(
        fd, mpar_.direction_mode_options().defaultvalue());
    mpar_.speed_mode().write(
        fd, mpar_.speed_mode_options().defaultvalue());
    
    mpar_.basic().vstart().write(
        fd, mpar_.basic().vstart_options().defaultvalue());
    mpar_.basic().vmid().write(
        fd, mpar_.basic().vmid_options().defaultvalue());
    mpar_.basic().vhigh().write(
        fd, mpar_.basic().vhigh_options().defaultvalue());
    
    mpar_.table().bar0().write(
        fd, mpar_.table().bar0_options().defaultvalue());
    mpar_.table().bar1().write(
        fd, mpar_.table().bar1_options().defaultvalue());
    mpar_.table().bar2().write(
        fd, mpar_.table().bar2_options().defaultvalue());
    mpar_.table().bar3().write(
        fd, mpar_.table().bar3_options().defaultvalue());
    mpar_.table().bar4().write(
        fd, mpar_.table().bar4_options().defaultvalue());
    mpar_.table().bar5().write(
        fd, mpar_.table().bar5_options().defaultvalue());
    mpar_.table().bar6().write(
        fd, mpar_.table().bar6_options().defaultvalue());
    mpar_.table().bar7().write(
        fd, mpar_.table().bar7_options().defaultvalue());
    mpar_.table().bar8().write(
        fd, mpar_.table().bar8_options().defaultvalue());
    mpar_.table().bar9().write(
        fd, mpar_.table().bar9_options().defaultvalue());
    mpar_.table().bar10().write(
        fd, mpar_.table().bar10_options().defaultvalue());
    mpar_.table().bar11().write(
        fd, mpar_.table().bar11_options().defaultvalue());
    mpar_.table().bar12().write(
        fd, mpar_.table().bar12_options().defaultvalue());
    mpar_.table().bar13().write(
        fd, mpar_.table().bar13_options().defaultvalue());
    mpar_.table().bar14().write(
        fd, mpar_.table().bar14_options().defaultvalue());
    mpar_.table().bar15().write(
        fd, mpar_.table().bar15_options().defaultvalue());
    mpar_.table().bar16().write(
        fd, mpar_.table().bar16_options().defaultvalue());
    mpar_.table().bar17().write(
        fd, mpar_.table().bar17_options().defaultvalue());
    mpar_.table().bar18().write(
        fd, mpar_.table().bar18_options().defaultvalue());
    mpar_.table().bar19().write(
        fd, mpar_.table().bar19_options().defaultvalue());
    mpar_.table().bar20().write(
        fd, mpar_.table().bar20_options().defaultvalue());
    mpar_.table().bar21().write(
        fd, mpar_.table().bar21_options().defaultvalue());
    mpar_.table().bar22().write(
        fd, mpar_.table().bar22_options().defaultvalue());
    mpar_.table().bar23().write(
        fd, mpar_.table().bar23_options().defaultvalue());
    mpar_.table().bar24().write(
        fd, mpar_.table().bar24_options().defaultvalue());
    mpar_.table().bar25().write(
        fd, mpar_.table().bar25_options().defaultvalue());
    mpar_.table().bar26().write(
        fd, mpar_.table().bar26_options().defaultvalue());
    mpar_.table().bar27().write(
        fd, mpar_.table().bar27_options().defaultvalue());

}

void ESP32S3Train::set_speed(openlcb::SpeedType speed)
{
    lastSpeed_ = speed;
    estop = false;
    if (speed_controller_ == nullptr) return;
    speed_controller_->call_speed(speed);
    if (get_fn(0))
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

void ESP32FunctionController::set_fn(uint32_t address, uint16_t value,
                                     openlcb::SpeedType lastSpeed)
{
    switch (address)
    {
    case 0:
        f0 = value;
        if (!value)
        {
            set_fn(1,0,lastSpeed);
            set_fn(2,0,lastSpeed);
        }
        else if (lastSpeed.direction() == openlcb::SpeedType::FORWARD)
        {
            set_fn(1,1,lastSpeed);
            set_fn(2,0,lastSpeed);
        }
        else
        {
            set_fn(1,0,lastSpeed);
            set_fn(2,1,lastSpeed);
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

void ESP32FunctionController::blink(bool AFast, bool AMedium, bool ASlow)
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

uint16_t ESP32FunctionController::get_fn(uint32_t address)
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
      ESP32FunctionController::apply_configuration(int fd, bool initial_load,
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
void ESP32FunctionController::factory_reset(int fd)
{
    for (int i = 0; i < NUM_FUNCTIONS; i++)
    {
        FunctionConsumerConfig func = functions_.entry(i);
        func.phase().write(fd, func.phase_options().defaultvalue());
        func.brightness().write(fd, func.brightness_options().defaultvalue());
    }
}

