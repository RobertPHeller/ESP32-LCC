// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Aug 17 18:27:33 2026
//  Last Modified : <260817.1847>
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

#include "driver/i2s_pdm.h"
#include "driver/gpio.h"
#include "esp_check.h"
#include <hal/gpio_types.h>
#include <utils/Atomic.hxx>
#include <unistd.h>
#include <vector>
#include "Esp32PDMTXI2S.hxx"

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

namespace openmrn_esp32
{
Esp32PDMTXI2S::Esp32PDMTXI2S(const char * const path)
      : path_(path)
{
}

Esp32PDMTXI2S::~Esp32PDMTXI2S()
{
    for (size_t idx = 0; idx < SOC_I2S_NUM; idx++)
    {
        if (i2sInitialized_[idx])
        {
            // delete I2S driver (?)
        }
    }
    if (vfsInitialized_)
    {
        ESP_ERROR_CHECK(esp_vfs_unregister(path_));
    }
}

void Esp32PDMTXI2S::hw_init(const gpio_num_t bclk, const gpio_num_t dout,
                            uint32_t sample_rate_hz, i2s_port_t port)
{
}

ssize_t Esp32PDMTXI2S::write(int fd, const void *buf, size_t size)
{
    return 0;
}

int Esp32PDMTXI2S::open(const char *path, int flags, int mode)
{
    return 0;
}

int close(int fd)
{
    return 0;
}

int Esp32PDMTXI2S::ioctl(int fd, int cmd, va_list args)
{
    return 0;
}


}
