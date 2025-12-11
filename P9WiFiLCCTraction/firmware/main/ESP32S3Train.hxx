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
//  Last Modified : <251202.1349>
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

#include "Blink.hxx"
#include "hardware.hxx"
#include "FunctionConfig.hxx"
#include "MotorConfig.hxx"

/** Speed Request buffer object */
struct SpeedRequest
{
    /** Constructor: reset the fields. */
    SpeedRequest()
    {
        reset();
    }
    /** The speed value of the request. */
    openlcb::SpeedType speed_;
    /** Emergency Stop flag. */
    bool emergencyStop_;
    /** Reset the structure. */
    void reset()
    {
        speed_ = 0.0;
        emergencyStop_ = false;
    }
};
/** @brief Speed controller implementation.  
 * A StateFlow which takes a speed request and sets the PWM outputs to drive
 * the motor controller H-Bridge.
 */
class ESP32SpeedController : public StateFlow<Buffer<SpeedRequest>, QList<2>>,
                             private DefaultConfigUpdateListener
{
public:
    /** Constructor: set things up to process speed requests.
     * @param s The service.
     * @param mpar The motor configuration.
     * @param motorpwm The PWM object for the motor PWM lines.
     */
    ESP32SpeedController(Service *s, MotorControl mpar,Esp32Ledc *motorpwm)
                : StateFlow<Buffer<SpeedRequest>, QList<2>>(s)
          , mpar_(mpar)
          , motorpwm_(motorpwm)
    {
    }
    /** Helper to generate a speed change.
     * @param speed The new speed.
     */
    void call_speed(openlcb::Velocity speed)
    {
        auto *b = alloc();
        b->data()->speed_ = speed;
        send(b, 1);
    }
    /** Helper to generate an emergency stop.
     */
    void call_estop()
    {
        auto *b = alloc();
        b->data()->emergencyStop_ = true;
        send(b, 0);
    }
    
private:
    /** Entry state: called when a new speed setting or emergency stop. */
    Action entry() override;
    /** Emergency stop release the brakes once stopped. */
    Action eoff_enablelow();
    /** Actually update the motor PWM settings. */
    Action do_speed();
    /** Apply a the configuration settings.
     * @param fd Config file descriptor.
     * @param initial_load Initial load flag.
     * @param done Notifiable.
     */
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    /** Factory reset.
     * @param fd Config file descriptor. 
     */
    virtual void factory_reset(int fd);
    /** Return the current request data. */
    SpeedRequest *req()
    {
        return message()->data();
    }
    /** Motor parameters. */
    MotorControl mpar_;
    /** PWM period. */
    long long period_ =
          1000000000 / MotorControl::pwm_frequency_options().defaultvalue();
    /** Motor PWM. */
    Esp32Ledc *motorpwm_;
    /** State Flow Timer. */
    StateFlowTimer timer_{this};
    /** Last direction. */
    bool lastDirMotAHi_{false};
};

/** @brief Train implimentation.
 * This is the implimentation of a train.  It uses a speed controller to run
 * the train and directly handles the functions.
 */
class ESP32S3Train : public openlcb::TrainImpl, public Blinking,
                     private DefaultConfigUpdateListener 
{
public:
    /** Constructor: initialize the implimentation.
     * @param functions Function configurations.
     * @param functionpwm Function PWM.
     */
    ESP32S3Train(FunctionConsumers functions,Esp32Ledc *functionpwm)
          : functions_(functions)
    , speed_controller_(nullptr)
    , functionpwm_(functionpwm)
    {
    }
    /** Set the speed controller.
     * @param speed_controller The speed controller object.
     */
    void set_speed_controller(ESP32SpeedController *speed_controller)
    {
        speed_controller_ = speed_controller;
    }
    /** Set the speed.
     * @param speed The speed to set.
     */
    virtual void set_speed(openlcb::SpeedType speed);
    /** Get the speed.
     * @returns the speed.
     */
    virtual openlcb::SpeedType get_speed()
    {
        return lastSpeed_;
    }
    /** Set the emergency brake. */
    virtual void set_emergencystop();
    /** Get the state of the emergency brake.
     * @returns the emergence brake status.
     */
    virtual bool get_emergencystop() {
        return estop;
    }
    /** Set a function.
     * @param address The function number.  Only addresses from 0 through 6 are
     * used and other addresses are ignored.
     * @param value A value of 0 (zero) is off.  Any other value is on.
     */
    virtual void set_fn(uint32_t address, uint16_t value);
    /** Get a function.
     * @param address The function number.  Only addresses from 0 through 6 are
     * used and other addresses always return 0.
     * @returns the state of the address.
     */
    virtual uint16_t get_fn(uint32_t address);
    /** Legacy address. */
    virtual uint32_t legacy_address();
    /** Legacy address type. */
    virtual dcc::TrainAddressType legacy_address_type();
    /** Blink callback.
     * @param AFast True if the fast cycle is on (phase A).
     * @param AMedium True if the medium cycle is on (phase A).
     * @param ASlow True if the slow cycle is on (phase A).
     */
    virtual void blink(bool AFast, bool AMedium, bool ASlow);
private:
    /** Configuration apply function.
     * @param fd Config file descriptor.
     * @param initial_load Initial load flag.
     * @param done Notifiable.
     */
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    /** Factory reset function.
     * @param fd Config file descriptor.
     */
    virtual void factory_reset(int fd);
    /** Function configurations. */
    FunctionConsumers functions_;
    /** The last speed setting. */
    openlcb::SpeedType lastSpeed_ = 0.0;
    /** The state of the emergency brake. */
    bool estop = false;
    /** The state of Function 0. */
    bool f0 = false;
    /** The states of Functions 1 through 6. */
    bool states[6] = {false,false,false,false,false,false};
    /** The phase values. */
    enum PhaseType {Steady=1,SlowA=2,MediumA=3,FastA=4,SlowB=5,MediumB=6,FastB=7};
    /** Function confonfiguration. */
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
    /** The speed controller. */
    ESP32SpeedController *speed_controller_;
    /** The function PWM. */
    Esp32Ledc *functionpwm_;
};
/** The nodes FDI. */
extern const char ESP32_FDI[];

#endif // __ESP32S3TRAIN_HXX
