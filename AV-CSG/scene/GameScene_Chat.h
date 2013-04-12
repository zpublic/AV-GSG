#pragma once
#include "GameScene.h"
#include "data\resourcedata\Picture.h"
#include <string>

class GameScene_Chat : public GameScene
{
public:
    GameScene_Chat();
    virtual ~GameScene_Chat();

    virtual void Update();
    virtual void Output();
    virtual void Reset();

private:
    CPicture* m_PictureBackgroud;
    CPicture* m_PictureMessageRect;
};