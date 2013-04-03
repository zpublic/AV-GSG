#include "stdafx.h"
#include "GameScene_Play.h"
#include "GameScene_Pause.h"
#include "control\game\GameFrame.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\generate\EnemyGenerate.h"
#include "control\game\GameStatus.h"

GameScene_Play::GameScene_Play(const TCHAR* lpszPath, HDC BkDc)
    : m_BackgourdDC(0)
    , m_nY(0)
{
    m_BackgourdDC = BkDc;
    _LoadImage(lpszPath, m_BackgourdDC);
    BitBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_BackgourdDC, 0, 0, SRCCOPY);
}

GameScene_Play::GameScene_Play()
{
}

GameScene_Play::~GameScene_Play()
{

}

void GameScene_Play::_CirculationMap()
{
    m_nY += 1;
    if(m_nY == SCREEN_HEIGHT)
    m_nY = 0;
}

bool GameScene_Play::_LoadImage(const TCHAR* lpszPath, HDC hDC)
{
    if (!lpszPath)
    {
        return false;
    }
    HBITMAP hBitMap = (HBITMAP)LoadImage(NULL, lpszPath,
        IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(hDC, hBitMap);
    if (hBitMap)
    {
        DeleteObject(hBitMap);
    }
    return true;
}

void GameScene_Play::Update()
{
    if (InputEngine_->PressPause())
    {
        SceneEngine::Instance()->Push(new GameScene_Parse());
        CGameStatus::PauseGame();
        CSelfPlane::GetInstance()->Control(STOP_MOVE);
    }
    _CirculationMap();
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
    //»æÖÆµØÍ¼
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    BitBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, m_nY, m_BackgourdDC, 0, SCREEN_HEIGHT - m_nY, SRCCOPY);
    BitBlt(g_hMemDC, 0, m_nY, SCREEN_WIDTH, SCREEN_HEIGHT - m_nY, m_BackgourdDC, 0, 0, SRCCOPY);
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
