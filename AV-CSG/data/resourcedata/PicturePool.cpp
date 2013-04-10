#include "stdafx.h"
#include "PicturePool.h"
#include "PictureMap.h"

CPicturePool * CPicturePool::m_pPicturePool = NULL;

CPicturePool * CPicturePool::GetInstance()
{
    if (NULL == m_pPicturePool)
    {
        m_pPicturePool = new CPicturePool();
    }
    return m_pPicturePool;
}

CPicturePool::CPicturePool(void)
{
}

CPicturePool::~CPicturePool(void)
{
}

void CPicturePool::FreeImage()
{
    for (auto i = m_mapPic.begin(); i != m_mapPic.end(); ++i)
    {
        i->second->FreeBitmap();
    }
    m_mapPic.clear();
}

void CPicturePool::LoadImage(LPCWSTR lpFilePath)
{
    CPictureMap picMap;
    std::map<std::string, PictureNode> mapPicture;
    picMap.LoadXml(lpFilePath, mapPicture);
    for (auto i = mapPicture.begin(); i != mapPicture.end(); ++i)
    {
        CPicture* pPic = new CPicture();
        pPic->LoadBitmap(
            i->second.strPath.c_str(),
            RGB(i->second.r, i->second.g, i->second.b),
            i->second.width, i->second.height);
        m_mapPic[i->first] = pPic;
    }
}

CPicture* CPicturePool::GetPicture(const std::string& picID) const
{
    auto It = m_mapPic.find(picID);
    if (It == m_mapPic.end())
    {
        return 0;
    }
    return It->second;
}