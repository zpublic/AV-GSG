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

CGameControler * CGameControler::pGameControler = NULL;

CGameControler* CGameControler::GetInstance()
{
    if (NULL == pGameControler)
    {
        pGameControler = new CGameControler;
    }

    return pGameControler;
}

CGameControler::CGameControler(void)
    : m_nY(0)
    , m_PresentStage(0)
{
    m_nPreKey = m_nCurKey = 0;
    m_pSelfPlane = CSelfPlane::GetInstance();

    m_hBitmapMap = NULL;
    m_hMemBitmap = NULL;
    m_hMemDC = NULL;
    m_hMapDC = NULL;
}

CGameControler::~CGameControler(void)
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
    if (m_hMemDC)
    {
        DeleteDC(m_hMemDC);
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
    BitBlt(m_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hMapDC, 0, 0, SRCCOPY);

    TCHAR szOut[100] = {0};
    wsprintf(szOut, L"最终得分：%d", CScore::GetScore());
    ::MessageBox(0, szOut, L"", 0);
}

void CGameControler::GameReady()
{
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    m_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\gameready.bmp"), IMAGE_BITMAP,
        SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
    SelectObject(m_hMapDC, m_hBitmapMap);
    BitBlt(m_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hMapDC, 0, 0, SRCCOPY);
}

void CGameControler::CirculationMap()
{
    BitBlt(m_hMemDC, 0, 0, SCREEN_WIDTH, m_nY, m_hMapDC, 0, SCREEN_HEIGHT - m_nY, SRCCOPY);
    BitBlt(m_hMemDC, 0, m_nY, SCREEN_WIDTH, SCREEN_HEIGHT - m_nY, m_hMapDC, 0, 0, SRCCOPY);

    if (!CGameStatus::GetGamePause())
        {
    m_nY += 1;
    if(m_nY == SCREEN_HEIGHT)
        m_nY = 0;
    }
}

void CGameControler::SetWndDC(HDC hDC)
{
    m_hWndDC = hDC;
    m_hMemDC = CreateCompatibleDC(hDC);
    m_hMapDC = CreateCompatibleDC(hDC);

    if (m_hMemBitmap) DeleteObject(m_hBitmapMap);
    m_hMemBitmap = CreateCompatibleBitmap(hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
    SelectObject(m_hMemDC, m_hMemBitmap);
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

void CGameControler::PauseGame()
{
    if (!CGameStatus::GetGameRuning())
    {
        return;
    }
    CGameStatus::PauseGame();
}

void CGameControler::RecoveGame()
{
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

    SelectObject(m_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(m_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    CirculationMap();
    if (CGameStagePlayer::GetInstance().PresentStatus() == emGameStagePlayStatusNone)
    {
        ::MessageBox(0, _T("过关了！"), _T("过关了！"), MB_OK);
        CGameStagePlayer::GetInstance().NextStage();
    }
    if (!CGameStatus::GetGamePause())
    {
        CGameStagePlayer::GetInstance().Updata(CEnemyGenerate::EnemyNumber());
        CEnemyGenerate::CreateEnemy(CGameStagePlayer::GetInstance().PresentObject(),
            CGameStagePlayer::GetInstance().Stopwatch());
        CGameFrame::FrameUpdate();
    }
    CGameFrame::FrameRender(m_hMemDC);

    BitBlt(m_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hMemDC, 0, 0, SRCCOPY);
}

void CGameControler::KeyDown(WPARAM nKeyCode)
{
    if (nKeyCode == 'P')
    {
        if (CGameStatus::GetGamePause())
        {
            RecoveGame();
        }
        else
        {
            PauseGame();
            m_pSelfPlane->Control(STOP_MOVE);
        }
    }
    if (CGameStatus::GetGamePause())
    {
        return;
    }
    if (nKeyCode == VK_LEFT)
        nKeyCode = 'A';
    if (nKeyCode == VK_DOWN)
        nKeyCode = 'S';
    if (nKeyCode == VK_RIGHT)
        nKeyCode = 'D';
    if (nKeyCode == VK_UP)
        nKeyCode = 'W';
    switch (nKeyCode)
    {
    case 'A':
    case 'S':
    case 'D':
    case 'W':
        m_nPreKey = m_nCurKey;
        m_nCurKey = nKeyCode;

        if ( (m_nPreKey + m_nCurKey)%'A' == 0)
        {
            m_pSelfPlane->Control(LEFT);
        }
        else if ((m_nPreKey + m_nCurKey)%'D'==0)
        {
            m_pSelfPlane->Control(RIGHT);
        }
        else if ((m_nPreKey + m_nCurKey)%'W' == 0)
        {
            m_pSelfPlane->Control(UP);
        }
        else if ((m_nPreKey + m_nCurKey)%'S' == 0)
        {
            m_pSelfPlane->Control(DOWN);
        }
        else if ((m_nPreKey + m_nCurKey) == ('A' + 'W'))
        {
            m_pSelfPlane->Control(LEFT_UP);

        }
        else if ((m_nPreKey + m_nCurKey) == ('A' + 'S'))
        {
            m_pSelfPlane->Control(LEFT_DOWN);

        }
        else if ((m_nPreKey + m_nCurKey) == ('D' + 'W'))
        {
            m_pSelfPlane->Control(RIGHT_UP);

        }
        else if ((m_nPreKey + m_nCurKey) == ('D' + 'S'))
        {
            m_pSelfPlane->Control(RIGHT_DOWN);

        }
        break;
    case 'J':
    case 'Z':
        m_pSelfPlane->Control(FIRE);
        break;
    case '1':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO0);
        break;
    case '2':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO1);
        break;
    case '3':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO2);
        break;
    case '4':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO3);
        break;
    case VK_SPACE:
    case 'K':
    case 'X':
        m_pSelfPlane->Control(FIREALL);
        break;
    }
}

