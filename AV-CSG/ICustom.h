#ifndef _CUSTOM_I
#define _CUSTOM_I

#include <string>
#include <vector>
#include <tchar.h>
#include "EnemyPlane.h"

using std::string;
using std::vector;

typedef std::vector<std::pair<CEnemyPlane*, int> > EnemyList;
typedef std::basic_string<TCHAR> TString;

class ICustom
{
public:
    ICustom() {}
    virtual ~ICustom() {}
    virtual void SetName(const TString& strName) = 0;
    virtual const TString& GetName() = 0;
    virtual void SetCustomId(int strName) = 0;
    virtual int GetCustomId() = 0;

    virtual void SetEnemyBoss(const CEnemyPlane& epBoss) = 0;
    virtual const CEnemyPlane& GetEnemyBoss() = 0;
    virtual void SetEnemy(const EnemyList& vecEnemyList) = 0;
    virtual EnemyList::const_iterator EnemyBegin() = 0;
    virtual EnemyList::const_iterator EnemyEnd() = 0;

    virtual void MapBackgroud(const TString& lpszPath) = 0;

    virtual bool IsBoss() = 0;
};

#endif