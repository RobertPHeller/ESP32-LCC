#!/usr/bin/tclsh
#*****************************************************************************
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Thu Feb 23 10:58:07 2023
#  Last Modified : <230223.1121>
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

set njfp [open [lindex $argv 0] r]

set builddir [file normalize [file dirname [lindex $argv 0]]]


while {[gets $njfp line] >= 0} {
    #puts stderr "*** line (L1) is '$line'"
    if {[regexp {^build cmake_object_order_depends_target_[^.]*\.elf:} $line] > 0} {break}
}

set allincludes {}
while {[gets $njfp line] >= 0} {
    #puts stderr "*** line (L2) is '$line'"
    if {[regexp {^[[:space:]]*INCLUDES[[:space:]]*=[[:space:]]*(.*)$} $line => allincludes] > 0} {break}
}
close $njfp

#puts stderr "*** allincludes is '$allincludes'"

if {$allincludes eq {}} {puts "";exit}

foreach inc [split $allincludes { }] {
    #puts stderr "*** inc = '$inc'"
    if {[regexp {^-I(\.\./.*)$} $inc => relativeinc] > 0} {
        set inc "-I[file normalize [file join $builddir $relativeinc]]"
    }
    if {[regexp {esp-idf-v} $inc] > 0} {continue}
    if {$inc eq {-Iconfig}} {continue}
    lappend includes $inc
}

puts $includes
exit
