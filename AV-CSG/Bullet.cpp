#include "StdAfx.h"
#include "Bullet.h"
#include "SelfPlane.h"
#include "EnemyPlane.h"
#include "Explosion.h"
#include "control\generate\EnemyGenerate.h"

#include <string>

CBullet::CBullet(int x, int y,
                 bool bFriend,
                 BulletType bulletType,
                 float fAngle)
    : CSprite(x, y)
    , m_BulletType(bulletType)
{
    m_bFriend = bFriend;
    m_fAngle = fAngle;
    m_Bullet = CBulletXMLParse::GetInstance().Get(bulletType);
    if (m_Bullet == NULL)
    {
        return;
    }
    m_nSpeed = m_Bullet->GetSpeed();
    m_nPower = m_Bullet->GetPower();
    m_nWidth = m_Bullet->GetWidth();
    m_nHeight = m_Bullet->GetHeight();
    m_nFrameCount = m_Bullet->GetFrameCount();
}

CBullet::~CBullet(void)
{

}

bool CBullet::IsVisible()
{
    if(m_bIsVisible == false)
    {
        return m_bIsVisible;
    }
    if (m_nPosX < -50               ||
        m_nPosY < -50               ||
        m_nPosX > SCREEN_WIDTH + 50 ||
        m_nPosY > SCREEN_HEIGHT + 50)
    {
        return false;
    }
    return true;
}

void CBullet::Render(HDC hDC)
{
    if (!CPicturePool::GetInstance()->GetPicture(m_Bullet->GetSkinId()))
    {
        return;
    }
    CPicturePool::GetInstance()->GetPicture(m_Bullet->GetSkinId())->DrawBitmap(
        hDC,
        m_nPosX, m_nPosY,
        m_nWidth, m_nHeight,
        m_nFrameStartX, 0);
}

void CBullet::Update()
{
    float fDis = ElapsedTime * m_nSpeed;
    m_nPosX += int(cos(m_fAngle) * fDis);
    m_nPosY += int(sin(m_fAngle) * fDis);

    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    ++m_nCurrentFrame;
    m_nCurrentFrame %= m_nFrameCount;

    if (m_bFriend)
    {
        CEnemyPlane* temp = CEnemyGenerate::spEnemyHead;
        for( ; temp!=NULL; temp=temp->m_pEmnemyNext )
        {
            if(temp->CheckCollision(m_nPosX, m_nPosY, m_nWidth, m_nHeight, m_nPower))
            {
                m_bIsVisible = false;
                new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, "emBlastTypeBullet");
                break;
            }
        }
    }
    else
    {
        if (CSelfPlane::GetInstance()->CheckCollision(
            m_nPosX, m_nPosY,
            m_nWidth, m_nHeight,
            m_nPower))
        {
            m_bIsVisible = false;
            new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, "emBlastTypeBullet");
        }
    }
}