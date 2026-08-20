// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Aug 19 18:59:00 2026
//  Last Modified : <260819.1902>
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

#ifndef __SOUNDCONFIGUPDATER_HXX
#define __SOUNDCONFIGUPDATER_HXX

#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "SoundConfig.hxx"

class SoundConfigUpdater : public DefaultConfigUpdateListener
{
public:
    SoundConfigUpdater(SoundConfig cfg) : cfg_(cfg)
    {
    }
    /** Apply a the configuration settings.
     *      * @param fd Config file descriptor.
     *      * @param initial_load Initial load flag.
     *      * @param done Notifiable.
     *      */
    virtual UpdateAction apply_configuration(int fd, bool initial_load,
                                             BarrierNotifiable *done);
    /** Factory reset.
     *      * @param fd Config file descriptor. 
     *      */
    virtual void factory_reset(int fd);
private:
    SoundConfig cfg_;
};

#endif // __SOUNDCONFIGUPDATER_HXX

