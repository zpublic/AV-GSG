#ifndef BULLET_XML_PARSE_
#define BULLET_XML_PARSE_

#include "Parse_def.h"
#include "tinyxml.h"
#include "BulletXMLObject.h"
#include <map>
#include <string>

typedef std::map<std::string, CBulletXMLObject*> MapBulletList;

class CBulletXMLParse
{
public:
    ~CBulletXMLParse();
    static CBulletXMLParse& GetInstance();
    bool LoadXML(const std::string& strPath);

    const CBulletXMLObject* Get(const std::string& strId) const;
    const int Size() const;

private:
    bool _Parse(TiXmlDocument& TinyXML);
    void _Close();

private:
    CBulletXMLParse(CBulletXMLParse&);
    CBulletXMLParse& operator = (CBulletXMLParse&);
    CBulletXMLParse();
    static CBulletXMLParse m_Explosin;

    MapBulletList m_mapBullet;
};

#endif