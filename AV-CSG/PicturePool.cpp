#include "stdafx.h"
#include "PicturePool.h"

CPicture * CPicturePool::pPictureBlast[2] = {0};

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
        pPictureBlast[i]->FreeBitmap();
    }
}

void CPicturePool::LoadImage()
{
    for (int i = 0; i < 2; ++i)
    {
        pPictureBlast[i] = new CPicture();
    }

    pPictureBlast[0]->LoadBitmap(_T("Resource\\BulletBlast.bmp"), RGB(255, 0, 255));
    pPictureBlast[1]->LoadBitmap(_T("Resource\\PlaneBlast.bmp"), RGB(0, 0, 0));
}

CPicture** CPicturePool::GetExplosionPic()
{
    return (CPicture**)&pPictureBlast;
}
