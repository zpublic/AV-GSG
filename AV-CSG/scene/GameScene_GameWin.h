#pragma once
#include "GameScene.h"
#include "data\resourcedata\Picture.h"
#include <string>

class GameScene_GameWin : public GameScene
{
public:
    GameScene_GameWin();
    virtual ~GameScene_GameWin();

    virtual void Update();
    virtual void Output();
    virtual void Reset();

private:
    CPicture* m_Picture;
};