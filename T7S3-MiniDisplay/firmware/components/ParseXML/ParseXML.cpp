// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 6 10:30:30 2026
//  Last Modified : <260406.1239>
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

static const char rcsid[] = "@(#) : $Id$";

#include "TinyXML.hxx"
#include <list>
#include <utility>
#include <string>
#include <functional>
#include <stack>
#include <unistd.h>

#include "ParseXML.hxx"

namespace ParseXML 
{
const std::string SimpleDOMElement::Attribute(std::string attribute) const
{
    for (auto a = attributes_.begin(); a != attributes_.end(); a++)
    {
        if (a->first == attribute) return a->second;
    }
    return std::string("");
}

void SimpleDOMElement::SetAttribute(std::string attribute, std::string value)
{
    for (auto a = attributes_.begin(); a != attributes_.end(); a++)
    {
        if (a->first == attribute) 
        {
            a->second = value;
            return;
        }
    }
    attributes_.push_back(std::make_pair(attribute,value));
}

const std::list<const SimpleDOMElement*> SimpleDOMElement::GetElementsByTagName(std::string thetag,int depth) const
{
    std::list<const SimpleDOMElement*> result;
    if (tag_ == thetag)
    {
        result.push_back(this);
    }
    if (depth == 0) return result;
    if (depth > 0) depth--;
    for (auto c = children_.begin(); c != children_.end(); c++)
    {
        auto elts = (*c)->GetElementsByTagName(thetag,depth);
        for (auto e = elts.begin(); e != elts.end(); e++)
        {
            result.push_back(*e);
        }
    }
    return result;
}

const std::list<const SimpleDOMElement*> SimpleDOMElement::GetElementsById(std::string theid) const
{
    std::list<const SimpleDOMElement*> result;
    if (Attribute("id") == theid)
    {
        result.push_back(this);
    }
    for (auto c = children_.begin(); c != children_.end(); c++)
    {
        auto elts = (*c)->GetElementsById(theid);
        for (auto e = elts.begin(); e != elts.end(); e++)
        {
            result.push_back(*e);
        }
    }
    return result;
}

bool SimpleDOMElement::IsChild(const SimpleDOMElement *item) const
{
    for (auto c = children_.begin(); c != children_.end(); c++)
    {
        if (*c == item) return true;
    }
    return false;
}

const SimpleDOMElement* SimpleDOMElement::GetParent (const SimpleDOMElement *item) const
{
    if (IsChild(item)) 
    {
        return this;
    }
    else
    {
        for (auto c = children_.begin(); c != children_.end(); c++)
        {
            auto result = (*c)->GetParent(item);
            if (result != nullptr) return result;
        }
        return nullptr;
    }
    
}

void SimpleDOMElement::RemoveChild (const SimpleDOMElement *item)
{
    for (auto c = children_.begin(); c != children_.end(); c++)
    {
        if (*c == item)
        {
            delete *c;
            children_.erase(c);
            break;
        }
    }
}

ParseXML::ParseXML(int ifd)
      : SimpleDOMElement("")
{
    TinyXML::TinyXML parser;
    uint8_t tempbuffer[DEFAULT_BUFFER_SIZE];
    uint8_t ch;
    int readStatus;
    parser.init(tempbuffer,sizeof(tempbuffer),
                std::bind(&ParseXML::xmlCallback_,this,std::placeholders::_1,
                          std::placeholders::_2,std::placeholders::_3,
                          std::placeholders::_4,std::placeholders::_5));
    nodeStack_.push(this);
    while ((readStatus = read(ifd,&ch,1)) > 0)
    {
        parser.processChar(ch);
    }
}

ParseXML::ParseXML(std::string xmlstring)
      : SimpleDOMElement("")
{
    TinyXML::TinyXML parser;
    uint8_t tempbuffer[DEFAULT_BUFFER_SIZE];
    uint8_t ch;
    parser.init(tempbuffer,sizeof(tempbuffer),
                std::bind(&ParseXML::xmlCallback_,this,std::placeholders::_1,
                          std::placeholders::_2,std::placeholders::_3,
                          std::placeholders::_4,std::placeholders::_5));
    nodeStack_.push(this);
    for (std::string::size_type i = 0; i < xmlstring.size(); i++)
    {
        ch = xmlstring[i];
        parser.processChar(ch); 
    }
}

ParseXML::~ParseXML()
{
}

void ParseXML::xmlCallback_(uint8_t errorflag, char* nameBuffer,  
                            uint16_t namebuflen, char* dataBuffer,  
                            uint16_t databuflen)
{
    switch (errorflag)
    {
    case STATUS_START_TAG:
        // _elementstart
        {
            SimpleDOMElement *parent = nodeStack_.top();
            SimpleDOMElement *node = new SimpleDOMElement(nameBuffer);
            nodeStack_.push(node);
            parent->AddChild(node);
        }
        break;
    case STATUS_TAG_TEXT:
        // _characterdata
        {
            SimpleDOMElement *curnode = nodeStack_.top();
            curnode->SetData(dataBuffer);
        }
        break;
    case STATUS_ATTR_TEXT:
        // ...
        {
            SimpleDOMElement *curnode = nodeStack_.top();
            curnode->SetAttribute(nameBuffer,dataBuffer);
        }
        break;
    case STATUS_END_TAG:
        // _elementend
        nodeStack_.pop();
    default:
    case STATUS_ERROR:
        // errors...
        break;
    }
}

}
