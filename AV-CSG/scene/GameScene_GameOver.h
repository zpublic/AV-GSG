#pragma once
#include "GameScene.h"
#include "data\resourcedata\Picture.h"
#include <string>

class GameScene_GameOver : public GameScene
{
public:
    GameScene_GameOver(const std::string& strPic);
    virtual ~GameScene_GameOver();

    virtual void Update();
    virtual void Output();
    virtual void Reset();

private:
    GameScene_GameOver();
    CPicture* m_Picture;
};
