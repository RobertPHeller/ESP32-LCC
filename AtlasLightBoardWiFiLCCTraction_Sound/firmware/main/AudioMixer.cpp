// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Aug 22 13:17:19 2026
//  Last Modified : <260822.1431>
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

static const char rcsid[] = "@(#) : $Id$";

#include <utils/Atomic.hxx>
#include <unistd.h>
#include <vector>
#include "stropts.h"
#include "AudioMixer.hxx"
#include "sdkconfig.h"
#include "utils/format_utils.hxx"
#include "utils/logging.h"
#include "utils/StringPrintf.hxx"
#include <sys/param.h>

#include <algorithm>

#if CONFIG_VFS_SUPPORT_TERMIOS
// remove defines added by arduino-esp32 core/esp32/binary.h which are
// duplicated in sys/termios.h which may be included by esp_vfs.h
#undef B110
#undef B1000000
#endif // CONFIG_VFS_SUPPORT_TERMIOS
#include <esp_vfs.h>
#include <string>
#include <sys/errno.h>

AudioMixer::AudioMixer(const char * const path)
      : path_(path)
, mixBuffer_(nullptr)
, mixBufferSize_(0)
, mixBufferFill_(0)
{
    esp_vfs_t vfs = {};
    vfs.write_p = vfs_write_;
    vfs.read_p = vfs_read_;
    vfs.open_p = vfs_open_;
    vfs.close_p = vfs_close_;
    vfs.fcntl_p = vfs_fcntl_;
    vfs.ioctl_p = vfs_ioctl_;
    vfs.flags = ESP_VFS_FLAG_CONTEXT_PTR;
    ESP_ERROR_CHECK(esp_vfs_register(path_, &vfs, this));
    
    vfsInitialized_ = true;
}

AudioMixer::~AudioMixer()
{
    if (vfsInitialized_)
    {
        ESP_ERROR_CHECK(esp_vfs_unregister(path_));
    }
    if (mixBuffer_ != nullptr) free(mixBuffer_);
}

int AudioMixer::open(const char *path, int flags, int mode)
{
    std::string path_str = path;
    mix_channel_t new_dev =
    {
        .mix_channel_index = 0,
        .fd = 0,
    };
    // scan existing devices to find a unique file handle number to return to
    // the caller. The file handle starts with zero and is set to the maximum
    // file handle found plus one. When a file handle is reclaimed there will
    // be gaps in the file handles which will not be reclaimed until entries
    // with higher file handle numbers are also reclaimed.
    {
        AtomicHolder h(this);
        
        if (!mix_channels_.empty())
        {
            for (auto &entry: mix_channels_)
            {
                if (entry.fd >= new_dev.fd)
                {
                    new_dev.fd = entry.fd + 1;
                }
            }
        }
        mix_channels_.push_back(new_dev);
    }
    LOG(INFO, "[AudioMixer] Using fd: %d for %s", new_dev.fd, path);
    return new_dev.fd;
}

int AudioMixer::close(int fd)
{
    AtomicHolder h(this);
    auto entry = std::find_if(mix_channels_.begin(), mix_channels_.end(),
    [fd](const auto &device)
    {
        return device.fd == fd;
    });
    
    // only delete the device if has been found.
    if (entry != mix_channels_.end())
    {
        mix_channels_.erase(entry);
    }
    
    return 0;
}
    
ssize_t AudioMixer::write(int fd, const void *buf, size_t size)
{
    AtomicHolder h(this);
    const uint16_t *wbuf = (uint16_t *) buf;
    size_t wsize = size / sizeof(uint16_t);
    auto entry = std::find_if(mix_channels_.begin(), mix_channels_.end(),
                              [fd](const auto &mix_channel)
                          {
                              return mix_channel.fd == fd;
                          });
    if (entry == mix_channels_.end())
    {
        // file handle not found, return an error.
        errno = EBADF;
        return -EBADF; 
    }
    else if (entry->fd < 0)
    {
        // no address has been defined for this file handle, return an error
            errno = EINVAL;
            return -EINVAL;
    }
    
    if ((entry->mix_channel_index+wsize) > mixBufferSize_)
    {
        ssize_t newspace = (entry->mix_channel_index+wsize) - mixBufferSize_;
        mixBuffer_ = (uint16_t *) realloc(mixBuffer_,entry->mix_channel_index+wsize*sizeof(uint16_t));
        mixBufferSize_ = entry->mix_channel_index+wsize;
        ssize_t newindex = mixBufferSize_ - newspace;
        memset(mixBuffer_+newindex,0,newspace*sizeof(uint16_t));
    }
    for (size_t i = 0; i < wsize; i++)
    {
        uint32_t sum =  mixBuffer_[entry->mix_channel_index+i];
        sum += wbuf[i];
        mixBuffer_[entry->mix_channel_index+i] = sum >> 1;
    }
    mixBufferFill_ = MAX(entry->mix_channel_index+wsize,mixBufferFill_);
    entry->mix_channel_index += wsize;
    return size;
}

ssize_t AudioMixer::FlushToI2S(int i2s_fp)
{
    AtomicHolder h(this);
    
    if (mixBufferFill_ == 0) return 0;
    ssize_t result = write(i2s_fp,mixBuffer_,mixBufferFill_/sizeof(uint16_t));
    mixBufferFill_ = 0;
    
    for (auto entry = mix_channels_.begin(); entry != mix_channels_.end(); entry++)
    {
        entry->mix_channel_index = 0;
    }
    return result;
}
