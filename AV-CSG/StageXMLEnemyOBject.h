#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "XMLObject.h"
#include "StageXMLItemOBject.h"

typedef std::map<std::string, CStageXMLItem*> ItemObejctMap;

class CStageXMLEnemy : public CXMLObject
{
public:
    CStageXMLEnemy();
    virtual ~CStageXMLEnemy();

    bool PushItem(CStageXMLItem* sItemObject);
    const ItemObejctMap::const_iterator Begin() const;
    const ItemObejctMap::const_iterator End() const;

    virtual void SetPoint(int iPosX = 0, int iPosY = 0);
    virtual void SetPoint(const PosObject& pos);
    virtual const PosObject& GetPoint() const;

    bool SetItem(const std::string& strId,CStageXMLItem* sItemObject);
    const CStageXMLItem* GetItem(const std::string& strId) const;

    void SetAppear(long lnAppear);
    const long GetAppear() const;
    void SetBind(const std::string& strBind);
    const std::string& GetBind() const;

private:

    void _Close();

    long m_Appear;
    std::string m_Bind;
    ItemObejctMap m_mapItem;
    PosObject m_Point;
};

#endif