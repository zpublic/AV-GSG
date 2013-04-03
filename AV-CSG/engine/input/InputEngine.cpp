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
    m_bClickPause   = false;
    m_bClickFireAll = false;
    m_bPressFire    = false;
    m_bClickFire    = false;
    m_bClickUp      = false;
    m_bClickDown    = false;
    m_bClickLeft    = false;
    m_bClickRigth   = false;
}

inline void ConvertDirection(WPARAM& nKeyCode)
{
    if (nKeyCode == VK_LEFT)
        nKeyCode = 'A';
    else if (nKeyCode == VK_DOWN)
        nKeyCode = 'S';
    else if (nKeyCode == VK_RIGHT)
        nKeyCode = 'D';
    else if (nKeyCode == VK_UP)
        nKeyCode = 'W';
}

void InputEngine::KeyDown( WPARAM nKeyCode )
{
    ConvertDirection(nKeyCode);
    if (nKeyCode == 'P')
    {
        m_bClickPause = true;
    }
    else if (nKeyCode == 'X' || nKeyCode == 'K')
    {
        m_bClickFireAll = true;
    }
    else if (nKeyCode == 'J' || nKeyCode == 'Z')
    {
        m_bPressFire = true;
        m_bClickFire = true;
    }
    else
    {
        switch (nKeyCode)
        {
        case 'A':
            m_bClickLeft = true;
            break;
        case 'S':
            m_bClickDown = true;
            break;
        case 'D':
            m_bClickRigth = true;
            break;
        case 'W':
            m_bClickUp = true;
            break;
        default:
            break;
        }
        m_MoveDirection.Down(nKeyCode);
    }
}

void InputEngine::KeyUp( WPARAM nKeyCode )
{
    ConvertDirection(nKeyCode);
    if (nKeyCode == 'P')
    {
        m_bClickPause = false;
    }
    else if (nKeyCode == 'X' || nKeyCode == 'K')
    {
        m_bClickFireAll = false;
    }
    else if (nKeyCode == 'J' || nKeyCode == 'Z')
    {
        m_bPressFire = false;
        m_bClickFire = false;
    }
    else
    {
        switch (nKeyCode)
        {
        case 'A':
            m_bClickLeft = false;
            break;
        case 'S':
            m_bClickDown = false;
            break;
        case 'D':
            m_bClickRigth = false;
            break;
        case 'W':
            m_bClickUp = false;
            break;
        default:
            break;
        }
        m_MoveDirection.Up(nKeyCode);
    }
}

bool InputEngine::ClickPause()
{
    if (m_bClickPause)
    {
        m_bClickPause = false;
        return true;
    }
    return false;
}

bool InputEngine::ClickFireAll()
{
    if (m_bClickFireAll)
    {
        m_bClickFireAll = false;
        return true;
    }
    return false;
}

bool InputEngine::ClickFire()
{
    if (m_bClickFire)
    {
        m_bClickFire = false;
        return true;
    }
    return false;
}

bool InputEngine::ClickOk()
{
    return ClickFire();
}

bool InputEngine::ClickUp()
{
    if (m_bClickUp)
    {
        m_bClickUp = false;
        return true;
    }
    return false;
}

bool InputEngine::ClickDown()
{
    if (m_bClickDown)
    {
        m_bClickDown = false;
        return true;
    }
    return false;
}

bool InputEngine::ClickLeft()
{
    if (m_bClickLeft)
    {
        m_bClickLeft = false;
        return true;
    }
    return false;
}

bool InputEngine::ClickRigth()
{
    if (m_bClickRigth)
    {
        m_bClickRigth = false;
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

