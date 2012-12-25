#pragma once

typedef struct _PictureNode
{
    _PictureNode() : strPath(L"")
    {
        r = 0;
        g = 0;
        b = 0;
    }

    std::wstring strPath;
    BYTE r,g,b;
}PictureNode;

///> Õº∆¨◊ ‘¥xmlº”‘ÿ
class CPictureMap
{
public:
    CPictureMap(void);
    ~CPictureMap(void);

    BOOL LoadXml(LPCWSTR lpFilePath, std::map<int, PictureNode>& m_mapPicture);
};

