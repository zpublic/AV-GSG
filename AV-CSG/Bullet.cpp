#include "StdAfx.h"
#include "Bullet.h"

CPicture * CBullet::m_pPictureAmmo[8] = {0};

CBullet::CBullet(int x, int y):CSprite(x, y)
{
}


CBullet::~CBullet(void)
{
	
}

void CBullet::FreeBullet()
{
	for(int i = 0; i < 8; ++i)
	{
		m_pPictureAmmo[i]->FreeBitmap();
	}
}

void CBullet::LoadBullet()
{
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