void CGameControler::KeyUp(WPARAM nKeyCode)
{
    if (nKeyCode == VK_LEFT)
        nKeyCode = 'A';
    if (nKeyCode == VK_DOWN)
        nKeyCode = 'S';
    if (nKeyCode == VK_RIGHT)
        nKeyCode = 'D';
    if (nKeyCode == VK_UP)
        nKeyCode = 'W';
    if (nKeyCode == m_nCurKey)
    {
        if (m_nPreKey && (m_nPreKey != m_nCurKey))
        {
            m_nCurKey = m_nPreKey;
            m_nPreKey = 0;
            if ((m_nPreKey + m_nCurKey) % 'A' ==0)
            {
                m_pSelfPlane->Control(LEFT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'D' == 0)
            {
                m_pSelfPlane->Control(RIGHT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'W' == 0)
            {
                m_pSelfPlane->Control(UP);
            }
            else if ( (m_nPreKey + m_nCurKey) % 'S' == 0)
            {
                m_pSelfPlane->Control(DOWN);
            }
        }
        else
        {
            m_nCurKey = 0;
            m_pSelfPlane->Control(STOP_MOVE);
        }
    }
    else if (nKeyCode == m_nPreKey)
    {
        if (m_nCurKey)
        {
            m_nPreKey = 0;
            if ((m_nPreKey + m_nCurKey) % 'A' ==0)
            {
                m_pSelfPlane->Control(LEFT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'D' == 0)
            {
                m_pSelfPlane->Control(RIGHT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'W' == 0)
            {
                m_pSelfPlane->Control(UP);
            }
            else if ( (m_nPreKey + m_nCurKey) % 'S' == 0)
            {
                m_pSelfPlane->Control(DOWN);
            }
        }
        else
        {
            m_nPreKey = 0;
            m_pSelfPlane->Control(STOP_MOVE);
        }
    }
    else if ( nKeyCode == 'J' || nKeyCode == 'Z')
    {
        m_pSelfPlane->Control(STOP_FIRE);
    }
    else if ( nKeyCode == 'P')
    {
        m_pSelfPlane->Control(STOP_FIRE);
    }
}
