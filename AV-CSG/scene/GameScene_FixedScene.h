#pragma once
#include "GameScene.h"
#include "data\resourcedata\Picture.h"

class GameScene_FixedScene : public GameScene
{
public:
    GameScene_FixedScene(const TCHAR* lpszPath);
    virtual ~GameScene_FixedScene();

    virtual void Update();
    virtual void Output();

private:
    GameScene_FixedScene();
    HDC m_BackgourdDC;
    CPicture m_Picture;
};
