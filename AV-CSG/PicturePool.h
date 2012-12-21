#pragma once

#include "Picture.h"

class CPicturePool
{
public:
    CPicturePool(void);
    ~CPicturePool(void);

    static void FreeImage();
    static void LoadImage();

    static CPicture** GetPicture(PictureType picType);

private:
    static CPicture* m_pPictureBlast[emBlastTypeMax];
    static CPicture* m_pPictureAmmo[emBulletTypeMax];
    static CPicture* m_pPictureEnemy[emEnemyTypeMax];
};

