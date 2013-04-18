#ifndef XML_PARSER_
#define XML_PARSER_

#include <string>
#include "unit\Unit.h"
#include "tinyxml.h"
#include "XMLObject.h"
#include "Parse_def.h"

class CXMLParser
{
public:
    CXMLParser();
    virtual ~CXMLParser();

    virtual bool LoadXML(const std::string& strPath) = 0;

protected:
    virtual bool BaseParse(CXMLObject* xmlobj, TiXmlElement* tiElement);
    virtual bool BasePos(PosObject* posobj, TiXmlElement* tiElement);
};

#endif