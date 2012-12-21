#include "StdAfx.h"
#include "Sprite.h"

CSprite * CSprite::pHead = NULL;

CSprite::CSprite(int x, int y):
		m_nPosX(x),
		m_nPosY(y),
		m_bIsVisible(true)
{
	this->pNext = pHead;
	pHead = this;
}


CSprite::~CSprite(void)
{
	//精灵从画面上删除时，需要更新链表
	//当删除的精灵是表头精灵时
	if (pHead == this)
	{
		pHead = pNext;
		return;
	}
	//当删除的精灵不是表头精灵时
	CSprite *pTemp = pHead;
	for (;pTemp->pNext != NULL; pTemp = pTemp->pNext)
	{
		if (pTemp->pNext == this)
		{
			pTemp->pNext = this->pNext;
			return;
		}
	}
}

bool CSprite::IsVisible()
{
	if(false == m_bIsVisible)
	{
		return m_bIsVisible;
	}
	//超出可见区域
	if(m_nPosX < - m_nWidth		||
	   m_nPosY < - m_nHeight	||
	   m_nPosX > SCREEN_WIDTH	||
	   m_nPosY > SCREEN_HEIGHT)
	{
		return false;
	}

	return true;
}

void CSprite::FrameRender(HDC hDC)
{
	CSprite* pTemp = pHead;
	for(;pTemp!=NULL;pTemp=pTemp->pNext)
	{
		pTemp->Render(hDC);
	}
}

void CSprite::FrameUpdate()
{
	//循环更新链上每一个图形
	CSprite *pTemp = pHead;
	for (;pTemp != NULL;)
	{
		if (!pTemp->IsVisible())
		{
			//不可见则删除，并更新链表
			CSprite *p = pTemp;
			p = p->pNext;
			delete pTemp;
			pTemp = p;
		} 
		else
		{
			pTemp->Update();
			pTemp = pTemp->pNext;
		}
	}
}