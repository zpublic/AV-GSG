#include "StdAfx.h"
#include "PrincipalPlane.h"
#include "GameControler.h"
#include <math.h>
#include "Bullet.h"
#include "EnemyPlane.h"
#include "BigBullet.h"

CPrincipalPlane * CPrincipalPlane::pCPrincipalPlane = NULL;
CPicture * CPrincipalPlane::pPictureLife = NULL;
CPicture * CPrincipalPlane::pPicturePlane = NULL;
CPicture * CPrincipalPlane::pPictureHP = NULL;
CPicture * CPrincipalPlane::pPictureHPSide = NULL;
GameStatus CPrincipalPlane::m_emGameStatus = emGameStatusReady;

CPrincipalPlane * CPrincipalPlane::GetInstance()
{
    if (NULL == pCPrincipalPlane)
    {
        pCPrincipalPlane = new CPrincipalPlane(SCREEN_WIDTH/2 - 24, 350);
    }
    return pCPrincipalPlane;
}

CPrincipalPlane::CPrincipalPlane(int x, int y)
    : PlaneBase(x, y)
{
    m_nLife = 1;
    m_nAmmoCount = 3;
    m_nBulletType = emBulletTypeAMMO0;
    m_nAction = STOP_MOVE;
    m_nWidth = 49;
    m_nHeight = 66;
    m_nSpeed = 350;
    InitPlane();
}

void CPrincipalPlane::InitPlane()
{
    m_bIsStopMove = true;
    m_nHP = 100;	
    m_nPosX = SCREEN_WIDTH/2 - 24;
    m_nPosY = 480;
    m_fBulletFrequency = 0.2f;//每秒发射5次子弹
    m_fFrequencyTime = 0.0f;
    m_fInvincibletime = 1.0;
    m_bUnDead = true;
    m_bFire = false;
    m_nWholeFired = 2;
}

CPrincipalPlane::~CPrincipalPlane()
{
}

void CPrincipalPlane::LoadBimap()
{
    pPicturePlane = new CPicture();
    pPictureLife = new CPicture();
    pPictureHP = new CPicture();
    pPictureHPSide = new CPicture();

    pPicturePlane->LoadBitmap(_T("Resource\\OurFighter.bmp"), RGB(0, 255, 0));
    pPictureLife->LoadBitmap(_T("Resource\\Life.bmp"), RGB(255, 0, 255));

    pPictureHP->LoadBitmap(_T("Resource\\HPBar.bmp"), RGB(255, 0, 255));
    pPictureHPSide->LoadBitmap(_T("Resource\\HPBarSide.bmp"), RGB(255, 0, 255));
}

void CPrincipalPlane::FreeBitmap()
{
    pPicturePlane->FreeBitmap();
    pPictureLife->FreeBitmap();
    pPictureHP->FreeBitmap();
    pPictureHPSide->FreeBitmap();
}

