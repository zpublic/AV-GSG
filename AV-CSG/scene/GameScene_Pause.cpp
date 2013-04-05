#include "stdafx.h"
#include "GameScene_Pause.h"
#include "control\game\GameFrame.h"

GameScene_Parse::GameScene_Parse()
{

}

GameScene_Parse::~GameScene_Parse()
{

}

void GameScene_Parse::Update()
{
    ///> 暂停场景只接受取消暂停的消息
    if (InputEngine_->ClickPause())
    {
        SceneEngine_->Pop();
    }
}

void GameScene_Parse::Output()
{
    FrameRender(g_hMemDC);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}

