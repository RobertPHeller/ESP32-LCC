// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Aug 22 12:52:52 2026
//  Last Modified : <260822.1609>
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

#ifndef __AUDIOMIXER_HXX
#define __AUDIOMIXER_HXX

#include <utils/Atomic.hxx>
#include <unistd.h>
#include <vector>
#include "utils/macros.h"


class AudioMixer : private Atomic
{
public:
    /// Constructor.
    ///
    /// @param path Base path to use for mixer
    AudioMixer(const char * const path = "/dev/mixer");
    
    /// Destructor.
    ///
    ~AudioMixer();
    
    /// VFS implementation of write(fd, buf, size) 
    /// @param fd is the file descriptor being written to.
    /// @param buf is the buffer containing the data to be written.
    /// @param size is the size of the buffer.
    ///
    /// @return number of bytes written or -1 if there is the write would be a
    /// blocking operation.
    ///
    /// NOTE: The provided fd is used internally to determine which mix channel
    /// to use.
    ssize_t write(int fd, const void *buf, size_t size);
    
    /// VFS implementation of open(path, flags, mode).
    ///
    /// @param path is the path to the file being opened.  The digit at the end
    /// is the channel number to open
    /// @param flags are the flags to use for opened file.  (Only O_WRONLY)
    /// @param mode is the mode to use for the opened file. (not used)
    /// @return 0 upon success, -1 upon failure with errno containing the cause.
    int open(const char *path, int flags, int mode);
    
    /// VFS implementation of close(fd).
    ///
    /// @param fd is the file descriptor to close.
    ///
    /// @return zero upon success, negative value with errno for failure.
    int close(int fd); 
    
    /// Flush mix buffer to I2S.  Resets all channels when flush is complete.
    ///
    /// @param i2s_fp I2S file descriptor.
    /// @return number of bytes written or -1 if there is the write would be a
    /// blocking operation.
    ssize_t FlushToI2S(int i2s_fp);
    
private:
    /// VFS Mount point.
    const char * const path_;
    
    /// Mix buffer
    uint16_t *mixBuffer_;
    
    /// Mix buffer size
    ssize_t mixBufferSize_;
    
    /// Mix buffer fill index
    ssize_t mixBufferFill_;
    
    /// Tracking structure used to map file handles to a mix channel index.
    ///
    struct mix_channel_t
    {
        /// Mix channel index
        ssize_t mix_channel_index;
        /// Assigned file handle for this entry.
        int fd;
    };
    /// Collection of mix hannels that have been opened.
    std::vector<mix_channel_t> mix_channels_;
    /// Internal tracking for the VFS adapter layer.
    bool vfsInitialized_{false};
    
    /// VFS adapter for write(fd, buf, size) 
    ///
    /// @param ctx is the @ref AudioMixer instance to invoke.
    /// @param fd is the file descriptor being written to.
    /// @param buf is the buffer containing the data to be written.
    /// @param size is the size of the buffer.
    /// @return number of bytes written or -1 if there is the write would be a
    /// blocking operation.
    static ssize_t vfs_write_(void *ctx, int fd, const void *buf, size_t size)
    {
        HASSERT(ctx != NULL);
        AudioMixer *mixer = reinterpret_cast<AudioMixer *>(ctx);
        return mixer->write(fd, buf, size);
    }
    /// VFS adapter for read(fd, buf, size)
    ///
    /// @param ctx is the @ref AudioMixer instance to invoke.
    /// @param fd is the file descriptor being read from.
    /// @param buf is the buffer to write into.
    /// @param size is the size of the buffer.
    /// @return number of bytes read or -1 if there is the read would be a
    /// blocking operation.
    /// This is a noop.
    static ssize_t vfs_read_(void *ctx, int fd, void *buf, size_t size)
    {
        HASSERT(ctx != NULL);
        return 0;
    }
    /// VFS adapter for open(path, flags, mode).
    ///
    /// @param ctx is the @ref AudioMixer instance to invoke.
    /// @param path is the path to the file being opened.
    /// @param flags are the flags to use for opened file.
    /// @param mode is the mode to use for the opened file.
    ///
    /// @return 0 upon success, -1 upon failure with errno containing the cause.
    static int vfs_open_(void *ctx, const char *path, int flags, int mode)
    {
        HASSERT(ctx != NULL);
        AudioMixer *mixer = reinterpret_cast<AudioMixer *>(ctx);
        return mixer->open(path,flags,mode);
    }
    /// VFS adapter for close(fd).
    ///
    /// @param ctx is the @ref AudioMixer instance to invoke.
    /// @param fd is the file descriptor to close.
    ///
    /// @return zero upon success, negative value with errno for failure.
    static int vfs_close_(void *ctx, int fd)
    {
        HASSERT(ctx != NULL);
        AudioMixer *mixer = reinterpret_cast<AudioMixer *>(ctx);
        return mixer->close(fd);
    }
    /// VFS adapter for ioctl.
    ///
    /// @param ctx is the @ref AudioMixer instance to invoke.
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
    /// @param ctx is the @ref AudioMixer instance to invoke.
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

#endif // __AUDIOMIXER_HXX

