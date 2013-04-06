#include "stdafx.h"
#include "player_gamestatus.h"

Player_GameStatus::Player_GameStatus()
    : m_nMaxScore(0)
    , m_nLife(Default_Life)
    , m_HP(0)
    , m_nScroe(0)
{
    memset(&m_ScoreList, 0, sizeof(m_ScoreList));
}

Player_GameStatus::~Player_GameStatus()
{
}

int Player_GameStatus::GetMaxScore()
{
    return m_nMaxScore;
}

bool Player_GameStatus::SetMaxScore(int nMaxScore)
{
    if(nMaxScore <= 0 || nMaxScore < m_nMaxScore)
    {
        return false;
    }
    m_nMaxScore = nMaxScore;
    return true;
}

int Player_GameStatus::GetLife()
{
    return m_nLife;
}

int Player_GameStatus::AddLife( int nAdd /*= 1*/ )
{
    m_nLife += nAdd;
    return m_nLife;
}

int Player_GameStatus::SubLife( int nSub /*= 1*/ )
{
    m_nLife -= nSub;
    if (m_nLife < 0)
    {
        m_nLife = 0;
    }
    return m_nLife;
}

int Player_GameStatus::GetHp()
{
    return m_HP;
}

void Player_GameStatus::SetHp( int nHp )
{
    m_nLife = nHp;
}

int Player_GameStatus::AddHp( int nAdd )
{
    m_HP += nAdd;
    return m_HP;
}

int Player_GameStatus::SubHp( int nSub )
{
    m_HP -= nSub;
    if (m_HP < 0)
    {
        m_HP = 0;
        assert(false);
    }
    return m_HP;
}

int Player_GameStatus::GetScore()
{
    return m_nScroe;
}

int Player_GameStatus::AddScore( int nAdd )
{
    m_nScroe += nAdd;
    return m_nScroe;
}

int Player_GameStatus::SubScore( int nSub )
{
    m_nScroe -= nSub;
    if (m_nScroe < 0)
    {
        m_nScroe = 0;
        assert(false);
    }
    return m_nScroe;
}

void Player_GameStatus::ResetGameStatus()
{
    m_nLife = Default_Life;
    m_nScroe = 0;
}

void Player_GameStatus::GetScoreList( ScoreList& list )
{
    memcpy(&list, &m_ScoreList, sizeof(m_ScoreList));
}

void Player_GameStatus::SetScoreList( const ScoreList& list )
{
    memcpy(&m_ScoreList, &list, sizeof(m_ScoreList));
}

bool Player_GameStatus::SetScore2List( int nScore )
{
    ///> 规定得分榜数字为增序
    ///> 从前往后找，得到比输入得分小的数字的个数
    int i = 0;
    for (; i < 10; ++i)
    {
        if (m_ScoreList.nScore[i] > nScore)
        {
            break;
        }
    }
    if (i > 0)
    {
        ///> 将比输入得分小的数字往左移，最左的丢弃
        for (int j = 1; j < i; ++j)
        {
            m_ScoreList.nScore[j - 1] = m_ScoreList.nScore[j];
        }
        ///> 最后插入输入分数
        m_ScoreList.nScore[i - 1] = nScore;
        return true;
    }
    return false;
}
