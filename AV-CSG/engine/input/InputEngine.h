#pragma once
#include "unit\Singleton.h"
#include "MoveDirection.h"

class InputEngine : public Singleton<InputEngine>
{
    friend class Singleton<InputEngine>;

public:
    virtual ~InputEngine();
    virtual bool Initialize();

    void KeyDown(WPARAM nKeyCode);
    void KeyUp(WPARAM nKeyCode);

    bool PressPause();
    bool PressFireAll();

    bool PressFire();

    MoveDirection GetMoveDirection();

private:
    InputEngine();

    CMoveDirection m_MoveDirection;

    bool    m_bPressPause;
    bool    m_bPressFireAll;
    bool    m_bPressFire;
};
