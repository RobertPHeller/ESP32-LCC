#*****************************************************************************
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Fri Mar 3 16:40:36 2023
#  Last Modified : <230303.1702>
#
#  Description	
#
#  Notes
#
#  History
#	
#*****************************************************************************
#
#    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
#			51 Locke Hill Road
#			Wendell, MA 01379-9728
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# 
#
#*****************************************************************************


package require ReceiptPrinter
package require snit

snit::type PrintSticker {
    pragma -hastypeinfo    no
    pragma -hastypedestroy no
    pragma -hasinstances   no
    
    typevariable printer {}
    typevariable _builddate
    typevariable _gitcommit
    typevariable _openmrngitcommit
    typevariable _buildflags
    typevariable _printer
    typeconstructor {
        set fp [open Sticker.out r]
        set _builddate [gets $fp]
        set _gitcommit [gets $fp]
        set _openmrngitcommit [gets $fp]
        set _buildflags [gets $fp]
        close $fp
        set _printer [POSReceiptPrinter create %AUTO% /dev/usb/lp2]
        
        $_printer destroy
    }
}


