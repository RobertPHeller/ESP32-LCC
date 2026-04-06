// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 6 08:11:23 2026
//  Last Modified : <260406.1237>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2026  Robert Heller D/B/A Deepwoods Software
//			51 Locke Hill Road
//			Wendell, MA 01379-9728
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __PARSEXML_HXX
#define __PARSEXML_HXX

#include "TinyXML.hxx"
#include <list>
#include <utility>
#include <string>
#include <stack>

namespace ParseXML
{
class SimpleDOMElement {
public:
    SimpleDOMElement(std::string tag)
                : tag_(tag)
    {
    }
    ~SimpleDOMElement()
    {
        attributes_.clear();
        options_.clear();
        for (auto c = children_.begin(); c != children_.end(); c++)
        {
            delete *c;
        }
        children_.clear();
        
    }
    const std::list<SimpleDOMElement*> Children() const {return children_;}
    void AddChild(SimpleDOMElement *childnode)
    {
        children_.push_back(childnode);
    }
    size_t length() const
    {
        return children_.size();
    }
    const std::string Data() const {return data_;}
    void SetData(std::string d) {data_ = d;}
    const std::string Attribute(std::string attribute) const;
    void SetAttribute(std::string attribute, std::string value="");
    const std::list<const SimpleDOMElement*> GetElementsByTagName(std::string thetag,int depth=-1) const;
    const std::list<const SimpleDOMElement*> GetElementsById(std::string theid) const;
    bool IsChild(const SimpleDOMElement *item) const;
    const SimpleDOMElement* GetParent (const SimpleDOMElement *item) const;
    void RemoveChild (const SimpleDOMElement* item);
private:
    std::string tag_;
    std::list<std::pair<std::string,std::string>> attributes_;
    std::list<std::pair<std::string,std::string>> options_;
    std::list<SimpleDOMElement*> children_;
    std::string data_;
};

class ParseXML : public SimpleDOMElement
{
public:
    ParseXML(int ifd);
    ParseXML(std::string xmlstring);
    ~ParseXML();
private:
    void xmlCallback_(uint8_t errorflag, char* nameBuffer,  uint16_t namebuflen, char* dataBuffer,  uint16_t databuflen);
    std::stack<SimpleDOMElement *> nodeStack_;
};
}

#endif // __PARSEXML_HXX

