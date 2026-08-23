// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Aug 17 15:54:18 2026
//  Last Modified : <260819.1539>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2026  Robert Heller D/B/A Deepwoods Software
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

#ifndef __ESP32STDI2S_HXX
#define __ESP32STDI2S_HXX

#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "esp_check.h"
#include <hal/gpio_types.h>
#include <utils/Atomic.hxx>
#include <unistd.h>
#include <vector>
#include "utils/macros.h"

namespace openmrn_esp32
{

class Esp32STDI2S : private Atomic
{
public:
    
    /// Constructor.
    ///
    /// @param path Base path to use for I2S std drivers.
    Esp32STDI2S(const char * const path = "/dev/i2s");
    
    /// Destructor.
    ~Esp32STDI2S();
    
    /// Initializes the underlying I2S controller hardware and VFS interface.
    ///
    /// @param bclk GPIO pin to use for I2S Bit Clock
    /// @param dout GPIO pin to use for I2S data out
    /// @param ws GPIO pin to use for I2S word select (LR Clock)
    /// @param sample_rate_hz sample rate.
    /// @param port I2S controller to initialize.
    void hw_init(const gpio_num_t bclk, const gpio_num_t dout, 
                 const gpio_num_t ws,
                 uint32_t sample_rate_hz = 16000, i2s_port_t port = I2S_NUM_0);
    
    /// VFS implementation of write(fd, buf, size)
    ///
    /// @param fd is the file descriptor being written to.
    /// @param buf is the buffer containing the data to be written.
    /// @param size is the size of the buffer.
    ///
    /// @return number of bytes written or -1 if there is the write would be a
    /// blocking operation.
    ///
    /// NOTE: The provided fd is used internally to determine which I2S
    /// controller should be used.
    ssize_t write(int fd, const void *buf, size_t size);
    
    /// VFS implementation of read(fd, buf, size)
    ///
    /// @param fd is the file descriptor being read from.
    /// @param buf is the buffer containing the data to be read.
    /// @param size is the size of the buffer.
    ///
    /// @return number of bytes read or -1 if there is the read would be a
    /// blocking operation.
    ///
    /// NOTE: The provided fd is used internally to determine which I2S
    /// controller should be used.
    ssize_t read(int fd, void *buf, size_t size);
    
    /// VFS implementation of open(path, flags, mode).
    ///
    /// @param path is the path to the file being opened.
    /// @param flags are the flags to use for opened file.
    /// @param mode is the mode to use for the opened file.
    ///
    /// @return 0 upon success, -1 upon failure with errno containing the cause.
    int open(const char *path, int flags, int mode);
    
    /// VFS implementation of close(fd).
    ///
    /// @param fd is the file descriptor to close.
    ///
    /// @return zero upon success, negative value with errno for failure.
    int close(int fd);
    
    
private:
    /// VFS Mount point.
    const char * const path_;
    
    /// Tracking structure used to map file handles to an I2S controller and
    /// address.
    struct i2s_device_t
    {
        /// I2S Controller that this file handle will use.
        i2s_port_t port;
        
        
        /// Assigned file handle for this entry.
        int fd;
    };
    
    /// Collection of I2S devices that have been opened.
    std::vector<i2s_device_t> devices_;
    
    /// Internal tracking for initialization of the underlying I2S hardware.
    bool i2sInitialized_[SOC_I2S_NUM];
    i2s_chan_handle_t i2s_tx_chans_[SOC_I2S_NUM];
    i2s_chan_handle_t i2s_rx_chans_[SOC_I2S_NUM];
    /// Internal tracking for the VFS adapter layer.
    bool vfsInitialized_{false};
    
    /// VFS adapter for write(fd, buf, size)
    ///
    /// @param ctx is the @ref Esp32STDI2S instance to invoke.
    /// @param fd is the file descriptor being written to.
    /// @param buf is the buffer containing the data to be written.
    /// @param size is the size of the buffer.
    /// @return number of bytes written or -1 if there is the write would be a
    /// blocking operation.
    static ssize_t vfs_write_(void *ctx, int fd, const void *buf, size_t size)
    {
        HASSERT(ctx != NULL);
        Esp32STDI2S *i2s = reinterpret_cast<Esp32STDI2S *>(ctx);
        return i2s->write(fd, buf, size);
    }
    /// VFS adapter for read(fd, buf, size)
    ///
    /// @param ctx is the @ref Esp32STDI2S instance to invoke.
    /// @param fd is the file descriptor being read from.
    /// @param buf is the buffer to write into.
    /// @param size is the size of the buffer.
    /// @return number of bytes read or -1 if there is the read would be a
    /// blocking operation.
    static ssize_t vfs_read_(void *ctx, int fd, void *buf, size_t size)
    {
        HASSERT(ctx != NULL);
        Esp32STDI2S *i2s = reinterpret_cast<Esp32STDI2S *>(ctx);
        return i2s->read(fd, buf, size);
    }
    /// VFS adapter for open(path, flags, mode).
    ///
    /// @param ctx is the @ref Esp32STDI2S instance to invoke.
    /// @param path is the path to the file being opened.
    /// @param flags are the flags to use for opened file.
    /// @param mode is the mode to use for the opened file.
    ///
    /// @return 0 upon success, -1 upon failure with errno containing the cause.
    static int vfs_open_(void *ctx, const char *path, int flags, int mode)
    {
        HASSERT(ctx != NULL);
        Esp32STDI2S *i2s = reinterpret_cast<Esp32STDI2S *>(ctx);
        return i2s->open(path,flags,mode);
    }
    /// VFS adapter for close(fd).
    ///
    /// @param ctx is the @ref Esp32STDI2S instance to invoke.
    /// @param fd is the file descriptor to close.
    ///
    /// @return zero upon success, negative value with errno for failure.
    static int vfs_close_(void *ctx, int fd)
    {
        HASSERT(ctx != NULL);
        Esp32STDI2S *i2s = reinterpret_cast<Esp32STDI2S *>(ctx);
        return i2s->close(fd);
    }
    /// VFS adapter for ioctl.
    ///
    /// @param ctx is the @ref Esp32STDI2S instance to invoke.
    /// @param fd is the file descriptor to operate on.
    /// @param cmd is the command to execute.
    /// @param args is the args for the command.
    ///
    /// This method is currently a NO-OP.
    ///
    /// @return zero upon success, negative value with errno for failure.
    static int vfs_ioctl_(void *ctx, int fd, int cmd, va_list args)
    {
        HASSERT(ctx != NULL);
        return 0;
    }
    /// VFS adapter for fcntl(fd, cmd, arg).
    ///
    /// @param ctx is the @ref Esp32STDI2S instance to invoke.
    /// @param fd to operate on.
    /// @param cmd to be executed.
    /// @param arg arg to be used for the operation.
    ///
    /// This method is currently a NO-OP.
    ///
    /// @return zero upon success, negative value with errno for failure.
    static int vfs_fcntl_(void *ctx, int fd, int cmd, int arg)
    {
        HASSERT(ctx != NULL);
        return 0;
    }
};

}

#endif // __ESP32STDI2S_HXX

