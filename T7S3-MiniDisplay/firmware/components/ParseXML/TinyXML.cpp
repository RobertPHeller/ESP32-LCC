/* LCD library for noka 3110 display
 * Date: January 2010
 * Author: J Crouchley
 *
 * This is a table driven parser for simple XML,
 * Pass the XML into the library one character at a time
 * the callback function will be called at 'interesting'
 * point (got a tag, got an attribute value, tag text, end of tag)
 * with information about the tags and any values.
 *
 * See the examples for usage
 */
#include <inttypes.h>
#include "utils/logging.h"
#include "TinyXMLTable.hxx"

#include "TinyXML.hxx"


#define DEBUG 6
namespace TinyXML {

parseTable *pTable = (parseTable *)&stateTable;


TinyXML::TinyXML()
{
}

void TinyXML::init(uint8_t* buffer, uint16_t maxbuflen, XMLcallback XMLcb)
{
  Xcb = std::move(XMLcb);
  dataBuffer = buffer;
  maxDataLen = maxbuflen - 1;
  reset();
}

void TinyXML::reset()
{
  dataBufferPtr =0;
  tagBufferPtr = 0;
  LTCount = 0;
  tagCount = 0;
  currentState = Init;
}

void TinyXML::processChar(uint8_t ch)
{
  uint16_t chToParse;
  bool bMatch=false;
  while (!bMatch)
  {
    chToParse = pTable[currentState].charToParse;
    switch ( chToParse )
    {
    case whiteSpace:
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') bMatch=true;
      break;
    case alpha:
      if (isAlpha(ch))  bMatch=true;
      break;
    case alphanum:
      if (isAlpha(ch) || isNumeric(ch) || (ch == ':') || (ch == '_') || (ch == '-'))  bMatch=true;
      break;
    case quote:
      if (ch == '"' || ch == '\'')
      {
        matchQuote = ch;
        bMatch=true;
      }
      break;
    case matchingquote:
      if (ch == matchQuote) bMatch=true;
      break;
    case anychar:
      bMatch=true;
      break;
    default:
      if (ch == chToParse) bMatch=true;
      break;
    }
    if (!bMatch)
    {
#if DEBUG > 3
        LOG(INFO,"[TinyXML] Non-matching state: %d ch: %02x match criteria: %02x new state: %d",currentState,ch,chToParse,currentState+1);
#endif
      currentState++;
    }
  } // as every table enry must end in anychar we must get out of here

#if DEBUG > 2
     LOG(INFO,"[TinyXML] Matching state:%d ch: %02x match criteria: %02x tagBufferPtr:%d new state:%d",currentState,ch,chToParse,tagBufferPtr,pTable[currentState].nextState);
#endif
  action(ch, pTable[currentState].actionNumber);
  action(ch, pTable[currentState].actionNumber2);

  currentState=pTable[currentState].nextState;
}



void TinyXML::action(uint8_t ch, uint8_t actionType)
{
#if DEBUG > 5
    LOG(INFO,"[TinyXML] Action:%d",actionType);
#endif
    switch (actionType)
    {
    case donothing:
        break;
    case incLTcount:
        LTCount++;
        break;
    case decLTcount:
        if (LTCount == 0)
        {
            action(ch,error);
        }
        else
        {
            LTCount--;
        }
        break;
    case cleardata:
        dataBufferPtr = 0;
        break;
    case storeifneeded:
        if (dataBufferPtr < maxDataLen) dataBuffer[dataBufferPtr++] = ch;
        break;
    case starttagname:
        dataBuffer[dataBufferPtr] = 0; // terminate the text
        // call back if the previous tag text is required
        tagBuffer[tagBufferPtr] = 0;
        if (tagBufferPtr && dataBufferPtr) Xcb(STATUS_TAG_TEXT,(char*)tagBuffer,tagBufferPtr,(char*)dataBuffer,dataBufferPtr);
        dataBufferPtr = 0;    // clear down for next time
#if DEBUG > 2
        LOG(INFO,"[TinyXML] starttagname Tag:%s text:%s",(char*)tagBuffer,(char*)dataBuffer);
#endif
        if (tagBufferPtr < TAGBUFFERMAX) tagBuffer[tagBufferPtr++] = '/';
        else action(ch, error);
        break;
    case cleartagname:
        if (tagBufferPtr)
            tagBuffer[--tagBufferPtr]=0;  // remove the slash
        break;
    case addtotagname:
        if (tagBufferPtr < TAGBUFFERMAX) tagBuffer[tagBufferPtr++] = ch;
        else action(ch, error);
        break;
    case inctagcount:
        tagCount++;
        tagBuffer[tagBufferPtr] = 0;
        Xcb(STATUS_START_TAG,(char*)tagBuffer,tagBufferPtr,0,0);
#if DEBUG > 2
        LOG(INFO,"[TinyXML] incTagCount:%d Tags found:%s",tagCount,(char*)tagBuffer);
#endif
        break;
    case removelasttag:
        if (--tagCount < 0 )
	{
            action(ch,error);
            break;
	}
        tagBuffer[tagBufferPtr] = 0;
        Xcb(STATUS_END_TAG,(char*)tagBuffer,tagBufferPtr,0,0);
        while (tagBufferPtr && tagBuffer[--tagBufferPtr] != '/'); // as we error if tagBuffer overflows then this will be safe
#if DEBUG > 3
        tagBuffer[tagBufferPtr] = 0;
        LOG(INFO,"[TinyXML] removelasttag TagCount:%d tagBufferPtr:%d Tags found:%s",tagCount,tagBufferPtr,(char*)tagBuffer);
#endif
        break;
    case cleartagendname:
        checkTagBufferPtr = 0;
        break;
    case addtochktagname:
        if (checkTagBufferPtr < CHECKTAGMAX) checkTagBuffer[checkTagBufferPtr++] = ch;
        else action(ch, error);
        break;
    case checkremovelasttag:
        // need to test here to see if the tag being removed is the correct one - error if not
        if (--tagCount < 0 )
	{
            action(ch,error);
            break;
	}
        tagBufferPtr--;      // we have had a start so back past the last '/' we placed when the tag started
        tagBuffer[tagBufferPtr] = 0;
        Xcb(STATUS_END_TAG,(char*)tagBuffer,tagBufferPtr,0,0);
        while (tagBufferPtr && tagBuffer[--tagBufferPtr] != '/'); // as we error if tagBuffer overflows then this will be safe
#if DEBUG > 3
        tagBuffer[tagBufferPtr] = 0;
        LOG(INFO,"[TinyXML] checkremovelasttag TagCount:%d tagBufferPtr:%d Tags found:%s",tagCount,tagBufferPtr,(char*)tagBuffer);
#endif
        break;
    case clearattrname:
        attrBufferPtr = 0;
        dataBufferPtr = 0;
        break;
    case addtoattrname:
        attrBuffer[attrBufferPtr++] = ch;
        break;
    case setquotechar:
        matchQuote = ch;
        break;
    case addtoattrvalue:
        if (dataBufferPtr < maxDataLen) dataBuffer[dataBufferPtr++] = ch;
        break;
    case gotattrvalue:
        attrBuffer[attrBufferPtr] = 0;
        dataBuffer[dataBufferPtr] = 0;
        Xcb(STATUS_ATTR_TEXT,(char*)attrBuffer,attrBufferPtr,(char*)dataBuffer,dataBufferPtr);
        dataBufferPtr = 0;
        break;
    case error:
        Xcb(STATUS_ERROR,(char*)tagBuffer,tagBufferPtr,(char*)dataBuffer,dataBufferPtr);
        reset();
        break;
    case initialise:
        reset();
        break;
    }
}

}
