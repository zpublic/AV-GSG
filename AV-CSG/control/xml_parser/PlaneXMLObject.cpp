#include "stdafx.h"
#include "PlaneXMLObject.h"

CPlaneXMLObject::CPlaneXMLObject()
    : m_HP(0)
    , m_Speed(0)
{
}

CPlaneXMLObject::~CPlaneXMLObject()
{
}

void CPlaneXMLObject::SetSkinId(const std::string& strSkinId)
{
    m_SkinId = strSkinId;
}

const std::string& CPlaneXMLObject::GetSkinId() const
{
    return m_SkinId;
}

void CPlaneXMLObject::SetHP(long lnHP)
{
    m_HP = lnHP;
}
const long CPlaneXMLObject::GetHP() const
{
    return m_HP;
}

void CPlaneXMLObject::SetWeapon(const std::string& strBulletType)
{
    m_Weapon = strBulletType;
}
 const std::string& CPlaneXMLObject::GetWeapon() const
{
    return m_Weapon;
}

void CPlaneXMLObject::SetSpeed(int nSpeed)
{
    m_Speed = nSpeed;
}
const int CPlaneXMLObject::GetSpeed() const
{
    return m_Speed;
}