#include "WeaponXMLObject.h"


CWeaponXMLObject::CWeaponXMLObject()
{
}

CWeaponXMLObject::~CWeaponXMLObject()
{
}

void CWeaponXMLObject::SetEmitter(const std::string& strEmiterId)
{
    m_Emitter = strEmiterId;
}

const std::string& CWeaponXMLObject::GetEmitter() const
{
    return m_Emitter;
}

void CWeaponXMLObject::SetBulletType(const std::string& strBulletTypeId)
{
    m_BulletType = strBulletTypeId;
}


const std::string& CWeaponXMLObject::GetBulletType() const
{
    return m_BulletType;
}