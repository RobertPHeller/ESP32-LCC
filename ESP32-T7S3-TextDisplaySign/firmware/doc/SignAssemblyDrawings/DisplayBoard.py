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
#  Last Modified : <240506.2306>
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
    __Width=36.83
    __Height=57.15
    __Thick=1.6
    def __init__(self,name,origin):
        self.name = name
        if not isinstance(origin,Base.Vector):
             raise RuntimeError("origin is not a Vector!")
        self.origin = origin
        board=Part.makePlane(self.__Width,self.__Height,origin).extrude(Base.Vector(0,0,self.__Thick))
        self.board = board
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name); 
        obj.Shape=self.board
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([0.0,1.0,0.0])
        
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
    pinheader = doc.addObject('App::VRMLObject', 'PinHeader_1x10_P2')
    pinheader.VrmlFile = 'PinHeader_1x10_P2.wrl'
    pinheader.Label = 'PinHeader_1x10_P2'
    P1Xoff=19.3770
    P1Yoff=0
    pinheader.Placement = App.Placement(Base.Vector(P1Xoff,P1Yoff,0.8),\
                                        App.Rotation(Base.Vector(0,0,1),270))
    Gui.SendMsgToActiveView("ViewFit") 
    
