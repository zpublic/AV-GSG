#include "stdafx.h"
#include "GameScene_FixedScene.h"
#include "control\game\GameStatus.h"

GameScene_FixedScene::GameScene_FixedScene(const TCHAR* lpszPath, HDC BkDc)
    : m_BackgourdDC(0)
{
    m_BackgourdDC = BkDc;
    _LoadImage(lpszPath, BkDc);
    BitBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_BackgourdDC, 0, 0, SRCCOPY);
}

GameScene_FixedScene::~GameScene_FixedScene()
{
}

GameScene_FixedScene::GameScene_FixedScene()
{
}


bool GameScene_FixedScene::_LoadImage(const TCHAR* lpszPath, HDC BkDc)
{
    if (!lpszPath)
    {
        return false;
    }
    HBITMAP hBitMap = (HBITMAP)LoadImage(NULL, lpszPath,
        IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(BkDc, hBitMap);
    if (hBitMap)
    {
        DeleteObject(hBitMap);
    }
    return true;
}

void GameScene_FixedScene::Update()
{
}

void GameScene_FixedScene::Output()
{
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_BackgourdDC, 0, 0, SRCCOPY);
}