#include "stdafx.h"
#include "BulletXMLObject.h"

CBulletXMLObject::CBulletXMLObject()
    : m_Power(0)
    , m_Speed(0)
    , m_Width(0)
    , m_FrameCount(0)
    , m_Height(0)
{
}

CBulletXMLObject::~CBulletXMLObject()
{
}

void CBulletXMLObject::SetSkinId(const std::string& strSkinId)
{
    m_SkinId = strSkinId;
}

const std::string& CBulletXMLObject::GetSkinId() const
{
    return m_SkinId;
}

void CBulletXMLObject::SetPower(int nPower)
{
    m_Power = nPower;
}
const int CBulletXMLObject::GetPower() const
{
    return m_Power;
}

void CBulletXMLObject::SetWidth(int nWidth)
{
    m_Width = nWidth;
}

const int CBulletXMLObject::GetWidth() const
{
    return m_Width;
}

void CBulletXMLObject::SetHeight(int nHeight)
{
    m_Height = nHeight;
}

const int CBulletXMLObject::GetHeight() const
{
    return m_Height;
}

void CBulletXMLObject::SetFrameCount(int nFrameCount)
{
    m_FrameCount = nFrameCount;
}

const int CBulletXMLObject::GetFrameCount() const
{
    return m_FrameCount;
}

void CBulletXMLObject::SetSpeed(int nSpeed)
{
    m_Speed = nSpeed;
}
const int CBulletXMLObject::GetSpeed() const
{
    return m_Speed;
}