// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Mar 11 11:08:34 2023
//  Last Modified : <230311.1114>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
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

#ifndef __FACTORYRESETHELPER_HXX
#define __FACTORYRESETHELPER_HXX
#include "cdi.hxx"

#include <algorithm>
#include <stdint.h>
#include <executor/Notifiable.hxx>
#include <utils/ConfigUpdateListener.hxx>
#include <utils/format_utils.hxx>

namespace esp32quadneopixel{

// when the io board starts up the first time the config is blank and needs to
// be reset to factory settings.
class FactoryResetHelper : public DefaultConfigUpdateListener
{
public:
    FactoryResetHelper() : DefaultConfigUpdateListener()
    {
    }
    
    UpdateAction apply_configuration(int fd, bool initial_load,
                                     BarrierNotifiable *done) override;
    void factory_reset(int fd) override;
};

} // namespace esp32quadneopixel

#endif // __FACTORYRESETHELPER_HXX

