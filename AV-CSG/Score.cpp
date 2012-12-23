#include "stdafx.h"
#include "Score.h"

int CScore::m_nScore = 0;

CScore::CScore(void)
{
}

CScore::~CScore(void)
{
}

void CScore::Reset()
{
    m_nScore = 0;
}

int CScore::GetScore()
{
    return m_nScore;
}

int CScore::AddScore( int nValue /*= 1*/ )
{
    m_nScore += nValue;
    if (m_nScore > SCORE_MAX || m_nScore < 0)
    {
        ::MessageBox(0, L"分数不正常，游戏无法承受！", L"", 0);
        exit(0);
    }
    return m_nScore;
}

int CScore::SubScore( int nValue /*= 1*/ )
{
    m_nScore -= nValue;
    if (m_nScore > SCORE_MAX || m_nScore < 0)
    {
        ::MessageBox(0, L"分数不正常，游戏无法承受！", L"", 0);
        exit(0);
    }
    return m_nScore;
}

int GetNumX(int nScore, int i)
{
    switch (i)
    {
    case 0:
        return (nScore / 10000000) % 10;
        break;
    case 1:
        return (nScore / 1000000) % 10;
        break;
    case 2:
        return (nScore / 100000) % 10;
        break;
    case 3:
        return (nScore / 10000) % 10;
        break;
    case 4:
        return (nScore / 1000) % 10;
        break;
    case 5:
        return (nScore / 100) % 10;
        break;
    case 6:
        return (nScore / 10) % 10;
        break;
    case 7:
        return nScore % 10;
        break;
    default:
        break;
    }
    return 0;
}
