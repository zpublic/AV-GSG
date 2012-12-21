#include "StdAfx.h"
#include "Explosion.h"

CPicture * CExplosion::pPictureBlast[2] = {0};

CExplosion::CExplosion(int x, int y, BlastType blastType)
    : CSprite(x, y)
    , m_emBlastType(blastType)
{
    switch(blastType)
    {
    case BULLETBLAST:
        m_nWidth = 32;
        m_nHeight = 32;
        m_nFrameCount = 5;
        break;
    case PLANEBLAST:
        m_nWidth = 65;
        m_nHeight = 75;
        m_nFrameCount = 12;
        break;
    }
}

CExplosion::~CExplosion(void)
{

}

void CExplosion::FreeImage()
{
    for (int i = 0; i < 2; ++i)
    {
        pPictureBlast[i]->FreeBitmap();
    }
}

void CExplosion::LoadImage()
{
    for (int i = 0; i < 2; ++i)
    {
        pPictureBlast[i] = new CPicture();
    }

    pPictureBlast[0]->LoadBitmap(_T("Resource\\BulletBlast.bmp"), RGB(255, 0, 255));
    pPictureBlast[1]->LoadBitmap(_T("Resource\\PlaneBlast.bmp"), RGB(0, 0, 0));
}

void CExplosion::Update()
{
    if (m_nCurrentFrame >= m_nFrameCount)
    {
        m_bIsVisible = false;
    }
    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    m_nCurrentFrame++;
}

void CExplosion::Render(HDC hDC)
{
    pPictureBlast[m_emBlastType]->DrawBitmap(hDC, m_nPosX - m_nWidth/2, m_nPosY - m_nHeight / 2,
        m_nWidth, m_nHeight, m_nFrameStartX, 0);
}