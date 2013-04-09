#ifndef XMLRESOURCE_
#define XMLRESOURCE_

#include "Parse_def.h"
#include "EmitterXMLParser.h"
#include "BlastXMLParser.h"
#include "BulletXMLParser.h"
#include "PlaneXMLParser.h"
#include "StageXMLParser.h"
#include "WeaponXMLParser.h"

typedef std::map<std::string, std::string> mapXMLList;

class CXMLResource
{
public:
    CXMLResource();
    virtual ~CXMLResource();

    bool LoadXML(const std::string& strPath);

private:

    bool _Parse(TiXmlDocument& tiDoc);

    bool _LoadGameXML(mapXMLList& mapXMLList);

    mapXMLList m_mapXMLList;
};

#endif