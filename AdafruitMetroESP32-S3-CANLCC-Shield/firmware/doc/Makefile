##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Tue Oct 20 15:31:53 2026
#  Last Modified : <261021.1546>
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
##############################################################################


all: html latex pdf

SOURCES = $(wildcard ../main/*.hxx) $(wildcard ../main/*.cpp) \
	  $(wildcard ../components/Config/include/*.hxx) \
          $(wildcard ../../../CommonComponents/Azatrax/include/*.hxx) \
          $(wildcard ../../../CommonComponents/WiFiManager/include/*.hxx) \
          $(wildcard ../../../CommonComponents/NVSManager/include/*.hxx) \
          $(wildcard ../../../CommonComponents/FS/include/*.hxx) \
          $(wildcard ../../../CommonComponents/HealthMonitor/include/*.hxx) \
          $(wildcard ../../../CommonComponents/RebootHelpers/include/*.hxx) 

Doxyfile: Doxyfile.in ../../../.git/index ../sdkconfig
	sed -e "s/@PROJECTNAME@/$(PROJECTNAME)/g" \
	    -e "s/@PROJECTNUMBER@/$(PROJECTNUMBER)/g" \
	    >$@ <$<
	    
header.tex: Doxyfile Makefile header.sed
	doxygen -w latex new_header.tex /dev/null /dev/null
	sed <new_header.tex >header.tex -f header.sed 
	-rm new_header.tex

html latex: Doxyfile $(SOURCES) Makefile $(wildcard Images/*) header.tex
	-rm -rf html latex pdf
	doxygen Doxyfile
	cp Images/*.png latex/

pdf: latex 
	make -C latex
	touch pdf

clean:
	rm -rf html latex pdf Doxyfile


