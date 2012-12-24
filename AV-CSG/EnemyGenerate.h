#pragma once

class CEnemyPlane;

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static void CreateEnemy();
    static void ReleaseEnemy(CEnemyPlane* pEnemy);

    static int GetEnemyCount();
    static void AddEnemyCount(int nNum = 1);
    static void SubEnemyCount(int nNum = 1);
public:
    static CEnemyPlane *spEnemyHead;

private:
    static float m_sfLastCreateTime;
    static int m_snEnemyCount;
};

