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
    for (int i = 0; i < emBlastTypeMax; ++i)
    {
        m_pPictureBlast[i]->FreeBitmap();
    }
    for(int i = 0; i < emBulletTypeMax; ++i)
    {
        m_pPictureAmmo[i]->FreeBitmap();
    }
    for(int i = 0; i < emEnemyTypeMax; ++i)
    {
        m_pPictureEnemy[i]->FreeBitmap();
    }
    pPicturePlane->FreeBitmap();
    pPictureLife->FreeBitmap();
    pPictureHP->FreeBitmap();
    pPictureHPSide->FreeBitmap();
    pPictureNum->FreeBitmap();
}

void CPicturePool::LoadImage()
{
    CPictureMap picMap;
    std::map<int, PictureNode> mapPicture;
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

    for (int i = 0; i < emBlastTypeMax; ++i)
    {
        m_pPictureBlast[i] = new CPicture();
    }

    m_pPictureBlast[0]->LoadBitmap(_T("Resource\\BulletBlast.bmp"), RGB(255, 0, 255));
    m_pPictureBlast[1]->LoadBitmap(_T("Resource\\PlaneBlast.bmp"), RGB(0, 0, 0));

    for(int i = 0; i < emBulletTypeMax; ++i)
    {
        m_pPictureAmmo[i] = new CPicture();
    }
    m_pPictureAmmo[0]->LoadBitmap(_T("Resource\\Ammo0.bmp"), RGB(255, 0, 255));
    m_pPictureAmmo[1]->LoadBitmap(_T("Resource\\Ammo1.bmp"), RGB(255, 0, 255));
    m_pPictureAmmo[2]->LoadBitmap(_T("Resource\\Ammo2.bmp"), RGB(255, 0, 255));
    m_pPictureAmmo[3]->LoadBitmap(_T("Resource\\Ammo3.bmp"), RGB(255, 0, 255));
    m_pPictureAmmo[4]->LoadBitmap(_T("Resource\\Ammo4.bmp"), RGB(255, 0, 255));
    m_pPictureAmmo[5]->LoadBitmap(_T("Resource\\Ammo5.bmp"), RGB(0, 0, 0));
    m_pPictureAmmo[6]->LoadBitmap(_T("Resource\\Ammo6.bmp"), RGB(0, 0, 0));
    m_pPictureAmmo[7]->LoadBitmap(_T("Resource\\WholeFried.bmp"), RGB(0, 248, 0));
    m_pPictureAmmo[8]->LoadBitmap(_T("Resource\\AmmoSb.bmp"), RGB(255, 255, 255));
    m_pPictureAmmo[9]->LoadBitmap(_T("Resource\\AmmoSb2.bmp"), RGB(255, 255, 255));

    for(int i = 0; i < emEnemyTypeMax; ++i)
    {
        m_pPictureEnemy[i] = new CPicture();
    }
    m_pPictureEnemy[0]->LoadBitmap(_T("Resource\\Enemy0.bmp"), RGB(255, 255, 255));
    m_pPictureEnemy[1]->LoadBitmap(_T("Resource\\Enemy1.bmp"), RGB(255, 255, 255));
    m_pPictureEnemy[2]->LoadBitmap(_T("Resource\\Enemy2.bmp"), RGB(255, 255, 255));
    m_pPictureEnemy[3]->LoadBitmap(_T("Resource\\Enemy3.bmp"), RGB(255, 255, 255));
    m_pPictureEnemy[4]->LoadBitmap(_T("Resource\\Enemy4.bmp"), RGB(255, 255, 255));

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

CPicture** CPicturePool::GetPicture(PictureType picType)
{
    CPicture** ppPic = NULL;
    switch (picType)
    {
    case emPicTypeBullet:
        ppPic = (CPicture**)&m_pPictureAmmo;
        break;
    case emPicTypeExplosion:
        ppPic = (CPicture**)&m_pPictureBlast;
        break;
    case emPicTypePlane:
        ppPic = (CPicture**)&m_pPictureEnemy;
        break;
    default:
        break;
    }
    return ppPic;
}
