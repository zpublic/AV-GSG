#include "stdafx.h"
#include "GameFrame.h"
#include "gameobject\sprite\ISprite.h"

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
    //ѭ����������ÿһ��ͼ��
    ISprite *pTemp = g_pHead;
    for ( ; pTemp != NULL; )
    {
        if (!pTemp->IsVisible())
        {
            //���ɼ���ɾ��������������
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
