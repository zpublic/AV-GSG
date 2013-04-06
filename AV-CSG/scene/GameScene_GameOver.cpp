#include "stdafx.h"
#include "GameScene_GameOver.h"
#include "GameScene_ScoreList.h"
#include "data\resourcedata\PicturePool.h"

GameScene_GameOver::GameScene_GameOver()
    : m_Picture(NULL)
{
    m_Picture = CPicturePool::GetInstance()->GetPicture("gameover");
}

GameScene_GameOver::~GameScene_GameOver()
{
}

void GameScene_GameOver::Update()
{
    if (InputEngine_->ClickOk())
    {
        SceneEngine_->Pop();
    }
}

void GameScene_GameOver::Reset()
{
    ///> Çå¿ÕÍ¼Ïñ
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameScene_GameOver::Output()
{
    //ÏÈ»æÖÆ±³¾°
    if (m_Picture)
    {
        m_Picture->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }

    SceneEngine_->Push(new GameScene_ScoreList);
}