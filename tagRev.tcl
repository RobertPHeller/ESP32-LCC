#*****************************************************************************
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Thu Feb 2 15:04:56 2023
#  Last Modified : <230202.1554>
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


set rfp [open "components/Config/include/Revision.hxxout" r]
while {[gets $rfp line] >= 0} {
    #puts stderr "*** line is '$line'"
    if {[regexp {Revision::REVISION} "$line"] > 0} {break}
}
gets $rfp line
#puts stderr "*** line (after init loop) is '$line'"
set revs [list]
while {[gets $rfp line] >= 0} {
    #puts stderr "*** line (in second loop) is '$line'"
    if {[string trim $line] eq "nullptr"} {break}
    regexp {^[[:space:]]*"([^"]*)",$} $line => rev
    lappend revs $rev
}

#puts stderr "*** revs is $revs"
close $rfp
set printer [open "|lp -o media=X58mmY31.12Label -d receiptPrinter -- -" w]
foreach r $revs {
    puts $printer "$r"
}
close $printer

