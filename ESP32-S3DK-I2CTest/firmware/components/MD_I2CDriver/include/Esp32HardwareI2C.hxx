
/** \copyright
 * Copyright (c) 2023, Mike Dunston
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are  permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \file Esp32HardwareI2C.hxx
 *
 * I2C driver implementation for OpenMRN. This leverages the ESP-IDF I2C driver
 * implementation providing a VFS interface.
 *
 * @author Mike Dunston
 * @date 8 Feb 2023
 */

#ifndef _FREERTOS_DRIVERS_ESP32_ESP32HARDWAREI2C_HXX_
#define _FREERTOS_DRIVERS_ESP32_ESP32HARDWAREI2C_HXX_

#include <algorithm>
#include "i2c.h"
#include "i2c-dev.h"
#include <unistd.h>
#include <driver/i2c.h>
#include <hal/gpio_types.h>
#include <utils/Atomic.hxx>
#include <vector>

namespace openmrn_arduino
{

class Esp32HardwareI2C : private Atomic
{
public:
    /// Constructor
    /// @param sda 
    /// @param scl 
    /// @param port 
    /// @param path 
    Esp32HardwareI2C(const char * const path = "/dev/i2c");

    /// Destructor.
    ~Esp32HardwareI2C();

    /// Initializes the underlying I2C controller hardware and VFS interface.
    ///
    /// NOTE: This must be called prior to usage.
    void hw_init(const gpio_num_t sda, const gpio_num_t scl,
                 const uint32_t bus_speed, const i2c_port_t port = I2C_NUM_0);

    /// Utility method to perform a scan for all devices on the I2C bus.
    void scan(const i2c_port_t port);

    ssize_t write(int fd, const void *buf, size_t size);
    ssize_t read(int fd, void *buf, size_t size);
    int open(const char *path, int flags, int mode);
    int close(int fd);
    int ioctl(int fd, int cmd, va_list args);

private:
    const char * const path_;

    static constexpr TickType_t I2C_TIMEOUT = pdMS_TO_TICKS(1000);
    static constexpr uint32_t I2C_BUS_SPEED = 400000;

    struct i2c_device_t
    {
        i2c_port_t port;
        int address;
        int fd;
    };

    /// Collection of I2C devices that have been opened.
    std::vector<i2c_device_t> devices_;

    bool i2cInitialized_[SOC_I2C_NUM];
    bool vfsInitialized_{false};

    int transfer_messages(const i2c_port_t port, struct i2c_msg *msgs, int num);
};

}; // namespace openmrn_arduino

using openmrn_arduino::Esp32HardwareI2C;

#endif // _FREERTOS_DRIVERS_ESP32_ESP32HARDWAREI2C_HXX_