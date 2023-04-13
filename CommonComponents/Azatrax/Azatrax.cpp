/* 
 * Azatrax.cpp - Library for communication and control of sensor
 *    shields made by Azatrax, LLC.
 * Written by John Parsons for public use.  No warranty.
 * revisions:
 * 11-May-2018 - initial release
 * 
 */

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils/logging.h"
#include "utils/macros.h"
#include "stropts.h"
#include "i2c.h"
#include "i2c-dev.h"

#include "Azatrax.hxx"

namespace azatrax
{

Azatrax::Azatrax(byte deviceAddr)	// constructor
{
    _deviceAddr = deviceAddr;   // i2c bus address of the target device
}

Azatrax::~Azatrax() // destructor
{                   // nothing to destruct
}

void Azatrax::begin(const char *i2cpath)
{
    i2cfd_ = ::open(i2cpath, O_RDWR);
    HASSERT(i2cfd_ >= 0);
    ::ioctl(i2cfd_, I2C_SLAVE, _deviceAddr);
}

// valid range of detector numbers on an RIR4 circuit
static const byte MIN_DET = 1; // minimum number of detectors per circuit
static const byte MAX_DET = 4; // maximum number of detectors per circuit
static const byte MIN_STOPW = 1; // minimum number of stopwatches per circuit
static const byte MAX_STOPW = 2; // maximum number of stopwatches per circuit

// register addresses within an RIR4 detector circuit:
static const byte detStatesRA = 0x00;
static const byte detLevelRA[] = {0x10,0x20,0x30,0x40};
static const byte detThresholdRA[] = {0x11,0x21,0x31,0x41};
static const byte detAmbientRA[] = {0x12,0x22,0x32,0x42};
static const byte devStopwatchRA = 0x0A;   // stopwatch state bitmap
static const byte directionRA[] = {0xA3, 0xB3};    // direction registers
// Following are the register addresses for the minutes, seconds and
// 1/100th second registers for stopwatches A & B:
static const byte RIR4stopwMinRA[] = {0xA0,0xB0};  // minute registers
static const byte RIR4stopwSecRA[] = {0xA1,0xB1};  // seconds registers
static const byte RIR4stopw100RA[] = {0xA2,0xB2};  // 1/100th seconds

/***********************************
 * getDetData
 * Returns a given data byte from our detector circuit.
 *
 ***********************************/
byte Azatrax::getDetData(byte registerAddr)
{
    byte returnVal;

    returnVal = 0xFF;    // default return value
    
    size_t s = ::write(i2cfd_, &registerAddr, sizeof(registerAddr));
    if (s != sizeof(registerAddr))
    {
        return returnVal;
    }
    s = ::read(i2cfd_, &returnVal, sizeof(returnVal));
    if (s != sizeof(returnVal))
    {
        returnVal = 0xFF;
    }

    return returnVal;
} // end of getDetData()

 
/***********************************
 * putDetData
 * Sends a given data byte to a specified register address 
 * of our detector circuit.
 * Returns 0x00 if communication completed successfully.
 * Returns non-zero if communication failed, possibly due to
 *    the absence of a detector circuit at this I2C address.
 ***********************************/
byte Azatrax::putDetData(byte registerAddr, byte writeData)
{
    byte returnVal;
    byte payload[2];
    
    payload[0] = registerAddr;
    payload[1] = writeData;
    size_t s = ::write(i2cfd_, payload, sizeof(payload));
    if (s != sizeof(payload))
    {
        returnVal = (byte) s;
    }
    else
    {
        returnVal = 0;
    }
    
    return returnVal;
} // end of putDetData()

/***********************************
 * detOccupied
 * Returns TRUE if the specified detector is sensing an object.
 * Input:  Detector number, range: 1 through (number of detectors)
 ***********************************/
boolean Azatrax::detOccupied(byte detectorNum)
{
    boolean returnVal;
    byte detectorData;

    returnVal = false;

    // make sure the specified detector number is within the valid range
    if((MIN_DET <= detectorNum) && (detectorNum <= MAX_DET)) {
        // read the detector state bitmap from the detector circuit
        detectorData = getDetData(detStatesRA);

        // check the state of the specified detector,
        // detector #1 is bit 0 (lsb), detector #2 is bit 1, etc.
        if(detectorData & (0x01 << (detectorNum - 1))) {
            returnVal = true;
        }
    }
    return returnVal;
} // end of detOccupied()

/***********************************
 * detVacant
 * Returns TRUE if the specified detector is not sensing an object.
 * Input:  Detector number, range: 1 through (number of detectors)
 ***********************************/
boolean Azatrax::detVacant(byte detectorNum)
{
    if(true == detOccupied(detectorNum)) {
        return false;
    }
    else {
        return true;
    }
} // end of detVacant()

/***********************************
 * getAmbient
 * Returns the ambient level measured by the specified detector.
 * Inputs: I2C address if the circuit board
 *          Detector number, range: 1 through (number of detectors)
 ***********************************/
byte Azatrax::getAmbient(byte detectorNum)
{
    byte returnVal;

    returnVal = 0xFF;   // default return value

    // make sure the specified detector number is within the valid range
    if((MIN_DET <= detectorNum) && (detectorNum <= MAX_DET)) {
        returnVal = getDetData(detAmbientRA[detectorNum- 1]);
    }
    return returnVal;
} // end getAmbient()

/***********************************
 * getSignalLevel
 * Returns the received signal level value for the specified detector.
 * Inputs: I2C address if the circuit board
 *          Detector number, range: 1 through (number of detectors)
 ***********************************/
byte Azatrax::getSignalLevel(byte detectorNum)
{
    byte returnVal;

    returnVal = 0xFF;   // default return value

    // make sure the specified detector number is within the valid range
    if((MIN_DET <= detectorNum) && (detectorNum <= MAX_DET)) {
        returnVal = getDetData(detLevelRA[detectorNum- 1]);
    }
    return returnVal;
} // end getSignalLevel()

/***********************************
 * getThreshold
 * Returns the threshold value for the specified detector.
 * Inputs: I2C address if the circuit board
 *          Detector number, range: 1 through (number of detectors)
 ***********************************/
byte Azatrax::getThreshold(byte detectorNum)
{
    byte returnVal;

    returnVal = 0xFF;   // default return value

    // make sure the specified detector number is within the valid range
    if((MIN_DET <= detectorNum) && (detectorNum <= MAX_DET)) {
        returnVal = getDetData(detThresholdRA[detectorNum- 1]);
    }
    return returnVal;
} // end of getThreshold()

/***********************************
 * setThreshold
 * Writes the given threshold value to the specified detector.
 * Inputs: I2C address if the circuit board
 *          Detector number, range: 1 through (number of detectors)
 * Returns 0x00 if communication completed successfully.
 * Returns non-zero if communication failed, probably due to
 *    the absence of a detector circuit at this I2C address,
 *    or if detector number is out of range.
 ***********************************/
byte Azatrax::setThreshold(byte detectorNum, byte thresholdValue)
{
    byte returnVal;

    returnVal = 0xFF;   // default value

    // make sure the specified detector number is within the valid range
    if((MIN_DET <= detectorNum) && (detectorNum <= MAX_DET)) {
        returnVal = putDetData(detThresholdRA[detectorNum - 1], thresholdValue);
    }
    return returnVal;
}  // end of setThreshold()

/***********************************
 * stopwatchRunning
 * Returns TRUE if the specified stopwatch is running.
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
boolean Azatrax::stopwatchRunning(byte stopwatchNum)
{
    boolean returnVal;
    byte deviceData;

    returnVal = false;

    // make sure the specified stopwatch number is within the valid range
    if((MIN_STOPW <= stopwatchNum) && (stopwatchNum <= MAX_STOPW)) {
        // read the stopwatch state bitmap from the detector circuit
        deviceData = getDetData(devStopwatchRA);

        // check the state of the specified stopwatch,
        // stopwatch #1 is bit 0 (lsb), stopwatch #2 is bit 1, etc.
        if(deviceData & (0x01 << (stopwatchNum - 1))) {
            returnVal = true;
        }
    }
    return returnVal;
} // end of stopwatchRunning()

/***********************************
 * stopwatchStopped
 * Returns TRUE if the specified stopwatch is stopped (not running).
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
boolean Azatrax::stopwatchStopped(byte stopwatchNum)
{
    if(true == stopwatchRunning(stopwatchNum)) {
        return false;
    }
    else {
        return true;
    }
} // end of stopwatchStopped()

/***********************************
 * stopwatchDir
 * Returns 0 if the stopwatch has been reset and not yet started,
 *      else returns the sensor number that started the stopwatch.
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
byte Azatrax::stopwatchDir(byte stopwatchNum)
{
    return getDetData(directionRA[stopwatchNum - 1]);

} // end of stopwatchDir()

/***********************************
 * stopwatchMin
 * Returns the minutes value for the specified stopwatch, range 0 to 255.
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
byte Azatrax::stopwatchMin(byte stopwatchNum)
{
    return getDetData(RIR4stopwMinRA[stopwatchNum - 1]);
} // end of stopwatchMin()

/***********************************
 * stopwatchSec
 * Returns the seconds value for the specified stopwatch, range 0 to 59.
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
byte Azatrax::stopwatchSec(byte stopwatchNum)
{
    return getDetData(RIR4stopwSecRA[stopwatchNum - 1]);
} // end of stopwatchSec()

/***********************************
 * stopwatch100
 * Returns the 1/100 seconds value for the specified stopwatch, range 0 to 99.
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
byte Azatrax::stopwatch100(byte stopwatchNum)
{
    return getDetData(RIR4stopw100RA[stopwatchNum - 1]);
} // end of stopwatch100()

/***********************************
 * stopwatchReset
 * Resets the specified stopwatch to zero and enables it to be triggered.
 * This is done by writing zero to the stopwatch minutes register.
 * Each stopwatch must be reset after power-up in order to be triggered.
 * Input:  Stopwatch number, range: 1 through (number of stopwatches)
 ***********************************/
void Azatrax::stopwatchReset(byte stopwatchNum)
{
    putDetData(RIR4stopwMinRA[stopwatchNum - 1], 0x00);
} // end of stopwatchReset()

}
