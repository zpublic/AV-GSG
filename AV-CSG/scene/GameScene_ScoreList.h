#pragma once
#include "GameScene.h"

class GameScene_ScoreList : public GameScene
{
public:
    GameScene_ScoreList();
    virtual ~GameScene_ScoreList();

    virtual void Update();
    virtual void Output();
    virtual void Reset();
};
