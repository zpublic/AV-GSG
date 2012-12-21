#pragma once

#include "Picture.h"

class CPicturePool
{
public:
    CPicturePool(void);
    ~CPicturePool(void);

    static void FreeImage();

    static void LoadImage();

    static CPicture** GetExplosionPic();
private:
    static CPicture* pPictureBlast[2];
};

