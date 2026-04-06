// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 17 12:37:51 2024
//  Last Modified : <240419.1719>
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
/// @file Esp32SPI.cpp
/// @author Robert Heller
/// @date Wed Apr 17 12:37:51 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";


#include <unistd.h>
#include <driver/spi_master.h>
#include "esp_err.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_types.h"
#include "driver/sdspi_host.h"
#include <hal/gpio_types.h>
#include <utils/Atomic.hxx>
#include <vector>
#include <string>
#include <cstring>

#include <algorithm>

#include "Esp32SPI.hxx"

namespace openmrn_arduino
{
Esp32SPI::Esp32SPI(spi_host_device_t spi_bus)
      : spi_num_(spi_bus)
{
}

Esp32SPI::~Esp32SPI()
{
    for (auto dev=open_devices_.begin(); dev != open_devices_.end(); dev++)
    {
        delete *dev;
        open_devices_.erase(dev);
    }
    spi_bus_free(spi_num_);
}
void Esp32SPI::hw_initbus(int mosi, int miso, int sclk)
{
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .mosi_io_num = mosi,
        .miso_io_num = miso,
        .sclk_io_num = sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .data4_io_num = 0,
        .data5_io_num = 0,
        .data6_io_num = 0,
        .data7_io_num = 0,
        .max_transfer_sz = 10248,
        .flags = 0,
        .intr_flags = 0
    };
    
