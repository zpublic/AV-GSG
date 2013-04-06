#include "stdafx.h"
#include "GameScene_ScoreList.h"

GameScene_ScoreList::GameScene_ScoreList()
{
}

GameScene_ScoreList::~GameScene_ScoreList()
{

}

void GameScene_ScoreList::Reset()
{
    ///> Çå¿ÕÍ¼Ïñ
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameScene_ScoreList::Update()
{
    if (InputEngine_->ClickOk())
    {
        SceneEngine_->Pop();
    }
}

void GameScene_ScoreList::Output()
{
    CString strTemp;
    RECT textRect;
    ScoreList scoreList;
    Player_->gamestatus_.GetScoreList(scoreList);
    ::SetBkMode(g_hMemDC, TRANSPARENT);
    ::SetTextColor(g_hMemDC, RGB(255,255,150));
    ::SetRect(&textRect, 130, 130, 200, 250);
    ::DrawText(g_hMemDC, L"µÃ·Ö°ñ", -1, &textRect, DT_NOCLIP);
    for (int i = 1; i <= 10; ++i)
    {
        strTemp.Format(L"rank %2d", i);
        ::SetTextColor(g_hMemDC, RGB(200,200,150));
        ::SetRect(&textRect, 130, 150 + i * 30, 200, 250 + i * 30);
        ::DrawText(g_hMemDC, strTemp, -1, &textRect, DT_NOCLIP);
        ::SetTextColor(g_hMemDC, RGB(200,200,100));
        strTemp.Format(L":     %08d", scoreList.nScore[10-i]);
        ::SetRect(&textRect, 200, 150 + i * 30, 200, 250 + i * 30);
        ::DrawText(g_hMemDC, strTemp, -1, &textRect, DT_NOCLIP);
    }

    ::BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}
