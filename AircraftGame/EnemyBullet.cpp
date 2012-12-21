#include "StdAfx.h"
#include "EnemyBullet.h"
#include <math.h>
#include "GameControler.h"
#include "PrincipalPlane.h"
#include "Explosion.h"


CEnemyBullet::CEnemyBullet(int x, int y, BulletType bulletType, float angle):CBullet(x, y)
{
	m_nSpeed = 220;
	m_nBulletType = bulletType;
	m_fAngle = angle;
	m_nCurrentFrame = 0;
	m_nFrameStartX = 0;
	m_nPower = 5;
	switch(bulletType)
	{
	case AMMO0:
		m_nWidth = 16;
		m_nHeight = 16;
		m_nFrameCount = 8;
		break;
	case AMMO1:
		m_nWidth = 16;
		m_nHeight = 16;
		m_nFrameCount = 6;
		break;
	case AMMO2:
		m_nWidth = 11;
		m_nHeight = 11;
		m_nFrameCount = 1;
		break;
	case AMMO3:
		m_nWidth = 16;
		m_nHeight = 16;
		m_nFrameCount = 6;
		break;
	case AMMO4:
		m_nWidth = 12;
		m_nHeight = 60;
		m_nFrameCount = 5;
		break;
	case AMMO5:
		m_nWidth = 23;
		m_nHeight = 49;
		m_nFrameCount = 1;
		break;
	}
}


CEnemyBullet::~CEnemyBullet(void)
{
}

bool CEnemyBullet::IsVisible()
{
	if(m_bIsVisible==false)
	{
		return m_bIsVisible;
	}
	if(m_nPosX < -50	||
		m_nPosY < -50	||
		m_nPosX > SCREEN_WIDTH+50	||
		m_nPosY > SCREEN_HEIGHT+50)
	{
		return false;
	}
	return true;
}

void CEnemyBullet::Render(HDC hDC)
{
	m_pPictureAmmo[m_nBulletType]->DrawBitmap(hDC, m_nPosX, m_nPosY,
		m_nWidth, m_nHeight, m_nFrameStartX, 0);
}

void CEnemyBullet::Update()
{
	float tD = CGameControler::GetInstance()->GetElapsedTime();
	float fDis = tD * m_nSpeed;
	int nStartX = 0, nStartY = 0;

	m_nPosX += cos(m_fAngle) * fDis;
	m_nPosY += sin(m_fAngle) * fDis;

	m_nFrameStartX = m_nCurrentFrame * m_nWidth;
	++m_nCurrentFrame;
	m_nCurrentFrame %= m_nFrameCount;

	if (CPrincipalPlane::GetInstance()->CheckCollision(m_nPosX, m_nPosY,m_nWidth, m_nHeight, m_nPower))
	{
		m_bIsVisible = false;
		new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, BULLETBLAST);
	}
}