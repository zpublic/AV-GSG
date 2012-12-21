#include "stdafx.h"
#include "GameFrame.h"

ISprite * g_pHead = NULL;

CGameFrame::CGameFrame(void)
{
}


CGameFrame::~CGameFrame(void)
{
}

void CGameFrame::FrameRender(HDC hDC)
{
    ISprite* pTemp = g_pHead;
    for( ; pTemp!=NULL; pTemp=pTemp->pNext )
    {
        pTemp->Render(hDC);
    }
}

void CGameFrame::FrameUpdate()
{
    //循环更新链上每一个图形
    ISprite *pTemp = g_pHead;
    for ( ; pTemp != NULL; )
    {
        if (!pTemp->IsVisible())
        {
            //不可见则删除，并更新链表
            ISprite *p = pTemp;
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