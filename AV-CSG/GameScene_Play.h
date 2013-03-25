#pragma once
#include "GameScene.h"
#include "GameStagePlayer.h"

class GameScene_Play : public GameScene
{
public:
    GameScene_Play();
    virtual ~GameScene_Play();

    virtual void Update();
    virtual void Output();

private:
    void ControlSelfPlane();
};
