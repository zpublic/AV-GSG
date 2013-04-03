#pragma once
#include "GameScene.h"
#include "control\stage_player\GameStagePlayer.h"

class GameScene_Play : public GameScene
{
public:
    GameScene_Play(const TCHAR* lpszPath, HDC BkDc);
    virtual ~GameScene_Play();

    virtual void Update();
    virtual void Output();

private:
    GameScene_Play();
    void ControlSelfPlane();
    void _CirculationMap();
    bool _LoadImage(const TCHAR* lpszPath, HDC hDC);
    HDC m_BackgourdDC;
    int m_nY;
};
