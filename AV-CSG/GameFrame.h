#pragma once
#include "ISprite.h"

class CGameFrame
{
public:
    CGameFrame(void);
    ~CGameFrame(void);

    //刷新一帧画面
    static void FrameRender(HDC hDC);

    //统一更新帧数据
    static void FrameUpdate();
};

