#pragma once
#include "GameScene.h"
#include <tchar.h>
#include <cstring>

#define MAX_PATH 260

class GameScene_Background : public GameScene
{
public:
    GameScene_Background(const TCHAR* lpszPath, HDC BkDc);
    virtual ~GameScene_Background();

    virtual void Update();
    virtual void Output();

private:
    GameScene_Background();
    HDC m_BackgourdDC;
    bool _LoadImage(const TCHAR* lpszPath, HDC BkDc);
};
