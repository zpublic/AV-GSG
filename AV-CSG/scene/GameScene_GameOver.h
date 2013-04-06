#pragma once
#include "GameScene.h"
#include "data\resourcedata\Picture.h"
#include <string>

class GameScene_GameOver : public GameScene
{
public:
    GameScene_GameOver();
    virtual ~GameScene_GameOver();

    virtual void Update();
    virtual void Output();
    virtual void Reset();

private:
    CPicture* m_Picture;
};
