#*****************************************************************************
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Thu Jan 4 19:47:45 2018
#  Last Modified : <230303.1710>
#
#  Description	
#
#  Notes
#
#  History
#	
#*****************************************************************************
#
#    Copyright (C) 2018  Robert Heller D/B/A Deepwoods Software
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


package require snit

snit::type POSReceiptPrinter {
        
    variable deviceChan
    constructor {deviceName args} {
        #puts stderr "$type create $self $deviceName $args"
        if {[catch {open $deviceName w} deviceChan]} {
            #puts stderr "$type create $self: deviceChan is $deviceChan"
            set errorMessage "$deviceChan"
            catch {unset deviceChan}
            error $errorMessage
            return
        }
        #$self configurelist $args
        $self _initializePrinter
    }
    destructor {
        catch {
            $self _initializePrinter
            close $deviceChan
        }
    }
    method _xputchar {c} {
        puts -nonewline $deviceChan "[format %c $c]"
    }
    method _putchar {char} {
        puts -nonewline $deviceChan "$char"
    }
    method textLine {text} {
        puts $deviceChan $text
    }
    method printMode {modebyte} {
        $self _xputchar 0x1b
        $self _putchar "!"
        $self _xputchar $modebyte
    }
    method setAbsPrintPos {xpos} {
        $self _xputchar 0x1b
        $self _putchar {$}
        $self _xputchar [expr {$xpos & 0x0ff}]
        $self _xputchar [expr {($xpos >> 8) & 0x0ff}]
    }
    method underlineOnThin {} {
        $self _xputchar 0x1b
        $self _putchar "-"
        $self _xputchar 1
    }
    method underlineOnThick {} {
        $self _xputchar 0x1b
        $self _putchar "-"
        $self _xputchar 2
    }
    method underlineOff {} {
        $self _xputchar 0x1b
        $self _putchar "-"
        $self _xputchar 0
    }
    method defaultLineSpacing {} {
        $self _xputchar 0x1b
        $self _putchar "2"
    }
    method lineSpacing {spacing} {
        $self _xputchar 0x1b
        $self _putchar "3"
        $self _xputchar $spacing
    }
    method _initializePrinter {} {
        $self _xputchar 0x1b
        $self _putchar "@"
    }
    method _setTabs {tabs} {
        $self _xputchar 0x1b
        $self _putchar "D"
        foreach t $tabs {$self _xputchar $t}
        $self _xputchar 0
    }
    method _emphasizedOn {} {
        $self _xputchar 0x1b
        $self _putchar "E"
        $self _xputchar 1
    }
    method _emphasizedOff {} {
        $self _xputchar 0x1b
        $self _putchar "E"
        $self _xputchar 0
    }
    method _doubleStrikeOn {} {
        $self _xputchar 0x1b
        $self _putchar "G"
        $self _xputchar 1
    }
    method _doubleStrikeOff {} {
        $self _xputchar 0x1b
        $self _putchar "G"
        $self _xputchar 0
    }
    method printAndFeed {space} {
        $self _xputchar 0x1b
        $self _putchar "J"
        $self _xputchar $space
    }
    method selectFontA {} {
        $self _xputchar 0x1b
        $self _putchar "M"
        $self _xputchar 0
    }
    method selectFontB {} {
        $self _xputchar 0x1b
        $self _putchar "M"
        $self _xputchar 1
    }
    method internationCharSet {set} {
        set indx [lsearch {usa france germany uk denmarki sweden italy spaini japan norway denmarkii spainii latinamerica} [string tolower $set]]
        if {$indx < 0} {set indx 0}
        $self _xputchar 0x1b
        $self _putchar "R"
        $self _xputchar $indx
    }
    method setRelPrintPos {xpos} {
        $self _xputchar 0x1b
        $self _putchar "\\"
        $self _xputchar [expr {$xpos & 0x0ff}]
        $self _xputchar [expr {($xpos >> 8) & 0x0ff}]
    }
    method selectLeftJustification {} {
        $self _xputchar 0x1b
        $self _putchar "a"
        $self _xputchar 0
    }
    method selectCenterJustification {} {
        $self _xputchar 0x1b
        $self _putchar "a"
        $self _xputchar 1
    }
    method selectRightJustification {} {
        $self _xputchar 0x1b
        $self _putchar "a"
        $self _xputchar 2
    }
    method feed {lines} {
        $self _xputchar 0x1b
        $self _putchar "d"
        $self _xputchar $lines
    }
    method selectCharacterCodeTable {{tab 0}} {
        $self _xputchar 0x1b 
        $self _putchar "t"
        $self _xputchar $tab
    }
    method refersePrintingOn {} {
        $self _xputchar 0x1d
        $self _putchar "B"
        $self _xputchar 1
    }
    method refersePrintingOff {} {
        $self _xputchar 0x1d
        $self _putchar "B"
        $self _xputchar 0
    }
    method setLeftMargin {xpos} {
        $self _xputchar 0x1d
        $self _putchar "L"
        $self _xputchar [expr {$xpos & 0x0ff}]
        $self _xputchar [expr {($xpos >> 8) & 0x0ff}]
    }
    method setUnits {xunit yunit} {
        $self _xputchar 0x1d
        $self _putchar "P"
        $self _xputchar $xunit
        $self _xputchar $yunit
    }
    method setPrintWidth {width} {
        $self _xputchar 0x1d
        $self _putchar "W"
        $self _xputchar [expr {$width & 0x0ff}]
        $self _xputchar [expr {($width >> 8) & 0x0ff}]
    }
    method printRasterBitImage {width height data {mode 0}} {
        $self _xputchar 0x1d
        $self _putchar "v"
        $self _putchar "0"
        $self _xputchar $mode
        set bytewidth [expr {($width + 7) >> 3}]
        $self _xputchar [expr {$bytewidth & 0x0ff}]
        $self _xputchar [expr {($bytewidth >> 8) & 0x0ff}] 
        $self _xputchar [expr {$height & 0x0ff}]
        $self _xputchar [expr {($height >> 8) & 0x0ff}]
        foreach b $data {$self _xputchar $b}
    }
    method selectCharacterSize {height width} {
        $self _xputchar 0x1d
        $self _putchar "!"
        set byte 0
        switch $height {
            double {set byte 1}
            default -
            single {set byte 0}
        }
        switch $width {
            double {set byte [expr {$byte | 0x10}]}
            default -
            single {set byte [expr {$byte & 0x0F}]}
        }
        $self _xputchar $byte
    }
            
}


package provide ReceiptPrinter 1.0
