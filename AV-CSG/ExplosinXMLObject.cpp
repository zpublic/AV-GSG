#include "stdafx.h"
#include "ExplosinXMLObject.h"

CExplosinXMLObject::CExplosinXMLObject()
    : m_Power(0)
    , m_Speed(0)
    , m_Width(0)
    , m_FrameCount(0)
    , m_Height(0)
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

void CExplosinXMLObject::SetPower(int nPower)
{
    m_Power = nPower;
}
const int CExplosinXMLObject::GetPower() const
{
    return m_Power;
}

void CExplosinXMLObject::SetWidth(int nWidth)
{
    m_Width = nWidth;
}

const int CExplosinXMLObject::GetWidth() const
{
    return m_Width;
}

void CExplosinXMLObject::SetHeight(int nHeight)
{
    m_Height = nHeight;
}

const int CExplosinXMLObject::GetHeight() const
{
    return m_Height;
}

void CExplosinXMLObject::SetFrameCount(int nFrameCount)
{
    m_FrameCount = nFrameCount;
}

const int CExplosinXMLObject::GetFrameCount() const
{
    return m_FrameCount;
}

void CExplosinXMLObject::SetSpeed(int nSpeed)
{
    m_Speed = nSpeed;
}
const int CExplosinXMLObject::GetSpeed() const
{
    return m_Speed;
}