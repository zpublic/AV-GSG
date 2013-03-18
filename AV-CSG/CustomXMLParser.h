#ifndef CUSTOM_PARSERXML_
#define CUSTOM_PARSERXML_

#include "tinyxml-2.6.2\tinyxml.h"
#include "ICustom.h"

typedef struct _PosObject
{
    _PosObject() : PosX(0), PosY(0) {}
    //_PosObject(int iPosX = 0, int iPosY = 0) : PosX(iPosX), PosY(iPosY) {}
    void SetPoint(int iPosX = 0, int iPosY = 0)
    {
        PosX = iPosX;
        PosY = iPosY;
    }

public:
    int PosX;
    int PosY;
}PosObject;

class CCustomXMLOBject
{
public:
    CCustomXMLOBject();
    virtual ~CCustomXMLOBject();

    virtual void SetName(const TString& strName);
    virtual const TString& GetName() const;
    virtual void SetId(int nId);
    virtual int GetId() const;

    virtual void SetType(int nType);
    virtual int GetType() const;

    virtual void SetPoint(int iPosX = 0, int iPosY = 0);
    virtual void SetPoint(const PosObject& pos);
    virtual const PosObject& GetPoint() const;

private:
    TString m_Name;
    int m_Id;
    int m_Type;
    PosObject m_Pos;
};

class CCustomXMLItem : public CCustomXMLOBject
{

};

class CCustomXMLEnemy : public CCustomXMLOBject
{

};

class CCustomXMLParse
{
public:
    ~CCustomXMLParse();

    static CCustomXMLParse& Initialize();
    bool LoadXML(const TString& strPath);

private:

    bool _Parse(TiXmlDocument& TinyXML);

private:
    CCustomXMLParse();
    CCustomXMLParse(CCustomXMLParse&);
    CCustomXMLParse& operator = (CCustomXMLParse&);

    static CCustomXMLParse m_XMLParse;
};

CCustomXMLParse CCustomXMLParse::m_XMLParse;

#endif