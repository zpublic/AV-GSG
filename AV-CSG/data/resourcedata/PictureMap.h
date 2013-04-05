#pragma once

typedef struct _PictureNode
{
    _PictureNode() : strPath(L"")
    {
        r = 0;
        g = 0;
        b = 0;
        width = 0;
        height = 0;
    }

    std::wstring strPath;
    int r,g,b;
    int width;
    int height;
}PictureNode;

///> ͼƬ��Դxml����
class CPictureMap
{
public:
    CPictureMap(void);
    ~CPictureMap(void);

    bool LoadXml(LPCWSTR lpFilePath, std::map<std::string, PictureNode>& mapPicture);

private:
    void GetPictureNode( TiXmlElement* pElement, std::map<std::string, PictureNode>& mapPicture );
};

