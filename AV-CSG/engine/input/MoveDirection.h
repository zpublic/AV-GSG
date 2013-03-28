#pragma once

class CMoveDirection
{
public:
    CMoveDirection()
    {
        m_MoveDirection = MoveDirection::MoveDirection_NONE;
    }

    ~CMoveDirection()
    {
    }

    void Down(WPARAM nKeyCode)
    {
        if (nKeyCode == VK_LEFT)
            nKeyCode = 'A';
        if (nKeyCode == VK_DOWN)
            nKeyCode = 'S';
        if (nKeyCode == VK_RIGHT)
            nKeyCode = 'D';
        if (nKeyCode == VK_UP)
            nKeyCode = 'W';
        switch (nKeyCode)
        {
        case 'A':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            default:
                break;
            }
            break;
        case 'S':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            default:
                break;
            }
            break;
        case 'D':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            default:
                break;
            }
            break;
        case 'W':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    void Up(WPARAM nKeyCode)
    {
        if (nKeyCode == VK_LEFT)
            nKeyCode = 'A';
        if (nKeyCode == VK_DOWN)
            nKeyCode = 'S';
        if (nKeyCode == VK_RIGHT)
            nKeyCode = 'D';
        if (nKeyCode == VK_UP)
            nKeyCode = 'W';
        switch (nKeyCode)
        {
        case 'A':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            default:
                break;
            }
            break;
        case 'S':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_RIGHT_UP;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            default:
                break;
            }
            break;
        case 'D':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_LEFT_UP;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_UP;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            default:
                break;
            }
            break;
        case 'W':
            switch (m_MoveDirection)
            {
            case MoveDirection_NONE:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            case MoveDirection_LEFT:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_DOWN:
                m_MoveDirection = MoveDirection_DOWN;
                break;
            case MoveDirection_RIGHT:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            case MoveDirection_UP:
                m_MoveDirection = MoveDirection_NONE;
                break;
            case MoveDirection_LEFT_UP:
                m_MoveDirection = MoveDirection_LEFT;
                break;
            case MoveDirection_LEFT_DOWN:
                m_MoveDirection = MoveDirection_LEFT_DOWN;
                break;
            case MoveDirection_RIGHT_UP:
                m_MoveDirection = MoveDirection_RIGHT;
                break;
            case MoveDirection_RIGHT_DOWN:
                m_MoveDirection = MoveDirection_RIGHT_DOWN;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    MoveDirection Get()
    {
        return m_MoveDirection;
    }

private:
    MoveDirection m_MoveDirection;
};
