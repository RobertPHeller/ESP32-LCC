// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Dec 17 14:34:03 2022
//  Last Modified : <250109.1714>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2022  Robert Heller D/B/A Deepwoods Software
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
/// @file BootPauseHelper.cpp
/// @author Robert Heller 
/// @date Sat Dec 17 14:34:03 2022
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";

#include <esp_err.h>
#include <esp_log.h>
#include <esp_ota_ops.h>
#include <esp_system.h>
#include <esp_task_wdt.h>
#ifdef CONFIG_IDF_TARGET_ESP32
#include <driver/uart.h>
#else
#include <driver/usb_serial_jtag.h>
#endif
#include "NvsManager.hxx"
#include "BootPauseHelper.hxx"
#include "utils/logging.h"


namespace nvsmanager
{
void BootPauseHelper::CheckPause()
{
#ifndef CONFIG_IDF_TARGET_ESP32
    usb_serial_jtag_driver_config_t jtagDef = USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT();
    esp_err_t res = usb_serial_jtag_driver_install(&jtagDef);
    if (res != ESP_OK) 
    {
        LOG_ERROR("[CheckPause] Failed to start usb serial jtag");
        return;
    }
#else
    bool need_driver_unload = !uart_is_driver_installed(UART_NUM_0);
    LOG(VERBOSE,"[CheckPause] need_driver_unload = %d",need_driver_unload);
    if (need_driver_unload)
    {
        esp_err_t res = uart_driver_install(UART_NUM_0,RXBufferLength,
                                            0,0,NULL,0);
        if (res != ESP_OK)
        {
            LOG_ERROR("[CheckPause] Failed to start UART");
            return;
        }
    }
#endif
    size_t bytesavailable;
    for (int i=0;i<PauseLoopCount;i++)
    {
#ifndef CONFIG_IDF_TARGET_ESP32
        unsigned char temp[2];
        bytesavailable = usb_serial_jtag_read_bytes(temp,sizeof(temp),10);
#else
        esp_err_t res = uart_get_buffered_data_len(UART_NUM_0,&bytesavailable);
        if (res != ESP_OK)
        {
            LOG_ERROR("[CheckPause] Failed to get buffered data len");
            return;
        }
#endif
        LOG(VERBOSE,"[CheckPause] bytesavailable = %d",bytesavailable);
        if (bytesavailable > 0)
        {
            break;
        }
        esp_rom_delay_us(PauseLoopDelay_us);
    }
    if (bytesavailable > 0)
    {
        PauseConsole();
        NvsManager::instance()->CheckPersist();
    }
#ifndef CONFIG_IDF_TARGET_ESP32
    res = usb_serial_jtag_driver_uninstall();
    if (res != ESP_OK)
    {
        LOG_ERROR("[CheckPause] Failed to delete usb serial jtag");
        return;
    }
    
#else    
    if (need_driver_unload)
    {
        esp_err_t res = uart_driver_delete(UART_NUM_0);
        if (res != ESP_OK)
        {
            LOG_ERROR("[CheckPause] Failed to delete uart");
            return;
        }
    }
#endif
}

static void writeSerial(const char *buffer,size_t length)
{
#ifndef CONFIG_IDF_TARGET_ESP32
    usb_serial_jtag_write_bytes(buffer,length,100);
#else
    uart_write_bytes(UART_NUM_0,buffer,length);
#endif
}

void BootPauseHelper::PauseConsole()
{
    char receivebuffer[RXBufferLength];
    char transmitBuffer[TXBufferLength];
    writeSerial("Ready.\r\n",8);
    
    while (true)
    {
        writeSerial("\r\n>>>",5);
        size_t len = ReadLine(UART_NUM_0,receivebuffer,sizeof(receivebuffer));
        if (len == 0)
        {
            continue;
        }
        switch (toupper(receivebuffer[0]))
        {
        case SETNODE:
            {
                uint64_t nid = ParseNode(&receivebuffer[1],len-1);
                writeSerial("\r\n",2);
                NvsManager::instance()->node_id(nid);
                int l = snprintf(transmitBuffer,sizeof(transmitBuffer),"\r\nSet Node ID: %0llx\r\n",nid);
                writeSerial(transmitBuffer,l);
                break;
            }
        case BOOTLOADER:
            NvsManager::instance()->force_bootloader();
            break;
        case EVENTRESET:
            NvsManager::instance()->force_reset_events();
            break;
        case FACTORYRESET:
            NvsManager::instance()->force_factory_reset();
            break;
        case TESTSIGLAMPS:
            NvsManager::instance()->force_test_signal_lamps();
            break;
#ifdef CONFIG_ESP32_WIFI_ENABLED
        case SETSSID:
            NvsManager::instance()->station_ssid(GetString(&receivebuffer[1],len-1));
            break;
        case SETPASS:
            NvsManager::instance()->station_pass(GetString(&receivebuffer[1],len-1));
            break;
        case SETHOST:
            NvsManager::instance()->hostname_prefix(GetString(&receivebuffer[1],len-1));
            break;
        case SETWIFI:
            NvsManager::instance()->wifi_mode(GetMode(&receivebuffer[1],len-1));
            break;
#endif
        case RESUME:
            return;
        default:
            {
                int l = snprintf(transmitBuffer,sizeof(transmitBuffer),"Err: %c\r\n",receivebuffer[0]);
                writeSerial(transmitBuffer,l);
                break;
            }
        }
    }
}

uint64_t BootPauseHelper::ParseNode(char * buffer, size_t bufferlen)
{
    uint64_t result = 0;
    char *p = NULL;
    size_t l = 0;
    for (p = buffer,l = bufferlen; l > 0 && *p != '\0';p++,l--)
    {
        if (isxdigit(*p))
        {
            if (isdigit(*p))
            {
                result = (result << 4) + (*p - '0');
            }
            else if (islower(*p))
            {
                result = (result << 4) + ((*p - 'a')+10);
            }
            else
            {
                result = (result << 4) + ((*p - 'A')+10);
            }
        }
    }
    return result;
}

size_t BootPauseHelper::ReadLine(uart_port_t uart_num,char *buffer,
                                 size_t bufferlen)
{
    char *p = buffer;
    size_t remainder = bufferlen;
    size_t numread   = 0;
    const char space[] = "\b \b";
    const char eol[] = "\r\n";
    
    while (remainder > 0)
    {
#ifndef CONFIG_IDF_TARGET_ESP32
        int r = usb_serial_jtag_read_bytes(p,1,100);
#else
        int r = uart_read_bytes(uart_num,p,1,100);
#endif
        if (r > 0)
        {
            if (*p == EOL)
            {
                writeSerial(eol,2);
                numread++;
                *p = '\0';
                break;
            }
            else if (*p == '\b' || *p == 0x7f)
            {
                if (p > buffer && remainder < bufferlen)
                {
                    p--; remainder++; numread--;
                    writeSerial(space,3);
                }
            }
            else
            {
                writeSerial(p,r);
                numread++;
                p++;
                remainder--;
            }
        }
    }
    return numread;
}

wifi_mode_t BootPauseHelper::GetMode(char *buffer,size_t bufferlen)
{
    char *p = buffer;
    char *end = buffer+bufferlen;
    while (*p <= ' ' && p < end) p++;
    if (p >= end) return WIFI_MODE_STA;
    if (strncasecmp("ON",p,2) == 0) {return WIFI_MODE_STA;}
    else if (strncasecmp("OFF",p,3) == 0) {return WIFI_MODE_NULL;}
    else if (strncasecmp("YES",p,3) == 0) {return WIFI_MODE_STA;}
    else if (strncasecmp("NO",p,2) == 0) {return WIFI_MODE_NULL;}
    else {return WIFI_MODE_STA;}
}

const char *BootPauseHelper::GetString(char *buffer,size_t bufferlen)
{
    char *p = buffer;
    char *end = buffer+bufferlen;
    while (*p <= ' ' && p < end) p++;
    if (p >= end) return "";
    while (*(end-1) <= ' ' && end > p) end--;
    *end = '\0';
    return p;
}

DEFINE_SINGLETON_INSTANCE(BootPauseHelper);

}
