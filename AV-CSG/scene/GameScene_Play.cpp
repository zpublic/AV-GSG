#include "stdafx.h"
#include "GameScene_Play.h"
#include "GameScene_Pause.h"
#include "control\game\GameFrame.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\generate\EnemyGenerate.h"
#include "GameScene_Chat.h"
#include "GameScene_GameOver.h"
#include "GameScene_GameWin.h"

GameScene_Play::GameScene_Play()
    : m_Picture(NULL)
    , m_nY(0)
    , m_nPresentStage(0)
    , m_nDeadPlane(0)
    , m_nEnemyPlane(0)
    , m_lnFrame(0)
    , m_lnSecond(0)
    , m_pStage(NULL)
    , m_IsChat(false)
{
    m_nPresentStage = CGameStagePlayer::GetInstance().FirstStageId();
    m_pStage = CGameStagePlayer::GetInstance().GetStage(m_nPresentStage);
    if (m_pStage)
    {
        if (!m_pStage->GetChat().empty())
        {
            SceneEngine_->Push(new GameScene_Chat(m_pStage->GetChat()));
            m_Picture = CPicturePool::GetInstance()->GetPicture(
                CGameStagePlayer::GetInstance().GetStage(m_nPresentStage)->GetMap());
            m_nEnemyPlane = m_pStage->GetEnemyNumber();
            CEnemyGenerate::IniEnemy(m_pStage);
            if (m_Picture)
            {
                m_Picture->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
            }
        }
    }
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
    m_lnFrame++;
    if (m_lnFrame == FastenFrameNum_Play)
    {
        m_lnSecond++;
        m_lnFrame = 0;
        CEnemyGenerate::CreateEnemy(m_lnSecond);
    }
    m_nDeadPlane = CEnemyGenerate::EnemyNumber();
    CSelfPlane::GetInstance()->Update();
    FrameUpdate();
}

void GameScene_Play::Output()
{
    if (m_IsChat && m_pStage)
    {
        //加载对话场景 忽视后面绘制
        SceneEngine_->Push(new GameScene_Chat(m_pStage->GetChat()));
        m_IsChat = false;
        return;
    }
    ///> 清空图像
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (m_Picture)
    {
        m_Picture->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, m_nY, 0, SCREEN_HEIGHT - m_nY);
        m_Picture->DrawBitmap(g_hMemDC, 0, m_nY, SCREEN_WIDTH, SCREEN_HEIGHT - m_nY, 0, 0);
    }
    FrameRender(g_hMemDC);
    CSelfPlane::GetInstance()->Render(g_hMemDC);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
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
    if (m_nEnemyPlane == m_nDeadPlane)
    {
        m_nPresentStage++;
        m_pStage = CGameStagePlayer::GetInstance().GetStage(m_nPresentStage);
        if (m_pStage)
        {
            //读取下一个关卡资源
            m_Picture = CPicturePool::GetInstance()->GetPicture(
                CGameStagePlayer::GetInstance().GetStage(m_nPresentStage)->GetMap());
            CEnemyGenerate::IniEnemy(m_pStage);
            m_nEnemyPlane = m_pStage->GetEnemyNumber();
            if (!m_pStage->GetChat().empty())
            {
                m_IsChat = true;
            }
        }
        m_nDeadPlane = 0;
        m_lnFrame = 0;
        m_lnSecond = 0;
    }
    if (m_nPresentStage > CGameStagePlayer::GetInstance().StageCount())
    {
        //完成所有关卡 胜利
        UpdateScore();

        //弹出游戏控制器
        SceneEngine_->Pop();
        //载入胜利场景
        SceneEngine_->Push(new GameScene_GameWin);
    }
}

void GameScene_Play::TestGameOver()
{
    if (Player_->gamestatus_.GetLife() == 0)
    {
        UpdateScore();

        //弹出游戏流程场景
        SceneEngine_->Pop();
        //载入游戏结束场景
        SceneEngine_->Push(new GameScene_GameOver);
    }
}

void GameScene_Play::UpdateScore()
{
    int nMaxScore = Player_->gamestatus_.GetScore();
    Player_->gamestatus_.SetMaxScore(nMaxScore);
    if(Player_->gamestatus_.SetScore2List(nMaxScore))
    {
        Player_->savedata_.Save();
    }
}
