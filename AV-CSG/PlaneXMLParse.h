#ifndef PLANE_XML_PARSE_
#define PLANE_XML_PARSE_

#include "Parse_def.h"
#include "../Import/tinyxml-2.6.2/tinyxml.h"
#include "PlaneXMLObject.h"
#include <map>
#include <string>

typedef std::map<std::string, CPlaneXMLObject*> MapPlane;

class CPlaneXMLParse
{
public:
    ~CPlaneXMLParse();
    static CPlaneXMLParse& GetInstance();
    bool LoadXML(const std::string& strPath);
    const CPlaneXMLObject* GetEnemyPlane(const std::string& strId) const;
    const CPlaneXMLObject* GetSelfPlane(const std::string& strId) const;

    const int EnemyTypeMax() const;
    const int SelfTypeMax() const;

private:
    CPlaneXMLParse(CPlaneXMLParse&);
    CPlaneXMLParse& operator = (CPlaneXMLParse&);
    CPlaneXMLParse();
    static CPlaneXMLParse m_Plane;

private:
    void _Close();
    bool _Parse(TiXmlDocument& TinyXML);

private:
    MapPlane m_mapEnemy;
    MapPlane m_mapSelf;
};

#endif