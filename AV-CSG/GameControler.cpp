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

CGameControler::CGameControler(void):m_nY(0),
    m_fElapsedTime(0)
{
    m_nPreKey = m_nCurKey = 0;
    CPicturePool::LoadImage();
    m_pSelfPlane = CSelfPlane::GetInstance();	

    m_hBitmapMap = NULL;
    m_hMemBitmap = NULL;
    m_hMemDC = NULL;
    m_hMapDC = NULL;
}

CGameControler::~CGameControler(void)
{

}

void CGameControler::Exit()
{
    CPicturePool::FreeImage();
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
    wsprintf(szOut, L"×îÖÕµÃ·Ö£º%d", CScore::GetScore());
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

    m_nY += 1;
    if(m_nY == SCREEN_HEIGHT)
        m_nY = 0;
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

void CGameControler::UpdateScence()
{
    if (!CGameStatus::IsNeedUpdate())
    {
        return;
    }
    if (CGameStatus::GetGameOver())
    {
        GameOver();
        CGameStatus::ClearGameStatus();
        return;
    }
    if (CGameStatus::GetGameReady())
    {
        GameReady();
        CGameStatus::ClearGameStatus();
        return;
    }

    m_dwCurrentTime = GetTickCount();
    if (m_dwCurrentTime - m_dwLastTime < MSPERFRAME)
    {
        return;
    }

    SelectObject(m_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(m_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    CirculationMap();
    m_fElapsedTime = (m_dwCurrentTime - m_dwLastTime) / 1000.0f;

    m_dwLastTime = m_dwCurrentTime;

    CEnemyGenerate::CreateEnemy();
    CGameFrame::FrameUpdate();
    CGameFrame::FrameRender(m_hMemDC);

    BitBlt(m_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hMemDC, 0, 0, SRCCOPY);
}

void CGameControler::KeyDown(WPARAM nKeyCode)
{
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
    case '5':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO4);
        break;
    case '6':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO5);
        break;
    case '7':
        m_pSelfPlane->SetBulletType(emBulletTypeAMMO6);
        break;
    case 'Q':
        m_pSelfPlane->SetBulletType(emBulletTypeAmmoSB);
        break;
    case 'E':
        m_pSelfPlane->SetBulletType(emBulletTypeAmmoSB2);
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
}