    ret = spi_bus_initialize(spi_num_, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
}
Esp32SPI::SpiDevice *Esp32SPI::open(gpio_num_t ss)
{
    return new SpiDevice(ss,this);
}
Esp32SPI::SpiDevice * Esp32SPI::mount_sd_card(const char *mountPoint, gpio_num_t cs, bool format)
{
    return new SpiDevice(cs,this,mountPoint,format);
}
void Esp32SPI::unmount_sd_card(Esp32SPI::SpiDevice *dev)
{
    delete dev;
}

void Esp32SPI::SpiDevice::transfer(void * data, uint32_t size)
{
    transferBytes((const uint8_t *)data, (uint8_t *)data, size);
}

void Esp32SPI::SpiDevice::Acquire()
{
    spi_device_acquire_bus(spi_,portMAX_DELAY);
}

void Esp32SPI::SpiDevice::Release()
{
    spi_device_release_bus(spi_);
}

uint8_t Esp32SPI::SpiDevice::transfer(uint8_t data,bool keepalive)
{
    AtomicHolder h(parent_);
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;
    t.flags = SPI_TRANS_USE_RXDATA;
    if (keepalive) t.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
    //spi_device_acquire_bus(spi_,portMAX_DELAY);
    ret = spi_device_polling_transmit(spi_,&t);
    ESP_ERROR_CHECK(ret);
    //spi_device_release_bus(spi_);
    return *(uint8_t*)t.rx_data;
}
uint16_t Esp32SPI::SpiDevice::transfer16(uint16_t data,bool keepalive)
{
    AtomicHolder h(parent_);
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8*2;
    t.tx_buffer = &data;
    t.flags = SPI_TRANS_USE_RXDATA;
    if (keepalive) t.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
    //spi_device_acquire_bus(spi_,portMAX_DELAY);
    ret = spi_device_polling_transmit(spi_,&t);
    ESP_ERROR_CHECK(ret);
    //spi_device_release_bus(spi_);
    return *(uint16_t*)t.rx_data;
}
uint32_t Esp32SPI::SpiDevice::transfer32(uint32_t data,bool keepalive)
{
    AtomicHolder h(parent_);
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8*4;
    t.tx_buffer = &data;
    t.flags = SPI_TRANS_USE_RXDATA;
    if (keepalive) t.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
    //spi_device_acquire_bus(spi_,portMAX_DELAY);
    ret = spi_device_polling_transmit(spi_,&t);
    ESP_ERROR_CHECK(ret);
    //spi_device_release_bus(spi_);
    return *(uint32_t*)t.rx_data;
}
void Esp32SPI::SpiDevice::transferBytes(const uint8_t * data, uint8_t * out, uint32_t size)
{
    AtomicHolder h(parent_);
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8*size;
    t.tx_buffer = data;
    t.rx_buffer = out;
    //spi_device_acquire_bus(spi_,portMAX_DELAY);
    ret = spi_device_polling_transmit(spi_,&t);
    ESP_ERROR_CHECK(ret);
    //spi_device_release_bus(spi_);
}
void Esp32SPI::SpiDevice::transferBits(uint32_t data, uint32_t * out, uint8_t bits)
{
    AtomicHolder h(parent_);
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = bits;
    t.tx_buffer = &data;
    t.rx_buffer = out;
    //spi_device_acquire_bus(spi_,portMAX_DELAY);
    ret = spi_device_polling_transmit(spi_,&t);
    ESP_ERROR_CHECK(ret);
    //spi_device_release_bus(spi_);
}
        
void Esp32SPI::SpiDevice::write(uint8_t data,bool keepalive)
{
    transfer(data,keepalive);
}
void Esp32SPI::SpiDevice::write16(uint16_t data,bool keepalive)
{
    transfer16(data,keepalive);
}
void Esp32SPI::SpiDevice::write32(uint32_t data,bool keepalive)
{
    transfer32(data,keepalive);
}
void Esp32SPI::SpiDevice::writeBytes(const uint8_t * data, uint32_t size)
{
    transferBytes((const uint8_t *)data, NULL, size);
}

#define MSB_32_SET(var, val) { uint8_t * d = (uint8_t *)&(val); (var) = d[3] | (d[2] << 8) | (d[1] << 16) | (d[0] << 24); }
#define MSB_24_SET(var, val) { uint8_t * d = (uint8_t *)&(val); (var) = d[2] | (d[1] << 8) | (d[0] << 16); }
#define MSB_16_SET(var, val) { (var) = (((val) & 0xFF00) >> 8) | (((val) & 0xFF) << 8); }
#define MSB_PIX_SET(var, val) { uint8_t * d = (uint8_t *)&(val); (var) = d[1] | (d[0] << 8) | (d[3] << 16) | (d[2] << 24); }

void Esp32SPI::SpiDevice::writePixels(const void * data_in, uint32_t size)
{
    uint32_t buffer[16];
    size_t longs = size >> 2;
    if(size & 3){
        longs++;
    }
    bool msb = true;
    uint32_t * data = (uint32_t*)data_in;
    size_t c_len = 0, c_longs = 0, l_bytes = 0;
    while(size)
    {
        c_len = (size>64)?64:size;
        c_longs = (longs > 16)?16:longs;
        l_bytes = (c_len & 3);
        for (size_t i=0; i<c_longs; i++) {
            if(msb)
            {
                if(l_bytes && i == (c_longs - 1))
                {
                    if(l_bytes == 2)
                    {
                        MSB_16_SET(buffer[i], data[i]);
                    }
                    else
                    {
                        buffer[i] = data[i] & 0xFF;
                    }
                }
                else
                {
                    MSB_PIX_SET(buffer[i], data[i]);
                }
            }
            else
            {
                buffer[i] = data[i];
            }
        }
        writeBytes((const uint8_t *)buffer,c_longs<<2);
        data += c_longs;
        longs -= c_longs;
        size -= c_len;
    }
}
void Esp32SPI::SpiDevice::writePattern(const uint8_t * data, uint8_t size, uint32_t repeat)
{
    if(size > 64) {
        return;    //max Hardware FIFO
    }

    uint32_t byte = (size * repeat);
    uint8_t r = (64 / size);
    const uint8_t max_bytes_FIFO = r * size;    // Max number of whole patterns (in bytes) that can fit into the hardware FIFO

    while(byte) {
        if(byte > max_bytes_FIFO) {
            writePattern_(data, size, r);
            byte -= max_bytes_FIFO;
        } else {
            writePattern_(data, size, (byte / size));
            byte = 0;
        }
    }    
}
void Esp32SPI::SpiDevice::writePattern_(const uint8_t * data, uint8_t size, uint32_t repeat)
{
    uint8_t bytes = (size * repeat);
    uint8_t buffer[64];
    uint8_t * bufferPtr = &buffer[0];
    const uint8_t * dataPtr;
    uint8_t dataSize = bytes;
    for(uint8_t i = 0; i < repeat; i++) {
        dataSize = size;
        dataPtr = data;
        while(dataSize--) {
            *bufferPtr = *dataPtr;
            dataPtr++;
            bufferPtr++;
        }
    }

    writeBytes(&buffer[0], bytes);
}

Esp32SPI::SpiDevice::SpiDevice(gpio_num_t ss, Esp32SPI *parent)
      : ss_(ss), parent_(parent), isSD_(false)
{
    esp_err_t ret;
    spi_device_interface_config_t devdfg = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode=0,
        .duty_cycle_pos =0,
        .cs_ena_pretrans=0,
        .cs_ena_posttrans=0,
        .clock_speed_hz = 10*1000*1000,
        .input_delay_ns=0,
        .spics_io_num=ss_,
        .flags =0,
        .queue_size=7,
        .pre_cb=NULL,
        .post_cb=NULL
    };
    ret=spi_bus_add_device(parent_->spi_num_, &devdfg, &spi_);
    ESP_ERROR_CHECK(ret);
    parent_->open_devices_.push_back(this);
}
Esp32SPI::SpiDevice::SpiDevice(gpio_num_t ss, Esp32SPI *parent, 
                               const char *mountPoint, bool format)
      : ss_(ss), parent_(parent), isSD_(true), mountPoint_(mountPoint)
{
    esp_err_t ret;
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = parent_->spi_num_;
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = format,
        .max_files = 5,
        .allocation_unit_size = 16*1024,
        .disk_status_check_enable = true
    };
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = ss_;
    slot_config.host_id = parent_->spi_num_;
    ret = esp_vfs_fat_sdspi_mount(mountPoint_.c_str(), &host, &slot_config, 
                                  &mount_config, &card_);
    ESP_ERROR_CHECK(ret);
    parent_->open_devices_.push_back(this);
}

Esp32SPI::SpiDevice::~SpiDevice()
{
    if (isSD_)
    {
        esp_vfs_fat_sdcard_unmount(mountPoint_.c_str(), card_);
    }
    else
    {
        esp_err_t ret;
        ret = spi_bus_remove_device(spi_);
        ESP_ERROR_CHECK(ret);
    }
    auto mine = std::find(parent_->open_devices_.begin(),
                          parent_->open_devices_.end(),this);
    if (mine != parent_->open_devices_.end())
    {
        parent_->open_devices_.erase(mine);
    }
}

};
