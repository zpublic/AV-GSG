#pragma once

#include "Picture.h"
#include "PlaneXMLParse.h"
#include <map>

class CPicturePool
{
public:
    CPicture* GetPicture(int picID) const;
    void FreeImage();

    static CPicturePool * GetInstance();

private:
    std::map<int, CPicture*> m_mapPic;

    static CPicturePool* m_pPicturePool;

    CPicturePool(void);
    ~CPicturePool(void);

    void LoadImage();

public:
    CPicture*            pPicturePlane;      //�ɻ�ͼƬ
    CPicture*            pPictureLife;       //����ͼƬ
    CPicture*            pPictureHP;
    CPicture*            pPictureHPSide;
    CPicture*            pPictureNum;
};

