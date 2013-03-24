#include "stdafx.h"
#include "InputEngine.h"

template<> InputEngine* Singleton<InputEngine>::m_pInst = NULL;

InputEngine::~InputEngine()
{

}

bool InputEngine::SingletonInitialize()
{
    return true;
}

InputEngine::InputEngine()
{
    m_nPreKey = 0;
    m_nCurKey = 0;
}

void InputEngine::KeyDown( WPARAM nKeyCode )
{
    if (nKeyCode == VK_LEFT)
        nKeyCode = 'A';
    if (nKeyCode == VK_DOWN)
        nKeyCode = 'S';
    if (nKeyCode == VK_RIGHT)
        nKeyCode = 'D';
    if (nKeyCode == VK_UP)
        nKeyCode = 'W';

    m_nPreKey = m_nCurKey;
    m_nCurKey = nKeyCode;
}

void InputEngine::KeyUp( WPARAM nKeyCode )
{
    if (nKeyCode == VK_LEFT)
        nKeyCode = 'A';
    if (nKeyCode == VK_DOWN)
        nKeyCode = 'S';
    if (nKeyCode == VK_RIGHT)
        nKeyCode = 'D';
    if (nKeyCode == VK_UP)
        nKeyCode = 'W';
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

