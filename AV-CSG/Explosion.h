#pragma once

#include "Sprite.h"
#include "Picture.h"

// 爆炸效果类，主要是根据给定的坐标和类型，显示爆炸的效果就可。
class CExplosion : CSprite
{
public:
    CExplosion(int x, int y, BlastType blastType);
    virtual ~CExplosion(void);
    static void LoadImage();
    static void FreeImage();

    void Update();
    void Render(HDC hDC);
private:
    static CPicture *pPictureBlast[2];
    BlastType m_emBlastType;
};
