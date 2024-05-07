#*****************************************************************************
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Mon May 6 21:12:14 2024
#  Last Modified : <240507.1427>
#
#  Description	
#
#  Notes
#
#  History
#	
#*****************************************************************************
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
#*****************************************************************************

import FreeCADGui
import Part
from FreeCAD import Base
import FreeCAD as App
import os
import sys
sys.path.append(os.path.dirname(__file__))
import Mesh

import datetime

class DisplayPCB(object):
    Width=36.83
    Height=57.15
    Thick=1.6
    P1Xoff=19.729
    P1Yoff=-.019708
    DisplayHeight=45.83
    DisplayWidth=34
    DisplayThick=2.4
    DisplayXoff=1.3
    DisplayYoff=8.175
    def __init__(self,name,origin):
        self.name = name
        if not isinstance(origin,Base.Vector):
             raise RuntimeError("origin is not a Vector!")
        self.origin = origin
        board=Part.makePlane(self.Width,self.Height,origin)\
                    .extrude(Base.Vector(0,0,self.Thick))
        self.board = board
        d1 = Part.makePlane(self.DisplayWidth,self.DisplayHeight,\
                            origin.add(Base.Vector(self.DisplayXoff,\
                                                   self.DisplayYoff,\
                                                   self.Thick)))\
                .extrude(Base.Vector(0,0,self.DisplayThick))
        self.frontDisplay = d1
        d2 = Part.makePlane(self.DisplayWidth,self.DisplayHeight,\
                            origin.add(Base.Vector(self.DisplayXoff,\
                                                   self.DisplayYoff,\
                                                   -self.DisplayThick)))\
                .extrude(Base.Vector(0,0,self.DisplayThick))
        self.backDisplay = d2
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name); 
        obj.Shape=self.board
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([0.0,1.0,0.0])
        obj = doc.addObject('App::VRMLObject', 'PinHeader_1x10_P2')
        obj.VrmlFile = 'PinHeader_1x10_P2.wrl' 
        obj.Label = 'PinHeader_1x10_P2'
        obj.Placement = Base.Placement(Base.Vector(self.P1Xoff, \
                                                   self.P1Yoff, \
                                                   self.Thick/2),\
                                       Base.Rotation(Base.Vector(0,0,1),270))
        obj = doc.addObject("Part::Feature",self.name+"_frontDisplay")
        obj.Shape=self.frontDisplay
        obj.Label=self.name+"_frontDisplay"
        obj.ViewObject.ShapeColor=tuple([1.0,1.0,1.0])
        obj = doc.addObject("Part::Feature",self.name+"_backDisplay")
        obj.Shape=self.backDisplay
        obj.Label=self.name+"_backDisplay"
        obj.ViewObject.ShapeColor=tuple([1.0,1.0,1.0])

class StyreenSpacerPanel(object):
    __C2Xoff=6.7
    __C2Yoff=0
    __C2Width=32.82-6.6133
    __C2Height=6.136789
    def __init__(self,name,origin):
        self.name = name
        if not isinstance(origin,Base.Vector):
            raise RuntimeError("origin is not a Vector!")
        self.origin = origin
        panel = Part.makePlane(DisplayPCB.Width,DisplayPCB.Height,origin) \
                .extrude(Base.Vector(0,0,DisplayPCB.DisplayThick))
        cutout = Part.makePlane(DisplayPCB.DisplayWidth,\
                                DisplayPCB.DisplayHeight,\
                                origin.add(Base.Vector(DisplayPCB.DisplayXoff,\
                                                       DisplayPCB.DisplayYoff,\
                                                       0)))\
                 .extrude(Base.Vector(0,0,DisplayPCB.DisplayThick))
        panel = panel.cut(cutout)
        cutout = Part.makePlane(self.__C2Width,self.__C2Height,\
                                origin.add(Base.Vector(self.__C2Xoff,\
                                                       self.__C2Yoff,0)))\
                  .extrude(Base.Vector(0,0,DisplayPCB.DisplayThick))
        self.panel = panel.cut(cutout)
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name)
        obj.Shape=self.panel
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([1.0,1.0,1.0])

## This is how App.getDocument() *should* be written.
def getDocument(name):
    docs = App.listDocuments()
    for key in docs:
        if key==name:
            return docs[key]
    return None

if __name__ == '__main__':
    doc = getDocument('DisplayBoard')
    if doc==None:
        doc = App.newDocument("DisplayBoard")
    App.ActiveDocument=doc
    for o in doc.Objects:
        doc.removeObject(o.Label)
    board = DisplayPCB("pcb",Base.Vector(0,0,0))
    board.show(doc)
    frontStyreen = StyreenSpacerPanel("front",Base.Vector(0,0,25.4))
    frontStyreen.show(doc)
    backStyreen = StyreenSpacerPanel("front",Base.Vector(0,0,-25.4))
    backStyreen.show(doc)
    Gui.SendMsgToActiveView("ViewFit") 
    
