#ifndef EASYCUSTOM_C
#define EASYCUSTOM_C

#include "ICustom.h"

class CEasyCustom : public ICustom
{
public:
    CEasyCustom();
    virtual ~CEasyCustom();

    virtual void SetName(const TString& strName);
    virtual const TString& GetName() const;
    virtual void SetCustomId(int strName);
    virtual int GetCustomId() const;

    virtual void SetEnemyBoss(const CEnemyPlane& epBoss);
    virtual const CEnemyPlane& GetEnemyBoss() const;
    virtual void SetEnemy(const EnemyList& vecEnemyList);
    virtual EnemyList::const_iterator EnemyBegin() const;
    virtual EnemyList::const_iterator EnemyEnd() const;

    virtual void MapBackgroud(const TString& lpszPath);

    virtual bool IsBoss() const;

private:
    TString m_strPath;
    TString m_Name;
    int m_Id;
    CEnemyPlane* m_BossPlane_Ptr;
    EnemyList m_vecEnemyList;
    bool m_IsBoss;
};

#endif