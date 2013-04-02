#ifndef WEAPON_XML_OBJECT_
#define WEAPON_XML_OBJECT_

#include "XMLObject.h"
#include <string>

class CWeaponXMLObject : public CXMLObject
{
public:
    CWeaponXMLObject();
    virtual ~CWeaponXMLObject();

    void SetEmitter(const std::string& strEmiterId);
    const std::string& GetEmitter() const;

    void SetBulletType(const std::string& strBulletTypeId);
    const std::string& GetBulletType() const;

private:
    std::string m_Emitter;
    std::string m_BulletType;
};

#endif