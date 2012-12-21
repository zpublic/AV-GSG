#include "StdAfx.h"
#include "EnemyPlane.h"
#include "GameControler.h"
#include "EnemyBullet.h"
#include "PrincipalPlane.h"
#include "Explosion.h"


CPicture * CEnemyPlane::spPictureEnemy[6] = {0};
float CEnemyPlane::sfLastCreateTime = 0.0;
int CEnemyPlane::snEnemyCount = 0;
CEnemyPlane * CEnemyPlane::spEnemyHead = NULL;

CEnemyPlane::CEnemyPlane(EnemyType enemyType):CSprite(0, 0),
	m_nEnemyType(enemyType)
{
	int nRandom = rand() % 5;//随机随0-2产生的飞机从屏幕上方左中右出现
							//5号特殊敌机从下方出现
	m_fFireTime = 1.0f;

	if (snEnemyCount < 10)
	{
		snEnemyCount++;
	}
	
	switch (m_nEnemyType)
	{
	case ENEMY0:
		m_nWidth = 43;
		m_nHeight = 36;
		m_nHP = 4;
		m_nSpeed = 150;
		break;
	case ENEMY1:
		m_nWidth = 76;
		m_nHeight = 94;
		m_nHP = 10;
		m_nSpeed = 100;
		break;
	case ENEMY2:
		m_nWidth = 93;
		m_nHeight = 85;
		m_nHP = 10;
		m_nSpeed = 90;
		break;
	case ENEMY3:
		m_nWidth = 100;
		m_nHeight = 47;
		m_nHP = 6;
		m_nSpeed = 80;
		break;
	case ENEMY4:
		m_nWidth = 45;
		m_nHeight = 43;
		m_nHP = 8;
		m_nSpeed = 100;
		break;
	}

	if (nRandom == 0)
	{
		m_nPosX = 0;
	}
	else
	{
		m_nPosX = nRandom * SCREEN_WIDTH/5 - m_nWidth / 2;
	}
	m_nPosY = -m_nHeight + 2; 

	m_pEmnemyNext = spEnemyHead;
	spEnemyHead  = this;
}


CEnemyPlane::~CEnemyPlane(void)
{
	snEnemyCount--;
	if (spEnemyHead == this)
	{
		spEnemyHead = this->m_pEmnemyNext;
	}
	else
	{
		CEnemyPlane* temp = spEnemyHead;
		for(;temp->m_pEmnemyNext!=NULL;temp=temp->m_pEmnemyNext)
		{
			if(temp->m_pEmnemyNext==this)
			{
				temp->m_pEmnemyNext = this->m_pEmnemyNext;
				return;
			}
		}
	}
}

void CEnemyPlane::CreateEnemy()
{
	float tD = CGameControler::GetInstance()->GetElapsedTime();
	sfLastCreateTime += tD;
	if (sfLastCreateTime > 0.3f)//0.5秒产生一架敌机
	{
		if (snEnemyCount < 10)
		{
			new CEnemyPlane((EnemyType)(snEnemyCount % 5));
		}
		sfLastCreateTime -= 0.5f;
	}
}

void CEnemyPlane::FreeBitmap()
{
	for(int i = 0; i < 6; ++i)
	{
		spPictureEnemy[i]->FreeBitmap();
	}
}

void CEnemyPlane::LoadBimap()
{
	for(int i = 0; i < 6; ++i)
	{
		spPictureEnemy[i] = new CPicture();
	}
	spPictureEnemy[0]->LoadBitmap(_T("Resource\\Enemy0.bmp"), RGB(255, 255, 255));
	spPictureEnemy[1]->LoadBitmap(_T("Resource\\Enemy1.bmp"), RGB(255, 255, 255));
	spPictureEnemy[2]->LoadBitmap(_T("Resource\\Enemy2.bmp"), RGB(255, 255, 255));
	spPictureEnemy[3]->LoadBitmap(_T("Resource\\Enemy3.bmp"), RGB(255, 0, 255));
	spPictureEnemy[4]->LoadBitmap(_T("Resource\\Enemy4.bmp"), RGB(255, 255, 255));
	spPictureEnemy[5]->LoadBitmap(_T("Resource\\Enemy5.bmp"), RGB(0, 0, 0));
}

bool CEnemyPlane::IsVisible()
{
	if(m_nPosX < - m_nWidth	||
	   m_nPosX > SCREEN_WIDTH + m_nWidth	||
	   m_nPosY < -m_nHeight	||
	   m_nPosY > SCREEN_HEIGHT + m_nHeight)
	{
		m_bIsVisible = false;
		return false;
	}
	return m_bIsVisible;
}

void CEnemyPlane::Update()
{
	float tD = CGameControler::GetInstance()->GetElapsedTime();
	float fDis = tD * m_nSpeed;

	m_nPosY += fDis;

	m_fFireTime -= tD;
	if (m_fFireTime <= 0.0f)
	{
		m_fFireTime = 1.0f;
		new CEnemyBullet(m_nPosX + m_nWidth / 2 - 8, m_nPosY + m_nHeight, (BulletType)(m_nEnemyType % 4), 17.0 * PI / 36.0);
	}

	if (CPrincipalPlane::GetInstance()->CheckCollision(m_nPosX, m_nPosY, m_nWidth, m_nHeight, 20))
	{
		m_bIsVisible = false;
		new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, PLANEBLAST);
		return;
	}
}

void CEnemyPlane::Render(HDC hDC)
{
	spPictureEnemy[m_nEnemyType]->DrawBitmap(hDC, m_nPosX, m_nPosY,
		m_nWidth, m_nHeight, m_nFrameStartX, 0);
}

bool CEnemyPlane::CheckCollision(int x, int y, int width, int height, int power)
{
	int Xa3 = m_nPosX + m_nWidth / 2;
	int Ya3 = m_nPosY + m_nHeight / 2;
	int Xb3 = x + width / 2;
	int Yb3 = y + height / 2;

	//由于图片的尺寸问题，稍微调整
	if ( (abs( Xb3 - Xa3 ) + m_nWidth / 5) <= (m_nWidth + width)/2 &&
		( abs( Yb3 - Ya3 ) + m_nHeight / 5) <= (m_nHeight + height)/2)
	{
		m_nHP -= power;
		if (m_nHP <= 0)
		{
			m_bIsVisible = false;
			new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, PLANEBLAST);
		}
		return true;
	}
	return false;
}