// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : 2025-11-29 20:06:48
//  Last Modified : <251130.1610>
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
/// @file PhysicalTrainNode.hxx
/// @author Robert Heller
/// @date 2025-11-29 20:06:48
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __ESP32S3TRAIN_HXX
#define __ESP32S3TRAIN_HXX

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


struct SpeedRequest
{
    SpeedRequest()
    {
        reset();
    }
    openlcb::SpeedType speed_;
    bool emergencyStop_;
    void reset()
    {
        speed_ = 0.0;
        emergencyStop_ = false;
    }
};

class ESP32SpeedController : public StateFlow<Buffer<SpeedRequest>, QList<2>>,
                             private DefaultConfigUpdateListener
{
public:
    ESP32SpeedController(Service *s, MotorControl mpar,Esp32Ledc *motorpwm)
                : StateFlow<Buffer<SpeedRequest>, QList<2>>(s)
          , mpar_(mpar)
          , motorpwm_(motorpwm)
    {
    }
    void call_speed(openlcb::Velocity speed)
    {
        auto *b = alloc();
        b->data()->speed_ = speed;
        send(b, 1);
    }
    void call_estop()
    {
        auto *b = alloc();
        b->data()->emergencyStop_ = true;
        send(b, 0);
    }
    
private:
    Action entry() override;
    Action eoff_enablelow();
    Action do_speed();
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    virtual void factory_reset(int fd);
    SpeedRequest *req()
    {
        return message()->data();
    }
    MotorControl mpar_;
    long long period_ =
          1000000000 / MotorControl::pwm_frequency_options().defaultvalue();
    Esp32Ledc *motorpwm_;
    StateFlowTimer timer_{this};
    bool lastDirMotAHi_{false};
};

class ESP32S3Train : public openlcb::TrainImpl, private DefaultConfigUpdateListener 
{
public:
    ESP32S3Train(FunctionConsumers functions,Esp32Ledc *functionpwm)
          : functions_(functions)
    , speed_controller_(nullptr)
    , functionpwm_(functionpwm)
    {
    }
    void set_speed_controller(ESP32SpeedController *speed_controller)
    {
        speed_controller_ = speed_controller;
    }
    virtual void set_speed(openlcb::SpeedType speed);
    virtual openlcb::SpeedType get_speed()
    {
        return lastSpeed_;
    }
    virtual void set_emergencystop();
    virtual bool get_emergencystop() {
        return estop;
    }
    virtual void set_fn(uint32_t address, uint16_t value);
    virtual uint16_t get_fn(uint32_t address);
    virtual uint32_t legacy_address();
    virtual dcc::TrainAddressType legacy_address_type();
    
private:
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    virtual void factory_reset(int fd);
    FunctionConsumers functions_;
    openlcb::SpeedType lastSpeed_ = 0.0;
    bool estop = false;
    bool f0 = false;
    bool states[6] = {false,false,false,false,false,false};
    enum PhaseType {Steady,Pulse,SlowA,MediumA,FastA,SlowB,MediumB,FastB};
    struct {
        PhaseType phase;
        uint8_t pulsewidth;
        uint8_t brightness;
    } functionConfig_[NUM_FUNCTIONS] = {
        {Steady, 1, 50},
        {Steady, 1, 50},
        {Steady, 1, 50},
        {Steady, 1, 50},
        {Steady, 1, 50},
        {Steady, 1, 50}
    };
    ESP32SpeedController *speed_controller_;
    Esp32Ledc *functionpwm_;
};

extern const char ESP32_FDI[];

#endif // __ESP32S3TRAIN_HXX
