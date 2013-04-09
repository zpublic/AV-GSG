#ifndef XMLRESOURCE_
#define XMLRESOURCE_

#include "Parse_def.h"
#include "EmitterXMLParser.h"
#include "BlastXMLParser.h"
#include "PlaneXMLParser.h"
#include "StageXMLParser.h"
#include "WeaponXMLParser.h"

typedef std::map<std::string, std::string> mapXMLList;

class CXMLResource
{
public:
    CXMLResource();
    virtual ~CXMLResource();

    int LoadXML(const std::string& strPath);

private:

    int _Parse(TiXmlDocument& tiDoc);

    mapXMLList m_mapXMLList;
};

#endif