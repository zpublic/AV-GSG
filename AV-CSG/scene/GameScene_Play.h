#pragma once
#include "GameScene.h"
#include "control\stage_player\GameStagePlayer.h"
#include "data\resourcedata\Picture.h"

class GameScene_Play : public GameScene
{
public:
    GameScene_Play(const std::string& strPic);
    virtual ~GameScene_Play();

    virtual void Update();
    virtual void Output();

private:
    GameScene_Play();
    void ControlSelfPlane();
    void CirculationMap();
    void ControlGameTiming();
    void TestGameOver();

    CPicture* m_Picture;
    int m_nY;
};
