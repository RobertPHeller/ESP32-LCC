// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 17 12:37:37 2024
//  Last Modified : <240419.1653>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
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
/// @file Esp32SPI.hxx
/// @author Robert Heller
/// @date Wed Apr 17 12:37:37 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __ESP32SPI_HXX
#define __ESP32SPI_HXX

#include <unistd.h>
#include <driver/spi_master.h>
#include <hal/gpio_types.h>
#include "driver/sdmmc_types.h"
#include "driver/sdspi_host.h"
#include "esp_err.h"
#include <utils/Atomic.hxx>
#include <vector>
#include <string>

namespace openmrn_arduino
{


class Esp32SPI : private Atomic
{
public:
    class SpiDevice
    {
    public:
        void transfer(void * data, uint32_t size);
        uint8_t transfer(uint8_t data,bool keepalive=false);
        uint16_t transfer16(uint16_t data,bool keepalive=false);
        uint32_t transfer32(uint32_t data,bool keepalive=false);
        
        void transferBytes(const uint8_t * data, uint8_t * out, uint32_t size);
        void transferBits(uint32_t data, uint32_t * out, uint8_t bits);
        
        void write(uint8_t data,bool keepalive=false);
        void write16(uint16_t data,bool keepalive=false);
        void write32(uint32_t data,bool keepalive=false);
        void writeBytes(const uint8_t * data, uint32_t size);
        void writePixels(const void * data, uint32_t size);//ili9341 compatible
        void writePattern(const uint8_t * data, uint8_t size, uint32_t repeat);
        
        void Acquire();
        void Release();
    protected:
        friend class Esp32SPI;
        SpiDevice(gpio_num_t ss, Esp32SPI *parent);
        SpiDevice(gpio_num_t ss, Esp32SPI *parent, const char *mountPoint, bool format = true);
        ~SpiDevice();
    private:
        gpio_num_t ss_;
        Esp32SPI *parent_;
        spi_device_handle_t spi_;
        sdmmc_card_t *card_;
        bool isSD_;
        std::string mountPoint_;
        SpiDevice() {}
        void writePattern_(const uint8_t * data, uint8_t size, uint32_t repeat);
    };
    Esp32SPI(spi_host_device_t spi_bus=SPI2_HOST);
    void hw_initbus(int mosi, int miso, int sclk);
    SpiDevice *open(gpio_num_t ss);
    SpiDevice * mount_sd_card(const char *mountPoint, gpio_num_t cs, 
                              bool format = true);
    void unmount_sd_card(SpiDevice *dev);
    ~Esp32SPI();
protected:
    friend class SpiDevice;
    std::vector<SpiDevice *> open_devices_;
    spi_host_device_t spi_num_;
};

};

using openmrn_arduino::Esp32SPI;

#endif // __ESP32SPI_HXX

