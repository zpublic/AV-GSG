#ifndef ITEM_OBJECT
#define ITEM_OBJECT

#include "XMLObject.h"

class CStageXMLItem : public CXMLObject
{
public:
    CStageXMLItem(const std::string& strWay);
    virtual ~CStageXMLItem();

    virtual const std::string& Way();

    virtual void SetNumber(long lnNumber);
    virtual long GetNumber() const;

    virtual void SetPoint(int iPosX = 0, int iPosY = 0);
    virtual void SetPoint(const PosObject& pos);
    virtual const PosObject& GetPoint() const;

private:
    CStageXMLItem();
private:
    long m_Number;
    std::string m_Way;
    PosObject m_Point;
};

#endif