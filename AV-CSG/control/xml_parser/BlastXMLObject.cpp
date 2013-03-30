#include "stdafx.h"
#include "BlastXMLObject.h"

CBlastXMLObject::CBlastXMLObject()
    : m_Height(0)
    , m_Width(0)
    , m_FrameCount(0)
{
}

CBlastXMLObject::~CBlastXMLObject()
{
}

void CBlastXMLObject::SetWidth(int nWidth)
{
    m_Width = nWidth;
}

const int CBlastXMLObject::GetWidth() const
{
    return m_Width;
}

void CBlastXMLObject::SetHeight(int nHeight)
{
    m_Height = nHeight;
}

const int CBlastXMLObject::GetHeight() const
{
    return m_Height;
}

void CBlastXMLObject::SetFrameCount(int nFrameCount)
{
    m_FrameCount = nFrameCount;
}

const int CBlastXMLObject::GetFrameCount() const
{
    return m_FrameCount;
}

void CBlastXMLObject::SetSkinId(const std::string& strSkinId)
{
    m_SkinId = strSkinId;
}

const std::string& CBlastXMLObject::GetSkinId() const
{
    return m_SkinId;
}