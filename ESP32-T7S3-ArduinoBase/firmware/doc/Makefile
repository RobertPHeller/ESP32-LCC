##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Thu Mar 23 13:21:11 2023
#  Last Modified : <230414.0816>
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
##############################################################################


all: html latex pdf

SOURCES = $(wildcard ../main/*.hxx) $(wildcard ../main/*.cpp) \
	  $(wildcard ../components/Config/include/*.hxx) \
	  $(wildcard ../../../CommonComponents/Azatrax/*.cpp) \
          $(wildcard ../../../CommonComponents/Azatrax/include/*.hxx) \
          $(wildcard ../../../CommonComponents/NVSManager/*.cpp) \
          $(wildcard ../../../CommonComponents/NVSManager/include/*.hxx) \
          $(wildcard ../../../CommonComponents/FS/*.cpp) \
          $(wildcard ../../../CommonComponents/FS/include/*.hxx) \
          $(wildcard ../../../CommonComponents/HealthMonitor/*.cpp) \
          $(wildcard ../../../CommonComponents/HealthMonitor/include/*.hxx) \
          $(wildcard ../../../CommonComponents/RebootHelpers/*.cpp) \
          $(wildcard ../../../CommonComponents/RebootHelpers/include/*.hxx)           $(wildcard ../../CommonComponents/Logic/include/*.hxx)

Doxyfile: Doxyfile.in ../../../.git/index ../sdkconfig
	sed -e "s/@PROJECTNAME@/$(PROJECTNAME)/g" \
	    -e "s/@PROJECTNUMBER@/$(PROJECTNUMBER)/g" \
	    >$@ <$<
	    

html latex: Doxyfile $(SOURCES)
	-rm -rf html latex pdf
	doxygen Doxyfile
	

pdf: latex
	make -C latex
	touch pdf

clean:
	rm -rf html latex pdf Doxyfile
