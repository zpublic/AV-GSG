#include "StdAfx.h"
#include "PrincipalPlane.h"
#include "GameControler.h"
#include "EnemyPlane.h"
#include "GameStatus.h"
#include "EmitterGenerate.h"
#include "Score.h"
#include "EnemyGenerate.h"

CPrincipalPlane * CPrincipalPlane::pCPrincipalPlane = NULL;

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
    InitGame();
}

CPrincipalPlane::~CPrincipalPlane()
{
}

void CPrincipalPlane::InitGame()
{
    m_nLifes = 2;
    SetBulletType(emBulletTypeAMMO0);
    m_nAction = STOP_MOVE;
    m_nWidth = 20;
    m_nHeight = 26;
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
        m_piEmitter->Emit(m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16, m_nBulletType);

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
        if (m_nWholeFired && CGameStatus::GetGameRuning())
        {
            IEmitter* iEmitter = CEmitterGenerate::Generate(5, true, 0, 0, 0);
            iEmitter->Emit(0, 0, emBulletTypeAmmoAll1);
            CEnemyPlane* temp = CEnemyGenerate::spEnemyHead;
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
    CPicturePool::pPicturePlane->DrawBitmap(
        hDC,
        m_nPosX, m_nPosY,
        m_nWidth, m_nHeight,
        0, 0);
    for (int i = 0; i < m_nLifes - 1; ++i)
    {
        CPicturePool::pPictureLife->DrawBitmap(hDC, 25 + i * 18, 10, 18, 24, 0, 0);
    }
    int nScore = CScore::GetScore();
    ///> 显示八位生命
    for (int i = 0; i < 8; ++i)
    {
        CPicturePool::pPictureNum->DrawBitmap(hDC, 440 + i * 16, 25, 16, 18, Unit::GetNumX(nScore, i) * 16, 0);
    }

    CPicturePool::pPictureHPSide->DrawBitmap(hDC, 20, 40, 105, 13, 0, 0);

    CPicturePool::pPictureHP->DrawBitmap(hDC, 22, 42, m_nHP, 9, 0, 0);
}

bool CPrincipalPlane::CheckCollision(int x, int y, int width, int height, int power)
{
    /*
    碰撞检测简单的用区域相交来计算
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
            m_nLifes--;
            if (m_nLifes > 0)
            {
                //new blast
                InitPlane();
            }
            else
            {
                CGameStatus::SetGameOver();
            }
        }
        return true;
    }
    return false;
}

void CPrincipalPlane::SetBulletType( BulletType bulletType )
{
    delete m_piEmitter;
    m_nBulletType = bulletType;
    if (m_nBulletType == emBulletTypeAMMO5 || m_nBulletType == emBulletTypeAMMO6)
    {
        m_piEmitter = CEmitterGenerate::Generate(
            2, true,
            3, 200, 0);
    }
    else if (m_nBulletType == emBulletTypeAmmoSB)
    {
        m_piEmitter = CEmitterGenerate::Generate(
            3, true,
            3, 200, 0);
    }
    else
    {
        m_piEmitter = CEmitterGenerate::Generate(
            1, true,
            3, 200, float(PI * 3 / 2.0));
    }
}