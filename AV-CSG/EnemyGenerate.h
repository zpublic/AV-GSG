#pragma once

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static void CreateEnemy();

    static int GetEnemyCount();
    static void AddEnemyCount(int nNum = 1);
    static void SubEnemyCount(int nNum = 1);

private:
    static float m_sfLastCreateTime;
    static int m_snEnemyCount;
};

