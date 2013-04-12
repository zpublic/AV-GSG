#include "stdafx.h"
#include "GameScene_Chat.h"
#include "data\resourcedata\PicturePool.h"

GameScene_Chat::GameScene_Chat()
    : m_PictureBackgroud(NULL)
    , m_PictureMessageRect(NULL)
{
    m_PictureBackgroud = CPicturePool::GetInstance()->GetPicture("NULL");
    m_PictureMessageRect = CPicturePool::GetInstance()->GetPicture("NULL");
}

GameScene_Chat::~GameScene_Chat()
{
}

void GameScene_Chat::Update()
{
    if (InputEngine_->ClickOk())
    {
        SceneEngine_->Pop();
    }
}

void GameScene_Chat::Reset()
{
    ///> 清空图像
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameScene_Chat::Output()
{
    //先绘制背景
    if (m_PictureBackgroud)
    {
        m_PictureBackgroud->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }
    //再绘制对话框
    if (m_PictureMessageRect)
    {
        m_PictureMessageRect->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }

    ::SetBkMode(g_hMemDC, TRANSPARENT);
    ::SetTextColor(g_hMemDC, RGB(255,0,0));

    //::SetRect(&textRect, 180, 150, 200, 250);
    //::DrawText(g_hMemDC, szOut, -1, &textRect, DT_NOCLIP);
    //::BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}