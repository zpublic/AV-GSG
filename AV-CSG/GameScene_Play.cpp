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
    ControlSelfPlane();
    CGameStagePlayer::GetInstance().Updata(CEnemyGenerate::EnemyNumber());
    CEnemyGenerate::CreateEnemy(
        CGameStagePlayer::GetInstance().Stopwatch());
    FrameUpdate();
}

void GameScene_Play::Output()
{
    FrameRender(g_hMemDC);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}

void GameScene_Play::ControlSelfPlane()
{
    if (InputEngine_->PressFireAll())
    {
        CSelfPlane::GetInstance()->Control(FIREALL);
    }
    switch (InputEngine_->GetMoveDirection())
    {
    case MoveDirection::MoveDirection_DOWN:
        CSelfPlane::GetInstance()->Control(DOWN);
        break;
    case MoveDirection::MoveDirection_UP:
        CSelfPlane::GetInstance()->Control(UP);
        break;
    case MoveDirection::MoveDirection_LEFT:
        CSelfPlane::GetInstance()->Control(LEFT);
        break;
    case MoveDirection::MoveDirection_RIGHT:
        CSelfPlane::GetInstance()->Control(RIGHT);
        break;
    case MoveDirection::MoveDirection_LEFT_DOWN:
        CSelfPlane::GetInstance()->Control(LEFT_DOWN);
        break;
    case MoveDirection::MoveDirection_LEFT_UP:
        CSelfPlane::GetInstance()->Control(LEFT_UP);
        break;
    case MoveDirection::MoveDirection_RIGHT_DOWN:
        CSelfPlane::GetInstance()->Control(RIGHT_DOWN);
        break;
    case MoveDirection::MoveDirection_RIGHT_UP:
        CSelfPlane::GetInstance()->Control(RIGHT_UP);
        break;
    case MoveDirection::MoveDirection_NONE:
        CSelfPlane::GetInstance()->Control(STOP_MOVE);
        break;
    default:
        CSelfPlane::GetInstance()->Control(STOP_MOVE);
    }
    if (InputEngine_->PressFire())
    {
        CSelfPlane::GetInstance()->Control(FIRE);
    }
    else
    {
        CSelfPlane::GetInstance()->Control(STOP_FIRE);
    }
}