void CPrincipalPlane::Update()
{
    float tD = CGameControler::GetInstance()->GetElapsedTime();
    float fDis = tD * m_nSpeed;

    if (m_bUnDead)
    {
        if (m_bIsStopMove && (m_nPosY > 2 * SCREEN_HEIGHT / 3))
        {
            m_nPosY -= (int)fDis;
        }

        m_fInvincibletime -= tD;
        if (m_fInvincibletime <= 0)
        {
            m_bUnDead = false;
            m_fInvincibletime = 1.0;
        }
    }
    m_fFrequencyTime +=tD;

    if (!m_bIsStopMove)
    {
        m_nPosX += int(cos(m_fAngle) * fDis);
        m_nPosY += int(sin(m_fAngle) * fDis);
        if(m_nPosX < 0.0f)
            m_nPosX = 0;
        if(m_nPosY < 0.0f)
            m_nPosY = 0;
        if(m_nPosX>SCREEN_WIDTH-m_nWidth)
            m_nPosX = SCREEN_WIDTH-m_nWidth;
        if(m_nPosY>SCREEN_HEIGHT-m_nHeight)
            m_nPosY = SCREEN_HEIGHT-m_nHeight;
    }

    if (m_bFire && m_fFrequencyTime >= m_fBulletFrequency)
    {
        switch(m_nAmmoCount)
        {
        case 1:
            new CBullet(
                m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(PI * 3.0 / 2.0));
            break;
        case 3:
            new CBullet(
                m_nPosX + m_nWidth / 2 - 16, m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(17.0*PI/12.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(3.0*PI/2.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 , m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(8.0*PI/5.0));
            break;
        case 5:
            new CBullet(
                m_nPosX + m_nWidth / 2 - 16, m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(0*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(1*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 , m_nPosY - 16,
                true, 3, 10,
                m_nBulletType, float(2*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16,
                true, 3, 5,
                m_nBulletType, float(3*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 3 , m_nPosY - 16,
                true, 3, 5,
                m_nBulletType, float(4*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16,
                true, 3, 5,
                m_nBulletType, float(5*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 3 , m_nPosY - 16,
                true, 3, 5,
                m_nBulletType, float(6*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16,
                true, 3, 5,
                m_nBulletType, float(7*PI/4.0));
            new CBullet(
                m_nPosX + m_nWidth / 3 , m_nPosY - 16,
                true, 3, 5,
                m_nBulletType, float(8*PI/4.0));
            break;
        }

        while(m_fFrequencyTime > m_fBulletFrequency)
        {
            m_fFrequencyTime -= m_fBulletFrequency;
        }
    }	
}

void CPrincipalPlane::Control(ActionType actionType)
{
    m_nAction = actionType;
    switch(actionType)
    {
    case LEFT:
        m_fAngle = PI;
        m_bIsStopMove = false;
        break;
    case RIGHT:
        m_fAngle = 0.0f;
        m_bIsStopMove = false;
        break;
    case UP:
        m_fAngle = 3.0f * PI / 2.0f;
        m_bIsStopMove = false;
        break;
    case DOWN:
        m_fAngle = PI / 2.0f;
        m_bIsStopMove = false;
        break;
    case LEFT_UP:
        m_fAngle = 5.0f * PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case LEFT_DOWN:
        m_fAngle = 3.0f * PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case RIGHT_UP:
        m_fAngle = 2.0f * PI - PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case RIGHT_DOWN:
        m_fAngle = PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case STOP_MOVE:
        m_bIsStopMove = true;
        break;
    case FIRE:	
        m_bFire = true;	
        break;
    case STOP_FIRE:
        m_bFire = false;
        break;
    case FIREALL:
        if (m_nWholeFired && GetGameRuning())
        {
            new CBigBullet(0, SCREEN_HEIGHT / 2 - 320 /2, emBulletTypeAmmoAll1, 0.0);
            new CBigBullet(SCREEN_WIDTH/2 - 224 /2, SCREEN_HEIGHT / 2 - 320 /2, emBulletTypeAmmoAll1, 0.0);
            new CBigBullet(SCREEN_WIDTH - 224, SCREEN_HEIGHT / 2 - 320 /2, emBulletTypeAmmoAll1, 0.0);
            CEnemyPlane* temp = CEnemyPlane::spEnemyHead;
            for(;temp!=NULL;temp=temp->m_pEmnemyNext)
            {
                temp->CheckCollision(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 100);
            }
            m_nWholeFired--;
        }
        break;
    }

}

void CPrincipalPlane::Render(HDC hDC)
{
    pPicturePlane->DrawBitmap(hDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight,
        0, 0);
    for (int i = 0; i < m_nLife; ++i)
    {
        pPictureLife->DrawBitmap(hDC, 25 + i * 18, 10 , 18, 24,0, 0);
    }

    pPictureHPSide->DrawBitmap(hDC, 20 , 40 , 105, 13,0, 0);

    pPictureHP->DrawBitmap(hDC, 22 , 42 , m_nHP, 9,0, 0);
}

bool CPrincipalPlane::CheckCollision(int x, int y, int width, int height, int power)
{
    //碰撞检测简单的用区域相交来计算
    //在网上找到一个算法
    /*
    判断两个矩形的中心坐标的水平和垂直距离，只要这两个值满足某种条件就可以相交。
    矩形A的宽 Wa = Xa2-Xa1 高 Ha = Ya2-Ya1
    矩形B的宽 Wb = Xb2-Xb1 高 Hb = Yb2-Yb1
    矩形A的中心坐标 (Xa3,Ya3) = （ (Xa2+Xa1)/2 ，(Ya2+Ya1)/2 ）
    矩形B的中心坐标 (Xb3,Yb3) = （ (Xb2+Xb1)/2 ，(Yb2+Yb1)/2 ）
    所以只要同时满足下面两个式子，就可以说明两个矩形相交。

    1） | Xb3-Xa3 | <= Wa/2 + Wb/2 
    2） | Yb3-Ya3 | <= Ha/2 + Hb/2

    即：
    | Xb2+Xb1-Xa2-Xa1 | <= Xa2-Xa1 + Xb2-Xb1
    | Yb2+Yb1-Ya2-Ya1 | <=Y a2-Ya1 + Yb2-Yb1

    */

    if (m_bUnDead)
    {
        return false;
    }

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
            m_nLife--;
            if (m_nLife >= 0)
            {
                //new blast
                InitPlane();
            }
            else
            {
                m_emGameStatus = emGameStatusOver;
            }
        }
        return true;
    }
    return false; 
}
