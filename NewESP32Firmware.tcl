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
#  Created       : Sun Apr 5 14:33:40 2026
#  Last Modified : <260406.0918>
#
#  Description	
#
#  Notes
#
#  History
#	
#*****************************************************************************
#
#    Copyright (C) 2026  Robert Heller D/B/A Deepwoods Software
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


if {$argc < 1} {
    error "missing project name"
}

set projectname [lindex $argv 0]

file mkdir firmware/main
file mkdir firmware/components/Config/CDI
file mkdir firmware/components/Config/include
file mkdir firmware/doc
file mkdir firmware/doc/Images

file link -symbolic firmware/components/OpenMRN /home/heller/openmrn/etc/esp-idf 

set templatedir [file join [file dirname [info script]] firmware-template]
set fp [open {firmware/CMakeLists.txt} w]
set ifp [open [file join $templatedir CMakeLists-top.txt] r]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp
close $ifp
set fp [open {firmware/sdkconfig.defaults} w]
set ifp [open [file join $templatedir sdkconfig.defaults] r]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp
close $ifp
file copy [file join $templatedir partitions.csv] \
      [file join {firmware} "$projectname-partitions.csv"]
foreach sh [glob -nocomplain [file join $templatedir  {*.sh}]] {
    file copy $sh firmware
}
set fp [open {firmware/main/CMakeLists.txt} w]
set ifp [open [file join $templatedir CMakeLists-main.txt] r]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp
close $ifp 
set fp [open {firmware/main/CMakeLists.txt} w]
puts $fp [regsub -all {@PROJECT@} {} $projectname]
close $fp
file copy [file join $templatedir idf_component.yml] "firmware/main/idf_component.yml"
set ifp [open [file join $templatedir main.cpp] r]
set fp [open "firmware/main/$projectname.cpp" w]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp
close $ifp
set ifp [open [file join $templatedir FactoryResetHelper.hxx] r]
set fp [open "firmware/main/FactoryResetHelper.hxx" w]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname] 
close $fp
close $ifp
file copy [file join $templatedir hardware.hxx] firmware/main
set ifp [open [file join $templatedir cdi.hxx] r]
set fp [open {firmware/components/Config/include/cdi.hxx} w]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp
close $ifp
file copy [file join $templatedir CMakeLists-config.txt] \
      firmware/components/Config/CMakeLists.txt
file copy [file join $templatedir Kconfig.projbuild] \
      firmware/components/Config/Kconfig.projbuild
file copy [file join $templatedir Makefile-CDI] \
      firmware/components/Config/CDI/Makefile
set ifp [open [file join $templatedir CompileCdiMain.cxx] r]
set fp [open {firmware/components/Config/CDI/CompileCdiMain.cxx} w]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp 
close $ifp
file copy [file join $templatedir SNIPEDIT.sed] \
      firmware/components/Config/CDI/SNIPEDIT.sed
file copy [file join $templatedir Makefile-doc] \
      firmware/doc/Makefile
file copy [file join $templatedir Doxyfile.in] \
      firmware/doc/Doxyfile.in
set ifp [open [file join $templatedir Doxyfile.kit.in] r]
set fp [open {firmware/doc/Doxyfile.kit.in} w]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname]
close $fp
close $ifp
set ifp [open [file join $templatedir header.sed ] r]
set fp [open {firmware/doc/header.sed} w]
puts $fp [regsub -all {@PROJECT@} [read $ifp] $projectname] 
close $fp
close $ifp 
file copy [file join $templatedir kitbooklet.h] \
      firmware/doc/kitbooklet.h
exec >@stdout 2>@stderr git add firmware/CMakeLists.txt
exec >@stdout 2>@stderr git add firmware/sdkconfig.defaults
exec >@stdout 2>@stderr git add firmware/$projectname-partitions.csv
exec >@stdout 2>@stderr git add firmware/main/CMakeLists.txt
exec >@stdout 2>@stderr git add firmware/main/idf_component.yml
exec >@stdout 2>@stderr git add firmware/main/$projectname.cpp
exec >@stdout 2>@stderr git add firmware/main/hardware.hxx
exec >@stdout 2>@stderr git add firmware/components/Config/CMakeLists.txt
exec >@stdout 2>@stderr git add firmware/components/Config/Kconfig.projbuild
exec >@stdout 2>@stderr git add firmware/components/Config/include/cdi.hxx
exec >@stdout 2>@stderr git add firmware/components/Config/CDI/Makefile
exec >@stdout 2>@stderr git add firmware/components/Config/CDI/CompileCdiMain.cxx
exec >@stdout 2>@stderr git add firmware/components/Config/CDI/SNIPEDIT.sed
exec >@stdout 2>@stderr git add firmware/doc/Makefile
exec >@stdout 2>@stderr git add firmware/doc/Doxyfile.in
exec >@stdout 2>@stderr git add firmware/doc/Doxyfile.kit.in
exec >@stdout 2>@stderr git add firmware/doc/header.sed 
exec >@stdout 2>@stderr git add firmware/doc/kitbooklet.h 
