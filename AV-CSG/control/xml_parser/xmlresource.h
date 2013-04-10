#ifndef XMLRESOURCE_
#define XMLRESOURCE_

#include "Parse_def.h"
#include "unit\Singleton.h"
#include "EmitterXMLParser.h"
#include "BlastXMLParser.h"
#include "BulletXMLParser.h"
#include "PlaneXMLParser.h"
#include "StageXMLParser.h"
#include "WeaponXMLParser.h"
#include "data\resourcedata\PicturePool.h"

typedef std::map<std::string, std::string> mapXMLList;

class CXMLResource : public Singleton<CXMLResource>
{
    friend Singleton<CXMLResource>;
public:
    virtual ~CXMLResource();

    bool LoadXML(const std::string& strPath);

    virtual bool Initialize();

private:
    CXMLResource();

    bool _Parse(TiXmlDocument& tiDoc);

    bool _LoadGameXML(mapXMLList& mapXMLList);

    mapXMLList m_mapXMLList;
};

#endif