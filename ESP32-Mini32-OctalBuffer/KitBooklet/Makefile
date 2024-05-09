##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Thu May 9 09:46:15 2024
#  Last Modified : <240509.1001>
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
#    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
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


all: KitBooklet.pdf

SOURCES = kitbooklet.h \
	$(wildcard ../../ESP32-OctalBufferOpenMRNIDF/components/Config/include/*.hxx)
	

ifndef PROJECTNAME
PROJECTNAME=ESP32 Mini32 OctalBuffer
endif
ifndef PROJECTNUMBER
PROJECTNUMBER=$(shell git rev-parse --short HEAD)
$(shell git diff --quiet)
ifeq ($.SHELLSTATUS,1)
$PROJECTNUMBER=${PROJECTNUMBER}-dirty
endif
endif

Doxyfile: Doxyfile.in ../../.git/index
	sed -e "s/@PROJECTNAME@/$(PROJECTNAME)/g" \
	    -e "s/@PROJECTNUMBER@/$(PROJECTNUMBER)/g" \
	    >$@ <$<

latex/refman.tex: Makefile Doxyfile $(SOURCES)
	-rm -rf latex
	doxygen Doxyfile
	
KitBooklet.pdf: latex/refman.tex
	make -C latex
	pdfbook2 latex/refman.pdf
	mv latex/refman-book.pdf ./KitBooklet.pdf
	
KitBooklet_even.pdf: KitBooklet.pdf
	pdftk KitBooklet.pdf cat even output KitBooklet_even.pdf
	
KitBooklet_odd.pdf: KitBooklet.pdf
	pdftk KitBooklet.pdf cat odd output KitBooklet_odd.pdf


clean:
	-rm -rf latex Doxyfile

distclean: clean
	-rm UserManual.pdf KitBooklet.pdf

