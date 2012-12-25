#pragma once

#include "Picture.h"

class CPicturePool
{
public:
    CPicture** GetPicture(PictureType picType);
    void FreeImage();

    static CPicturePool * GetInstance();

private:
    CPicture* m_pPictureBlast[emBlastTypeMax];
    CPicture* m_pPictureAmmo[emBulletTypeMax];
    CPicture* m_pPictureEnemy[emEnemyTypeMax];

    std::map<int, CPicture*> m_mapPic;

    static CPicturePool* m_pPicturePool;

    CPicturePool(void);
    ~CPicturePool(void);

    void LoadImage();

public:
    CPicture*            pPicturePlane;      //·É»úÍ¼Æ¬
    CPicture*            pPictureLife;       //ÉúÃüÍ¼Æ¬
    CPicture*            pPictureHP;
    CPicture*            pPictureHPSide;
    CPicture*            pPictureNum;
};

