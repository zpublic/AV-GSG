#pragma once
#include "Singleton.h"

class InputEngine : public Singleton<InputEngine>
{
    friend class Singleton<InputEngine>;

public:
    virtual ~InputEngine();
    virtual bool Initialize();

    void KeyDown(WPARAM nKeyCode);
    void KeyUp(WPARAM nKeyCode);

    int GetPreKey();
    int GetCurKey();

    bool PressPause();
    bool PressFireAll();

private:
    InputEngine();

    int     m_nPreKey;
    int     m_nCurKey;

    bool    m_bPressPause;
    bool    m_bPressFireAll;
};
