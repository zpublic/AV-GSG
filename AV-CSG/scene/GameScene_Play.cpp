#include "stdafx.h"
#include "GameScene_Play.h"
#include "GameScene_Pause.h"
#include "control\game\GameFrame.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\generate\EnemyGenerate.h"
#include "GameScene_FixedScene.h"

GameScene_Play::GameScene_Play(const std::string& strPic)
    : m_Picture(NULL)
    , m_nY(0)
{
    m_Picture = CPicturePool::GetInstance()->GetPicture(strPic);
    if (m_Picture)
    {
        m_Picture->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }
}

GameScene_Play::GameScene_Play()
{
}

GameScene_Play::~GameScene_Play()
{

}

void GameScene_Play::CirculationMap()
{
    m_nY += 1;
    if(m_nY == SCREEN_HEIGHT)
    m_nY = 0;
}

void GameScene_Play::Update()
{
    if (InputEngine_->ClickPause())
    {
        SceneEngine::Instance()->Push(new GameScene_Parse());
        CSelfPlane::GetInstance()->Control(STOP_MOVE);
    }

    ControlGameTiming();
    TestGameOver();

    CirculationMap();
    ControlSelfPlane();
    CGameStagePlayer::GetInstance().Updata(CEnemyGenerate::EnemyNumber());
    CEnemyGenerate::CreateEnemy(CGameStagePlayer::GetInstance().Stopwatch());
    FrameUpdate();
}

void GameScene_Play::Output()
{
    FrameRender(g_hMemDC);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
    //绘制地图
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (m_Picture)
    {
        m_Picture->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, m_nY, 0, SCREEN_HEIGHT - m_nY);
        m_Picture->DrawBitmap(g_hMemDC, 0, m_nY, SCREEN_WIDTH, SCREEN_HEIGHT - m_nY, 0, 0);
    }
}

void GameScene_Play::ControlSelfPlane()
{
    if (InputEngine_->ClickFireAll())
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

void GameScene_Play::ControlGameTiming()
{
    if (CGameStagePlayer::GetInstance().PresentStatus() == emGameStagePlayStatusNone)
    {
        CGameStagePlayer::GetInstance().NextStage();
        if (CGameStagePlayer::GetInstance().PresentStatus() == emGameStagePlayStatusWin)
        {
            //完成所有关卡 胜利
            //弹出游戏控制器
            SceneEngine_->Pop();
            //载入胜利场景
            SceneEngine_->Push(new GameScene_FixedScene("gamewin"));
        }
        else if (CGameStagePlayer::GetInstance().PresentObject())
        {
            CEnemyGenerate::ClearEnemy();
            CEnemyGenerate::IniEnemy(CGameStagePlayer::GetInstance().PresentObject());
            SceneEngine_->Pop();
            SceneEngine_->Push(new GameScene_Play(
                CGameStagePlayer::GetInstance().PresentObject()->GetMap()));
        }
    }
}

void GameScene_Play::TestGameOver()
{
    if (Player_->gamestatus_.GetLife() == 0)
    {
        //弹出游戏流程场景
        SceneEngine_->Pop();
        //载入游戏结束画面
        SceneEngine_->Push(new GameScene_FixedScene("gameover"));
        TCHAR szOut[100] = {0};
        wsprintf(szOut, L"最终得分：%d", Player_->gamestatus_.GetScore());
        ::MessageBox(0, szOut, L"", 0);
    }
}