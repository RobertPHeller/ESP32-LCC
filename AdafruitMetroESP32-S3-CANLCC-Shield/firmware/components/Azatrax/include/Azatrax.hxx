/* 
 * Azatrax.cpp - Library for communication and control of sensor
 *    shields made by Azatrax, LLC.
 * Written by John Parsons for public use.  No warranty.
 * revisions:
 * 11-May-2018 - initial release
 * Tue Apr  4 09:59:46 2023 -- Adapted for OpenMRN / FreeRTOS -- Robert Heller
 * 
 */
#ifndef AZATRAX_HXX
#define AZATRAX_HXX

#include <stdint.h>

typedef uint8_t byte;
typedef bool boolean;

namespace azatrax
{

class Azatrax {
public:
    Azatrax(byte devAddr);	    // constructor with the device's I2C bus address
    ~Azatrax();	    // destructor
    
    void begin(const char *i2cpath);
    
    byte devAddr;   // allow public access to the device's I2C bus address

    /***********************************
     * getDetData
     * Returns a given data byte from our detector circuit.
     *
     ***********************************/
     byte getDetData(byte registerAddr);
     
    /***********************************
     * putDetData
     * Sends a given data byte to a specified register address 
     * of our detector circuit.
     * Returns 0x00 if communication completed successfully.
     * Returns non-zero if communication failed, probably due to
     *    the absence of a detector circuit at this I2C address.
     ***********************************/
     byte putDetData(byte registerAddr, byte writeData);

    /***********************************
     * detOccupied
     * Returns TRUE if the specified detector is sensing an object.
     * Input:  Detector number, range: 1 through (number of detectors)
     ***********************************/
    boolean detOccupied(byte detectorNum);

    /***********************************
     * detVacant
     * Returns TRUE if the specified detector is not sensing an object.
     * Input:  Detector number, range: 1 through (number of detectors)
     ***********************************/
    boolean detVacant(byte detectorNum);

    /***********************************
     * getAmbient
     * Returns the ambient level measured by the specified detector.
     * Input:  Detector number, range: 1 through (number of detectors)
     ***********************************/
    byte getAmbient(byte detectorNum);

    /***********************************
     * getSignalLevel
     * Returns the received signal level value for the specified detector.
     * Input:  Detector number, range: 1 through (number of detectors)
     ***********************************/
    byte getSignalLevel(byte detectorNum);

    /***********************************
     * getThreshold
     * Returns the threshold value for the specified detector.
     * Input:  Detector number, range: 1 through (number of detectors)
     ***********************************/
    byte getThreshold(byte detectorNum);

    /***********************************
     * setThreshold
     * Writes the given threshold value to the specified detector.
     * Input:  Detector number, range: 1 through (number of detectors).
     *          and the new value for the threshold.
     * Returns 0x00 if communication completed successfully.
     * Returns non-zero if communication failed, possibly due to
     *    the absence of a detector circuit at this I2C address,
     *    or if detector number is out of range.
     ***********************************/
    byte setThreshold(byte detectorNum, byte thresholdValue);

    /***********************************
     * stopwatchRunning
     * Returns TRUE if the specified stopwatch is running.
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    boolean stopwatchRunning(byte stopwatchNum);

    /***********************************
     * stopwatchStopped
     * Returns TRUE if the specified stopwatch is stopped (not running).
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    boolean stopwatchStopped(byte stopwatchNum);

    /***********************************
     * stopwatchDir
     * Returns 0 if the stopwatch has been reset and not yet started,
     *      else returns the sensor number that started the stopwatch.
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    byte stopwatchDir(byte stopwatchNum);

    /***********************************
     * stopwatchMin
     * Returns the minutes value for the specified stopwatch, range 0 to 255.
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    byte stopwatchMin(byte stopwatchNum);

    /***********************************
     * stopwatchSec
     * Returns the seconds value for the specified stopwatch, range 0 to 59.
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    byte stopwatchSec(byte stopwatchNum);

    /***********************************
     * stopwatch100
     * Returns the 1/100 seconds value for the specified stopwatch, range 0 to 99.
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    byte stopwatch100(byte stopwatchNum);

    /***********************************
     * stopwatchReset
     * Resets the specified stopwatch to zero and enables it to be triggered.
     * Each stopwatch must be reset after power-up in order to be triggered.
     * Input:  Stopwatch number, range: 1 through (number of stopwatches)
     ***********************************/
    void stopwatchReset(byte stopwatchNum);


private:
    byte _deviceAddr;
    int i2cfd_;
};

}
#endif // AZATRAX_HXX

