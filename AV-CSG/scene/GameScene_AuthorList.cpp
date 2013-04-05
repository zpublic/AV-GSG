#include "stdafx.h"
#include "GameScene_AuthorList.h"

GameScene_AuthorList::GameScene_AuthorList()
{
}

GameScene_AuthorList::~GameScene_AuthorList()
{

}

void GameScene_AuthorList::Reset()
{
    ///> 清空图像
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameScene_AuthorList::Update()
{
    if (InputEngine_->ClickOk())
    {
        SceneEngine_->Pop();
    }
}

void GameScene_AuthorList::Output()
{
    wchar_t* pAuthorList[] =
    {
        L"zapline",
        L"Sum",
        L"叶子",
        L"按‘j’返回..."
    };
    ::SetBkMode(g_hMemDC, TRANSPARENT);
    ::SetTextColor(g_hMemDC, RGB(200,200,100));
    for (auto i = 0; i < sizeof(pAuthorList) / sizeof(wchar_t*); ++i)
    {
        RECT textRect;
        ::SetRect(&textRect, 130, 150 + i * 30, 200, 250 + i * 30);
        ::DrawText(g_hMemDC, pAuthorList[i], -1, &textRect, DT_NOCLIP);
    }

    ::BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}
