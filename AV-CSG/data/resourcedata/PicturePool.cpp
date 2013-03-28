#include "stdafx.h"
#include "PicturePool.h"
#include "PictureMap.h"

CPicturePool * CPicturePool::m_pPicturePool = NULL;

CPicturePool * CPicturePool::GetInstance()
{
    if (NULL == m_pPicturePool)
    {
        m_pPicturePool = new CPicturePool();
        m_pPicturePool->LoadImage();
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
    pPicturePlane->FreeBitmap();
    pPictureLife->FreeBitmap();
    pPictureHP->FreeBitmap();
    pPictureHPSide->FreeBitmap();
    pPictureNum->FreeBitmap();
}

void CPicturePool::LoadImage()
{
    CPictureMap picMap;
    std::map<std::string, PictureNode> mapPicture;
    TCHAR filePath[MAX_PATH] = {0};
    ::GetModuleFileName(0, filePath, MAX_PATH);
    ::PathRemoveFileSpec(filePath);
    ::PathAppend(filePath, _T("Resource\\picture.xml"));
    picMap.LoadXml(filePath, mapPicture);
    for (auto i = mapPicture.begin(); i != mapPicture.end(); ++i)
    {
        CPicture* pPic = new CPicture();
        pPic->LoadBitmap(
            i->second.strPath.c_str(),
            RGB(i->second.r, i->second.g, i->second.b));
        m_mapPic[i->first] = pPic;
    }

    pPicturePlane = new CPicture();
    pPictureLife = new CPicture();
    pPictureHP = new CPicture();
    pPictureHPSide = new CPicture();
    pPictureNum = new CPicture();
    pPicturePlane->LoadBitmap(_T("Resource\\OurFighter.bmp"), RGB(0, 255, 0));
    pPictureLife->LoadBitmap(_T("Resource\\Life.bmp"), RGB(255, 0, 255));
    pPictureHP->LoadBitmap(_T("Resource\\HPBar.bmp"), RGB(255, 0, 255));
    pPictureHPSide->LoadBitmap(_T("Resource\\HPBarSide.bmp"), RGB(255, 0, 255));
    pPictureNum->LoadBitmap(_T("Resource\\Num.bmp"), RGB(0, 0, 0));
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