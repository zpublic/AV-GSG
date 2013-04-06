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
    ///> ���ͼ��
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
    ScoreList scoreList;
    Player_->gamestatus_.GetScoreList(scoreList);

    ///> ���õ÷ְ���ַ���
    TCHAR szOut[300] = {0};
    TCHAR szCat[30] = {0};
    int j = 9;
    for(int i = 0 ; i < 10; ++i)
    {
        wsprintf(szCat, L"��%d��\t����: %d\n", i + 1, scoreList.nScore[j--]);
        wcscat(szOut, szCat);
    }

    ///> �����ڴ�DC
    ::SetBkMode(g_hMemDC, TRANSPARENT);
    ::SetTextColor(g_hMemDC, RGB(200,200,100));
    RECT textRect;
    ::SetRect(&textRect, 130, 150, 300, 500);
    ::DrawText(g_hMemDC, szOut, -1, &textRect, DT_NOCLIP);

    ///> ���Ƶ÷����а�
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}
