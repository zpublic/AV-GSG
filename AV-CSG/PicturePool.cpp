#include "stdafx.h"
#include "PicturePool.h"

CPicture * CPicturePool::m_pPictureBlast[2] = {0};
CPicture * CPicturePool::m_pPictureAmmo[8] = {0};

CPicturePool::CPicturePool(void)
{
}

CPicturePool::~CPicturePool(void)
{
}

void CPicturePool::FreeImage()
{
    for (int i = 0; i < 2; ++i)
    {
        m_pPictureBlast[i]->FreeBitmap();
    }
    for(int i = 0; i < 8; ++i)
    {
        m_pPictureAmmo[i]->FreeBitmap();
    }
}

void CPicturePool::LoadImage()
{
    for (int i = 0; i < 2; ++i)
    {
        m_pPictureBlast[i] = new CPicture();
    }

    m_pPictureBlast[0]->LoadBitmap(_T("Resource\\BulletBlast.bmp"), RGB(255, 0, 255));
    m_pPictureBlast[1]->LoadBitmap(_T("Resource\\PlaneBlast.bmp"), RGB(0, 0, 0));

    for(int i = 0; i < 8; ++i)
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
        break;
    default:
        break;
    }
    return ppPic;
}
