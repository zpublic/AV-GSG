#pragma once

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static void CreateEnemy();

    static int GetEnemyCount() { return m_snEnemyCount; }
    static void AddEnemyCount(int nNum = 1) { m_snEnemyCount += nNum; }
    static void SubEnemyCount(int nNum = 1) { m_snEnemyCount -= nNum; }

private:
    static float m_sfLastCreateTime;
    static int m_snEnemyCount;
};

