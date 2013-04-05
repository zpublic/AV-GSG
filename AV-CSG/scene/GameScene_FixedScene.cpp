#include "stdafx.h"
#include "GameScene_FixedScene.h"
#include "data\resourcedata\PicturePool.h"
#include "GameScene_Menu.h"

GameScene_FixedScene::GameScene_FixedScene(const std::string& strPic)
{
    m_Picture = CPicturePool::GetInstance()->GetPicture(strPic);
}

GameScene_FixedScene::~GameScene_FixedScene()
{
}

GameScene_FixedScene::GameScene_FixedScene()
    : m_Picture(NULL)
{
}

void GameScene_FixedScene::Update()
{
    if (InputEngine_->ClickOk())
    {
        SceneEngine_->Pop();
    }
}

void GameScene_FixedScene::Output()
{
    if (m_Picture)
    {
        m_Picture->ImmediateDrawBitmap(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }
}