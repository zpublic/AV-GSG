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

