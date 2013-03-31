#pragma once
#include "GameScene.h"
#include <tchar.h>
#include <cstring>

#define MAX_PATH 260

class GameScene_Map : public GameScene
{
public:
    GameScene_Map(const TCHAR* lpszPath, HDC BkDc, HDC MemDc);
    virtual ~GameScene_Map();

    virtual void Update();
    virtual void Output();

private:
    GameScene_Map();
    void _CirculationMap();
    bool _LoadImage(const TCHAR* lpszPath, HDC hDC);
    HDC m_MemDC;
    HDC m_BackgourdDC;
    int m_nY;
};
