// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon May 3 13:56:29 2021
//  Last Modified : <210503.1427>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2021  Robert Heller D/B/A Deepwoods Software
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

#include "EStopHandler.hxx"

#include <AllTrainNodes.hxx>

namespace BeagleCS
{

void EStopHandler::set_state(bool new_value)
{
  if (new_value)
  {
    LOG(INFO, "[eStop] Received eStop request, sending eStop to all trains.");
    // TODO: add helper method on AllTrainNodes for this.
    auto  trains = Singleton<commandstation::AllTrainNodes>::instance();
    for (size_t id = 0; id < trains->size(); id++)
    {
      auto node = trains->get_train_node_id(id);
      if (node)
      {
        trains->get_train_impl(node)->set_emergencystop();
      }
    }
    {
      AtomicHolder l(this);
      remaining_ = 200;
      packet_processor_add_refresh_source(this
                                        , dcc::UpdateLoopBase::ESTOP_PRIORITY);
    }
  }
  else
  {
    AtomicHolder l(this);
    if (remaining_)
    {
      LOG(INFO, "[eStop] Received eStop clear request.");
      remaining_ = 0;
      packet_processor_remove_refresh_source(this);
    }
  }
}

void EStopHandler::get_next_packet(unsigned code, dcc::Packet* packet)
{
  packet->set_dcc_speed14(dcc::DccShortAddress(0), true, false
                        , dcc::Packet::EMERGENCY_STOP);
  {
    AtomicHolder l(this);
    remaining_--;
    if (remaining_ <= 0)
    {
      packet_processor_remove_refresh_source(this);
    }
  }
}


}
