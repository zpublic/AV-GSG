#include "stdafx.h"
#include "GameScene_Play.h"
#include "GameScene_Pause.h"
#include "GameFrame.h"
#include "SelfPlane.h"
#include "EnemyGenerate.h"
#include "GameStatus.h"

GameScene_Play::GameScene_Play()
{

}

GameScene_Play::~GameScene_Play()
{

}

void GameScene_Play::Update()
{
    if (InputEngine_->PressPause())
    {
        SceneEngine::Instance()->Push(new GameScene_Parse());
        CGameStatus::PauseGame();
        CSelfPlane::GetInstance()->Control(STOP_MOVE);
    }
    else if (InputEngine_->PressFireAll())
    {
        CSelfPlane::GetInstance()->Control(FIREALL);
    }
    CSelfPlane::GetInstance()->GetInput();
    CGameStagePlayer::GetInstance().Updata(CEnemyGenerate::EnemyNumber());
    CEnemyGenerate::CreateEnemy(
        CGameStagePlayer::GetInstance().PresentObject(),
        CGameStagePlayer::GetInstance().Stopwatch());
    FrameUpdate();
}

void GameScene_Play::Output()
{
    FrameRender(g_hMemDC);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}
