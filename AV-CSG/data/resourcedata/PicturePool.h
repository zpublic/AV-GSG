#pragma once

#include "Picture.h"
#include <map>

class CPicturePool
{
public:
    CPicture* GetPicture(const std::string& picID) const;
    void FreeImage();

    static CPicturePool * GetInstance();

    void LoadImage(LPCWSTR lpFilePath);

private:
    std::map<std::string, CPicture*> m_mapPic;

    static CPicturePool* m_pPicturePool;

    CPicturePool(void);
    ~CPicturePool(void);
};

