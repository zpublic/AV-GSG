#include "stdafx.h"
#include "GameScene_Background.h"
#include "control\game\GameStatus.h"

GameScene_Background::GameScene_Background(const TCHAR* lpszPath, HDC BkDc)
    : m_BackgourdDC(0)
{
    m_BackgourdDC = BkDc;
    _LoadImage(lpszPath, BkDc);
    BitBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_BackgourdDC, 0, 0, SRCCOPY);
}

GameScene_Background::~GameScene_Background()
{
}

GameScene_Background::GameScene_Background()
{
}


bool GameScene_Background::_LoadImage(const TCHAR* lpszPath, HDC BkDc)
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

void GameScene_Background::Update()
{
}

void GameScene_Background::Output()
{
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_BackgourdDC, 0, 0, SRCCOPY);
}