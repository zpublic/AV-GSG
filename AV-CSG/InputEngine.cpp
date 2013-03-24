#include "stdafx.h"
#include "InputEngine.h"

template<> InputEngine* Singleton<InputEngine>::m_pInst = NULL;

InputEngine::~InputEngine()
{

}

bool InputEngine::Initialize()
{
    return true;
}

InputEngine::InputEngine()
{
    m_nPreKey       = 0;
    m_nCurKey       = 0;
    m_bPressPause   = false;
    m_bPressFireAll = false;
}

void InputEngine::KeyDown( WPARAM nKeyCode )
{
    if (nKeyCode == 'P')
    {
        m_bPressPause = true;
    }
    if (nKeyCode == 'X' || nKeyCode == 'K')
    {
        m_bPressFireAll = true;
    }

    m_nPreKey = m_nCurKey;
    m_nCurKey = nKeyCode;
}

void InputEngine::KeyUp( WPARAM nKeyCode )
{
    if (nKeyCode == 'P')
    {
        m_bPressPause = false;
    }
    if (nKeyCode == 'X' || nKeyCode == 'K')
    {
        m_bPressFireAll = false;
    }

    if (nKeyCode == m_nCurKey)
    {
        if (m_nPreKey && (m_nPreKey != m_nCurKey))
        {
            m_nCurKey = m_nPreKey;
            m_nPreKey = 0;
        }
        else
        {
            m_nCurKey = 0;
        }
    }
    else if (nKeyCode == m_nPreKey)
    {
        m_nPreKey = 0;
    }
}

int InputEngine::GetPreKey()
{
    return m_nPreKey;
}

int InputEngine::GetCurKey()
{
    return m_nCurKey;
}

bool InputEngine::PressPause()
{
    if (m_bPressPause)
    {
        m_bPressPause = false;
        return true;
    }
    return false;
}

bool InputEngine::PressFireAll()
{
    if (m_bPressFireAll)
    {
        m_bPressFireAll = false;
        return true;
    }
    return false;
}

