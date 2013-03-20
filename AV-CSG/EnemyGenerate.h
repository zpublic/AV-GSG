#pragma once

class CEnemyPlane;

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static void CreateEnemy();
    static void ReleaseEnemy(CEnemyPlane* pEnemy);

public:
    static CEnemyPlane *spEnemyHead;

private:
    static long m_Schedule;
};

