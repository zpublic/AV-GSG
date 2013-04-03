#include "stdafx.h"
#include "GameScene_FixedScene.h"
#include "control\game\GameStatus.h"

GameScene_FixedScene::GameScene_FixedScene(const TCHAR* lpszPath)
{
    m_Picture.LoadBitmap(lpszPath, SCREEN_WIDTH, SCREEN_HEIGHT);
}

GameScene_FixedScene::~GameScene_FixedScene()
{
}

GameScene_FixedScene::GameScene_FixedScene()
{
}

void GameScene_FixedScene::Update()
{
}

void GameScene_FixedScene::Output()
{
    m_Picture.ImmediateDrawBitmap(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
}