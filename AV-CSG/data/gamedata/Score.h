#pragma once

#define SCORE_MAX 99999999

///> �÷ּ���
class CScore
{
public:
    CScore(void);
    ~CScore(void);

    static void Reset();
    static int GetScore();
    static int AddScore(int nValue = 1);
    static int SubScore(int nValue = 1);

private:
    static int m_nScore;
};
