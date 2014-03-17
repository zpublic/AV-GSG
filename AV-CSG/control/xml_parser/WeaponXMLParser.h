#ifndef WEAPON_XML_PARSE_
#define WEAPON_XML_PARSE_

#include "unit\Singleton.h"
#include "XMLParser.h"
#include "WeaponXMLObject.h"
#include <string>
#include <map>

typedef std::map<std::string, CWeaponXMLObject*> WeaponList;

class CWeaponXMLParse
    : public Singleton<CWeaponXMLParse>
    , CXMLParser
{
    friend Singleton<CWeaponXMLParse>;
public:
    ~CWeaponXMLParse();

    virtual bool Initialize();

    bool LoadXML(const std::string& strPath);

    const CWeaponXMLObject* Get(const std::string& strId) const;
    const int Size() const;

private:
    CWeaponXMLParse();
    bool _Parse(TiXmlDocument& TinyXML);
    void _Close();
private:
    WeaponList m_mapWeapon;
};

#endif