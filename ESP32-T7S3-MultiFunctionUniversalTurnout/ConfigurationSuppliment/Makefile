##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : 2026-03-22 21:22:33
#  Last Modified : <260323.0726>
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

all: ConfigurationSuppliment-book.pdf ConfigurationSuppliment.pdf

SRCS = ../../CommonComponents/NVSManager/include/NodeIdConfigurationGroup.hxx \
	../../CommonComponents/NVSManager/include/WiFiConfigurationGroup.hxx \
	../../CommonComponents/GeneralIO/include/ButtonConfig.hxx \
	../../CommonComponents/GeneralIO/include/LEDConfig.hxx \
	../../CommonComponents/GeneralIO/include/OccupancyDetectorConfig.hxx \
	../../CommonComponents/GeneralIO/include/PointsConfig.hxx \
	../../CommonComponents/GeneralIO/include/ServoTurnoutConfig.hxx \
	../../CommonComponents/GeneralIO/include/TurnoutConfig.hxx \
	../../CommonComponents/Logic/include/LogicConfig.hxx \
	../../CommonComponents/Logic/include/TrackCircuitConfig.hxx \
	../../CommonComponents/Signals/include/LampConfig.hxx \
	../../CommonComponents/Signals/include/MastConfig.hxx \
	../../CommonComponents/Signals/include/RuleConfig.hxx \
	Esp32WiFiConfiguration.dox main.dox

       

ConfigurationSuppliment.pdf: latex/refman.pdf
	mv latex/refman.pdf ConfigurationSuppliment.pdf
	
ConfigurationSuppliment-book.pdf: ConfigurationSuppliment.pdf
	pdfbook2 ConfigurationSuppliment.pdf
	
clean:
	rm -f ConfigurationSuppliment-book.pdf ConfigurationSuppliment.pdf \
		*.bbl *.blg *.idx *.lof *.lot *.toc *.ilg *.ind *.out *~ *.bak

latex/refman.pdf: $(SRCS) Doxyfile
	rm -rf latex
	doxygen
	make -C latex/
