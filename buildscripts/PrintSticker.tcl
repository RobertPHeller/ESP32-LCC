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
#  Last Modified : <230309.1209>
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
        set _printer [POSReceiptPrinter create %AUTO% /dev/LABELS]
        $_printer selectCenterJustification
        $_printer _doubleStrikeOn
        $_printer textLine $_builddate
        $_printer _doubleStrikeOff
        $_printer selectLeftJustification
        $_printer selectFontB
        if {[regexp {^b'([[:xdigit:]]+)':(.*)$} $_gitcommit => commit remainder] > 0} {
            set remainder [regsub {:-d} $remainder {}]
            set _gitcommit "$commit:$remainder"
        }
        $_printer textLine $_gitcommit
        if {[regexp {^([[:xdigit:]]+):(.*)$} $_openmrngitcommit => commit what] > 0} {
            set _openmrngitcommit "[string range $commit 0 6]:$what"
        }
        $_printer textLine $_openmrngitcommit
        $_printer selectFontA
        set _flags [list]
        foreach f $_buildflags {
            lassign [split $f {=}] flag value
            if {$value eq {""}} {continue}
            lappend _flags $flag
        }
        $_printer selectCenterJustification
        $_printer textLine "Flags: $_flags"
        $_printer destroy
    }
}


