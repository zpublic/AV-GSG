#include "stdafx.h"
#include "ExplosinXMLObject.h"

CExplosinXMLObject::CExplosinXMLObject()
    : m_Power(0)
    , m_Speed(0)
{
}

CExplosinXMLObject::~CExplosinXMLObject()
{
}

void CExplosinXMLObject::SetSkinId(const std::string& strSkinId)
{
    m_SkinId = strSkinId;
}

const std::string& CExplosinXMLObject::GetSkinId() const
{
    return m_SkinId;
}

void CExplosinXMLObject::SetPower(int nBulletType)
{
    m_Power = nBulletType;
}
const int CExplosinXMLObject::GetPower() const
{
    return m_Power;
}

void CExplosinXMLObject::SetSpeed(int nSpeed)
{
    m_Speed = nSpeed;
}
const int CExplosinXMLObject::GetSpeed() const
{
    return m_Speed;
}