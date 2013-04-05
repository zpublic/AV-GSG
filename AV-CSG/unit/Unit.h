#pragma once
namespace Unit
{
    int GetNumX(int nScore, int i);
    float CalcAngle(int nPosX, int nPosY, int x, int y);

    BOOL GetXmlStrAttributeW( TiXmlElement *pElement, char *pName, std::wstring &strData );
    BOOL GetXmlStrAttributeA( TiXmlElement *pElement, char *pName, std::string &strData );
    BOOL GetXmlIntAttribute( TiXmlElement *pElement, char *pName, int &nData );

    void GetPath(std::string& strPath);
}
