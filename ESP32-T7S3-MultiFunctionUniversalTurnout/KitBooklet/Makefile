##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Sat Mar 4 08:32:49 2023
#  Last Modified : <230711.0924>
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


LATEX=/usr/bin/pdflatex
BIBTEX=/usr/bin/bibtex
MAKEINDEX=/usr/bin/makeindex
GS=/usr/bin/gs

all: ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf

insert: ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet_4up.pdf

TEXS=ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.tex Assembly.tex \
	Downloadables.tex GeneralWiring.tex ApplNote_Siding.tex \
	ApplNote_YardThroat.tex ApplNote_Crossing.tex ApplNote_ABS.tex

FIGURES=ESP32-T7S3-MultiFunctionUniversalTurnout.png TC-DaughterBoard.png \
	SC-DaughterBoard.png TS-DaughterBoard.png SM-DaughterBoard.png \
	NylonStandoffInstall.png ESP32-T7S3-MultiFunctionUniversalTurnout.png \
	TerminationJumpers.png SM-DaughterBoard-Annotated.png \
	SC-DaughterBoard-Annotated.png TC-DaughterBoard-Annotated.png \
	TS-DaughterBoard-Annotated.png SM-DaughterBoard-TortoiseWiring.png \
	ExampleSidingCP1-Wiring.png  \
	ExampleSidingCP1_EventFlow.pdf \
	YardThroat_TrackSelector.png YardThroat_YardSelect.pdf \
	CrossingInterchange.png Crossing_CPNorth.pdf Crossing_CPEast.pdf \
	Crossing_CPCrossing.pdf ABSTrack.png ABSTrack_EventID.pdf
	
%.pdf:%.gv
	dot -O -Tpdf $<
	mv $<.pdf $@
	
YardThroat_YardSelect.pdf: YardThroat_YardSelect.gv

ExampleSidingCP1_EventFlow.pdf: ExampleSidingCP1_EventFlow.gv

Crossing_CPNorth.pdf: Crossing_CPNorth.gv

Crossing_CPEast.pdf: Crossing_CPEast.gv

Crossing_CPCrossing.pdf: Crossing_CPCrossing.gv

ABSTrack_EventID.pdf: ABSTrack_EventID.gv


ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf : $(TEXS) $(FIGURES)
	$(LATEX) ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet
	-$(BIBTEX) ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet
	$(LATEX) ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet
	-$(MAKEINDEX) ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet
	$(LATEX) ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet
	$(LATEX) ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet
	#mv ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf \
	#	ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet-orig.pdf
	#$(GS) -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -dPDFSETTINGS=/prepress \
	#	-dEmbedAllFonts=true \
	#	-sOutputFile=ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf \
	#	-f ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet-orig.pdf
	#-rm ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet-orig.pdf

ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet-book.pdf :\
		ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf
	pdfbook2 ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf



clean:
	rm -f ESP32-T7S3-MultiFunctionUniversalTurnoutBooklet.pdf *.aux *.log *.inx \
		*.bbl *.blg *.idx *.lof *.lot *.toc *.ilg *.ind *.out *~ *.bak
