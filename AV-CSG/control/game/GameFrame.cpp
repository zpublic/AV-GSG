#include "stdafx.h"
#include "GameFrame.h"
#include "ISprite.h"

ISprite * g_pHead = NULL;

void FrameRender(HDC hDC)
{
    ISprite* pTemp = g_pHead;
    for( ; pTemp!=NULL; pTemp=pTemp->pNext )
    {
        pTemp->Render(hDC);
    }
}

void FrameUpdate()
{
    //循环更新链上每一个图形
    ISprite *pTemp = g_pHead;
    for ( ; pTemp != NULL; )
    {
        if (!pTemp->IsVisible())
        {
            //不可见则删除，并更新链表
            ISprite *pNext = pTemp->pNext;
            delete pTemp;
            pTemp = pNext;
        }
        else
        {
            pTemp->Update();
            pTemp = pTemp->pNext;
        }
    }
}
