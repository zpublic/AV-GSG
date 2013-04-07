#include "StdAfx.h"
#include "Sprite.h"

CSpriteBase::CSpriteBase(int x, int y):
    m_nPosX(x),
    m_nPosY(y),
    m_bIsVisible(true)
{
    m_nFrameStartX      = 0;
    m_nCurrentFrame     = 0;
    m_nWidth            = 0;
    m_nHeight           = 0;
    m_nFrameCount       = 0;
}

CSpriteBase::~CSpriteBase(void)
{
    //����ӻ�����ɾ��ʱ����Ҫ��������
    //��ɾ���ľ����Ǳ�ͷ����ʱ
    if (g_pHead == static_cast<ISprite *>(this))
    {
        g_pHead = pNext;
        return;
    }
    //��ɾ���ľ��鲻�Ǳ�ͷ����ʱ
    ISprite* pTemp = g_pHead;
    for ( ; pTemp->pNext != NULL; pTemp = pTemp->pNext )
    {
        if (pTemp->pNext == static_cast<ISprite *>(this))
        {
            pTemp->pNext = this->pNext;
            return;
        }
    }
}

bool CSpriteBase::IsVisible()
{
    if(false == m_bIsVisible)
    {
        return m_bIsVisible;
    }
    //�����ɼ�����
    if(m_nPosX < - m_nWidth     ||
        m_nPosY < - m_nHeight   ||
        m_nPosX > SCREEN_WIDTH  ||
        m_nPosY > SCREEN_HEIGHT)
    {
        return false;
    }

    return true;
}
