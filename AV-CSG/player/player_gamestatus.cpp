#include "stdafx.h"
#include "player_gamestatus.h"



Player_GameStatus::Player_GameStatus()
    : m_nMaxScore(0)
    , m_nLife(Default_Life)
    , m_HP(0)
    , m_nScroe(0)
{
    for(int i = 0; i < 10; ++i)
    {
        m_nScoreList.push_front(0);
    }
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


bool Player_GameStatus::PopScore(int& nScore)
{
    if(m_nScoreList.empty())
    {
        return false;
    }

    nScore = m_nScoreList.front();
    m_nScoreList.pop_front();
    return true;
}

bool Player_GameStatus::PushScore(int nScore)
{
    if(nScore < 0)
    {
        return false;
    }

    int nBackVal = m_nScoreList.back();
    if(nScore <= nBackVal && m_nScoreList.size() == 10)
    {
        return false;
    }


    auto it = m_nScoreList.begin();
    while(it != m_nScoreList.end())
    {
        if(nScore > *it)
        {
            m_nScoreList.insert(it, nScore);
            break;
        }
        ++it;
        continue;
    }

    int nListSize = m_nScoreList.size();
    while(--nListSize >= 10)
    {
        m_nScoreList.pop_back();
    }
}

void Player_GameStatus::SetScoreStack(int nScoreStack[])
{
    auto it = m_nScoreList.begin();
    while(it != m_nScoreList.end())
    {
        if(*nScoreStack <= 0)
        {
            break;
        }
        m_nScoreList.insert(it, *nScoreStack++);
    }

    int nListSize = m_nScoreList.size();
    while(--nListSize >= 10)
    {
        m_nScoreList.pop_back();
    }

}

bool Player_GameStatus::GetScoreStack(int nScoreStack[])
{
    if(m_nScoreList.empty())
    {
        return false;
    }

    ///> 从最高的分数依次传递给nScoreStack数组
    for(auto it = m_nScoreList.begin();
        it != m_nScoreList.end();
        ++it)
    {
        *nScoreStack++ = *it;
    }

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
        assert(false);
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
