#pragma once
class Unit
{
public:
    Unit(void);
    ~Unit(void);
    static int GetNumX(int nScore, int i);
    static float CalcAngle(int nPosX, int nPosY, int x, int y);
    static BOOL GetXmlStrAttributeW( TiXmlElement *pElement, char *pName, std::wstring &strData );
    static BOOL GetXmlStrAttributeA( TiXmlElement *pElement, char *pName, std::string &strData );
    static BOOL GetXmlIntAttribute( TiXmlElement *pElement, char *pName, int &nData );
};

