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
#  Last Modified : <240508.1500>
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

all: html latex UserManual.pdf KitBooklet.pdf

SOURCES = $(wildcard ../main/*.hxx) kitbooklet.h Revision.h \
	  $(wildcard ../main/*.cpp) \
	  $(wildcard ../components/Config/include/*.hxx) \
	  $(wildcard ../components/Esp32SPI/include/*.hxx) \
	  $(wildcard ../components/GFX/include/*.hxx) \
	  $(wildcard ../components/ST77XX/*.hxx) \
          $(wildcard ../../../CommonComponents/NVSManager/*.cpp) \
          $(wildcard ../../../CommonComponents/NVSManager/include/*.hxx) \
          $(wildcard ../../../CommonComponents/FS/*.cpp) \
          $(wildcard ../../../CommonComponents/FS/include/*.hxx) \
          $(wildcard ../../../CommonComponents/HealthMonitor/*.cpp) \
          $(wildcard ../../../CommonComponents/HealthMonitor/include/*.hxx) \
          $(wildcard ../../../CommonComponents/RebootHelpers/*.cpp) \
          $(wildcard ../../../CommonComponents/RebootHelpers/include/*.hxx) \

ifndef PROJECTNAME
PROJECTNAME=Esp32TextDisplay
endif
ifndef PROJECTNUMBER
PROJECTNUMBER=$(shell git rev-parse --short HEAD)
$(shell git diff --quiet)
ifeq ($.SHELLSTATUS,1)
$PROJECTNUMBER=${PROJECTNUMBER}-dirty
endif
endif

Doxyfile: Doxyfile.in ../../../.git/index ../sdkconfig
	sed -e "s/@PROJECTNAME@/$(PROJECTNAME)/g" \
	    -e "s/@PROJECTNUMBER@/$(PROJECTNUMBER)/g" \
	    >$@ <$<
	    
Doxyfile.kit: Doxyfile.kit.in ../../../.git/index ../sdkconfig
	sed -e "s/@PROJECTNAME@/$(PROJECTNAME)/g" \
	    -e "s/@PROJECTNUMBER@/$(PROJECTNUMBER)/g" \
	    >$@ <$<
	  
Revision.h: ../components/Config/include/Revision.hxxout
	echo '/** @page Revision Build Revisions' > $@
	grep '^[[:space:]]*"[^"]*",$$' $< |sed 's/^[[:space:]]*"/ * - /g'|sed 's/",$$//g' >> $@
	echo '*/' >> $@


html/index.html latex/refman.tex: Makefile Doxyfile $(SOURCES)
	-rm -rf html latex 
	doxygen Doxyfile
	

UserManual.pdf: latex/refman.tex
	make -C latex
	mv latex/refman.pdf ./UserManual.pdf
	

latex2/refman.tex: Makefile Doxyfile.kit $(SOURCES)
	-rm -rf latex2
	doxygen Doxyfile.kit

KitBooklet.pdf: latex2/refman.tex
	make -C latex2
	pdfbook2 latex2/refman.pdf
	mv latex2/refman-book.pdf ./KitBooklet.pdf

KitBooklet_even.pdf: KitBooklet.pdf
	pdftk KitBooklet.pdf cat even output KitBooklet_even.pdf
	
KitBooklet_odd.pdf: KitBooklet.pdf
	pdftk KitBooklet.pdf cat odd output KitBooklet_odd.pdf


clean:
	-rm -rf html latex latex2 Doxyfile Doxyfile.kit

distclean: clean
	-rm UserManual.pdf KitBooklet.pdf
