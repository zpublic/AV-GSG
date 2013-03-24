#include "StdAfx.h"
#include "GameControler.h"
#include "Sprite.h"
#include "SelfPlane.h"
#include "Bullet.h"
#include "EnemyPlane.h"
#include "Explosion.h"
#include "GameFrame.h"
#include "EnemyGenerate.h"
#include "GameStatus.h"
#include "GameStagePlayer.h"
#include "Score.h"


HDC         g_hMemDC = NULL;
HDC         g_hWndDC = NULL;

CGameControler::CGameControler()
    : m_nY(0)
    , m_PresentStage(0)
{
    m_nPreKey = m_nCurKey = 0;
    m_pSelfPlane = CSelfPlane::GetInstance();

    m_hBitmapMap = NULL;
    m_hMemBitmap = NULL;
    m_hMapDC = NULL;
}

CGameControler::~CGameControler()
{

}

void CGameControler::SetStageXML(const std::string& strPath)
{
    CStageXMLParse::GetInstance().LoadXML(strPath);
    CGameStagePlayer::GetInstance().Stage(&CStageXMLParse::GetInstance());
}

void CGameControler::SetPlaneXML(const std::string& strPath)
{
    CPlaneXMLParse::GetInstance().LoadXML(strPath);
}

void CGameControler::Exit()
{
    CPicturePool::GetInstance()->FreeImage();
    if (g_hMemDC)
    {
        DeleteDC(g_hMemDC);
    }
    if (m_hMapDC)
    {
        DeleteDC(m_hMapDC);
    }
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    if (m_hMemBitmap) DeleteObject(m_hMemBitmap);
}

void CGameControler::GameOver()
{
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    m_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\gameover.bmp"), IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(m_hMapDC, m_hBitmapMap);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hMapDC, 0, 0, SRCCOPY);

    TCHAR szOut[100] = {0};
    wsprintf(szOut, L"×îÖÕµÃ·Ö£º%d", CScore::GetScore());
    ::MessageBox(0, szOut, L"", 0);
}

void CGameControler::GameReady()
{
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    m_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\gameready.bmp"), IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(m_hMapDC, m_hBitmapMap);
    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hMapDC, 0, 0, SRCCOPY);
}

void CGameControler::CirculationMap()
{
    BitBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, m_nY, m_hMapDC, 0, SCREEN_HEIGHT - m_nY, SRCCOPY);
    BitBlt(g_hMemDC, 0, m_nY, SCREEN_WIDTH, SCREEN_HEIGHT - m_nY, m_hMapDC, 0, 0, SRCCOPY);

    if (!CGameStatus::GetGamePause())
        {
    m_nY += 1;
    if(m_nY == SCREEN_HEIGHT)
        m_nY = 0;
    }
}

void CGameControler::SetWndDC(HDC hDC)
{
    g_hWndDC = hDC;
    g_hMemDC = CreateCompatibleDC(hDC);
    m_hMapDC = CreateCompatibleDC(hDC);

    if (m_hMemBitmap) DeleteObject(m_hBitmapMap);
    m_hMemBitmap = CreateCompatibleBitmap(hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
    SelectObject(g_hMemDC, m_hMemBitmap);
}

void CGameControler::StartGame()
{
    m_dwLastTime = GetTickCount();
    srand((unsigned)time(0));

    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    m_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\Map.bmp"), IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(m_hMapDC, m_hBitmapMap);

    m_pSelfPlane->InitGame();
    CScore::Reset();
    CGameStatus::StartGame();
}

void CGameControler::UpdateScence()
{
    if (!CGameStatus::IsNeedUpdate())
    {
        Sleep(100);
        return;
    }
    if (CGameStatus::GetGameOver())
    {
        GameOver();
        CGameStatus::ClearGameStatus();
        Sleep(100);
        return;
    }
    if (CGameStatus::GetGameReady())
    {
        GameReady();
        CGameStatus::ClearGameStatus();
        Sleep(100);
        return;
    }

    DWORD dwElapsed = ::GetTickCount() - m_dwLastTime;
    if (dwElapsed < MSPERFRAME)
    {
        Sleep((DWORD)MSPERFRAME - dwElapsed);
    }
    m_dwLastTime = ::GetTickCount();

    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    CirculationMap();
    if (CGameStagePlayer::GetInstance().PresentStatus() == emGameStagePlayStatusNone)
    {
        CGameStagePlayer::GetInstance().NextStage();
    }
    ProcessInput();
    if (!CGameStatus::GetGamePause())
    {
        CGameStagePlayer::GetInstance().Updata(CEnemyGenerate::EnemyNumber());
        CEnemyGenerate::CreateEnemy(CGameStagePlayer::GetInstance().PresentObject(),
            CGameStagePlayer::GetInstance().Stopwatch());
        FrameUpdate();
    }
    FrameRender(g_hMemDC);

    BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}

void CGameControler::ProcessInput()
{
    if (InputEngine::Instance()->PressPause())
    {
        if (CGameStatus::GetGamePause())
        {
            CGameStatus::StartGame();
        }
        else
        {
            if (!CGameStatus::GetGameRuning())
            {
                return;
            }
            CGameStatus::PauseGame();
            m_pSelfPlane->Control(STOP_MOVE);
        }
    }
    else if (InputEngine::Instance()->PressFireAll())
    {
        m_pSelfPlane->Control(FIREALL);
    }
}