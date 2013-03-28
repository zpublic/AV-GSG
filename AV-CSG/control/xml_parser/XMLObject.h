#ifndef PARSER_XML_OBJECT
#define PARSER_XML_OBJECT

#include <string>
#include <map>
#include <vector>

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

class CXMLObject
{
public:
    CXMLObject();
    virtual ~CXMLObject();

    virtual void SetName(const std::string& strName);
    virtual const std::string& GetName() const;
    virtual void SetId(const std::string& strId);
    virtual std::string GetId() const;

    virtual void SetType(const std::string& strType);
    virtual const std::string& GetType() const;

private:
    std::string m_Name;
    std::string m_Id;
    std::string m_Type;
};

#endif