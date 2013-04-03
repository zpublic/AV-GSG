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

    bool ClickPause();
    bool ClickFireAll();

    bool ClickFire();
    bool ClickUp();
    bool ClickDown();
    bool ClickLeft();
    bool ClickRigth();

    bool PressFire();

    MoveDirection GetMoveDirection();

private:
    InputEngine();

    CMoveDirection m_MoveDirection;

    bool    m_bClickPause;
    bool    m_bClickFireAll;
    bool    m_bClickFire;
    bool    m_bClickUp;
    bool    m_bClickDown;
    bool    m_bClickLeft;
    bool    m_bClickRigth;

    bool    m_bPressFire;
};
