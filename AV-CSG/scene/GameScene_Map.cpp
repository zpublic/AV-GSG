#include "stdafx.h"
#include "GameScene_Map.h"
#include "control\game\GameStatus.h"

GameScene_Map::GameScene_Map(const TCHAR* lpszPath, HDC BkDc, HDC MemDC)
    : m_MemDC(0)
    , m_BackgourdDC(0)
    , m_nY(0)
{
    m_MemDC = MemDC;
    m_BackgourdDC = BkDc;
    _LoadImage(lpszPath, m_BackgourdDC);
    BitBlt(m_MemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_BackgourdDC, 0, 0, SRCCOPY);
}

GameScene_Map::~GameScene_Map()
{
}

GameScene_Map::GameScene_Map()
{
}

void GameScene_Map::_CirculationMap()
{
    m_nY += 1;
    if(m_nY == SCREEN_HEIGHT)
    m_nY = 0;
}

bool GameScene_Map::_LoadImage(const TCHAR* lpszPath, HDC hDC)
{
    if (!lpszPath)
    {
        return false;
    }
    HBITMAP hBitMap = (HBITMAP)LoadImage(NULL, lpszPath,
        IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(hDC, hBitMap);
    if (hBitMap)
    {
        DeleteObject(hBitMap);
    }
    return true;
}

void GameScene_Map::Update()
{
    if (!CGameStatus::GetGamePause())
    {
        _CirculationMap();
    }
}

void GameScene_Map::Output()
{
    SelectObject(m_MemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(m_MemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    BitBlt(m_MemDC, 0, 0, SCREEN_WIDTH, m_nY, m_BackgourdDC, 0, SCREEN_HEIGHT - m_nY, SRCCOPY);
    BitBlt(m_MemDC, 0, m_nY, SCREEN_WIDTH, SCREEN_HEIGHT - m_nY, m_BackgourdDC, 0, 0, SRCCOPY);
}