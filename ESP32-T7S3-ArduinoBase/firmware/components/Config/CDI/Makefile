##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Wed Sep 21 11:39:10 2022
#  Last Modified : <230413.1335>
#
#  Description	
#
#  Notes
#
#  History
#	
#  $Log$
#
##############################################################################
#
#    Copyright (C) 2022  Robert Heller D/B/A Deepwoods Software
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
##############################################################################

PROJECTPATH=`(cd ../../..;pwd)`

all: ../include/cdidata.hxx ../../../Sticker.out

../include/cdidata.hxx : compile_cdi SNIPEDIT.sed
	./compile_cdi |sed -f SNIPEDIT.sed >../include/cdidata.hxx
        

EXTRAFLAGS=

EXTRAINCLUDES=`../../../../../buildscripts/getincludes.tcl ../../../build/build.ninja`

compile_cdi: ../include/cdi.hxx CompileCdiMain.cxx \
	../../../sdkconfig ../include/Revision.hxxout
	g++ -o $@ $(EXTRAFLAGS) -I. -I../../../build/config $(EXTRAINCLUDES) \
		$(CDIEXTRA)  --std=c++11 -MMD \
		-MF $@.d $(CXXFLAGSEXTRA) CompileCdiMain.cxx
	


../include/Revision.hxxout : ../../../../../.git/index \
	../../../sdkconfig
	../../../../../buildscripts/revision.py -t \
		-i "$(PROJECTPATH)" -o ../include/Revision
	

../../../Sticker.out: ../../../../../.git/index ../include/Revision.hxxout \
	../../../sdkconfig
	../../../../../buildscripts/sticker.py -t \
		-i "$(PROJECTPATH)" \
		-b 'DEVKIT_BREADBOARD=$(CONFIG_DEVKIT_BREADBOARD) T7S3=$(CONFIG_T7S3)' \
		-o ../../../Sticker.out
FORCE:

