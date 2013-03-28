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
    m_bPressPause   = false;
    m_bPressFireAll = false;
    m_bPressFire    = false;
}

void InputEngine::KeyDown( WPARAM nKeyCode )
{
    if (nKeyCode == 'P')
    {
        m_bPressPause = true;
    }
    else if (nKeyCode == 'X' || nKeyCode == 'K')
    {
        m_bPressFireAll = true;
    }
    else if (nKeyCode == 'J' || nKeyCode == 'Z')
    {
        m_bPressFire = true;
    }
    else
    {
        m_MoveDirection.Down(nKeyCode);
    }
}

void InputEngine::KeyUp( WPARAM nKeyCode )
{
    if (nKeyCode == 'P')
    {
        m_bPressPause = false;
    }
    else if (nKeyCode == 'X' || nKeyCode == 'K')
    {
        m_bPressFireAll = false;
    }
    else if (nKeyCode == 'J' || nKeyCode == 'Z')
    {
        m_bPressFire = false;
    }
    else
    {
        m_MoveDirection.Up(nKeyCode);
    }
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

MoveDirection InputEngine::GetMoveDirection()
{
    return m_MoveDirection.Get();
}

bool InputEngine::PressFire()
{
    return m_bPressFire;
}

