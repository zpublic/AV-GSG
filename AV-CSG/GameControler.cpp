#include "StdAfx.h"
#include "GameControler.h"
#include "Sprite.h"
#include "PrincipalPlane.h"
#include "Bullet.h"
#include "EnemyPlane.h"
#include "Explosion.h"
#include "GameFrame.h"

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
    CPrincipalPlane::LoadBimap();
    CPicturePool::LoadImage();
    m_pPrincipalPlane = CPrincipalPlane::GetInstance();	

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
    CPrincipalPlane::FreeBitmap();
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
    if(m_nY==480)
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

    CPrincipalPlane::StartGame();
}

void CGameControler::UpdateScence()
{
    if (!CPrincipalPlane::IsNeedUpdate())
    {
        return;
    }
    if (CPrincipalPlane::GetGameOver())
    {
        GameOver();
        CPrincipalPlane::ClearGameStatus();
        return;
    }
    if (CPrincipalPlane::GetGameReady())
    {
        GameReady();
        CPrincipalPlane::ClearGameStatus();
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

    CEnemyPlane::CreateEnemy();
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
            m_pPrincipalPlane->Control(LEFT);
        }
        else if ((m_nPreKey + m_nCurKey)%'D'==0)
        {
            m_pPrincipalPlane->Control(RIGHT);
        }
        else if ((m_nPreKey + m_nCurKey)%'W' == 0)
        {
            m_pPrincipalPlane->Control(UP);
        }
        else if ((m_nPreKey + m_nCurKey)%'S' == 0)
        {
            m_pPrincipalPlane->Control(DOWN);
        }
        else if ((m_nPreKey + m_nCurKey) == ('A' + 'W'))
        {
            m_pPrincipalPlane->Control(LEFT_UP);

        }
        else if ((m_nPreKey + m_nCurKey) == ('A' + 'S'))
        {
            m_pPrincipalPlane->Control(LEFT_DOWN);

        }
        else if ((m_nPreKey + m_nCurKey) == ('D' + 'W'))
        {
            m_pPrincipalPlane->Control(RIGHT_UP);

        }
        else if ((m_nPreKey + m_nCurKey) == ('D' + 'S'))
        {
            m_pPrincipalPlane->Control(RIGHT_DOWN);

        }
        break;
    case 'J':
    case 'Z':
        m_pPrincipalPlane->Control(FIRE);
        break;
    case '1':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO0);
        break;
    case '2':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO1);
        break;
    case '3':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO2);
        break;
    case '4':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO3);
        break;
    case '5':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO4);
        break;
    case '6':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO5);
        break;
    case '7':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAMMO6);
        break;
    case 'Q':
        m_pPrincipalPlane->SetBulletType(emBulletTypeAmmoSB);
        break;
    case VK_SPACE:
    case 'K':
    case 'X':
        m_pPrincipalPlane->Control(FIREALL);
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
                m_pPrincipalPlane->Control(LEFT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'D' == 0)
            {
                m_pPrincipalPlane->Control(RIGHT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'W' == 0)
            {
                m_pPrincipalPlane->Control(UP);
            }
            else if ( (m_nPreKey + m_nCurKey) % 'S' == 0)
            {
                m_pPrincipalPlane->Control(DOWN);
            }
        }
        else
        {
            m_nCurKey = 0;
            m_pPrincipalPlane->Control(STOP_MOVE);
        }
    }
    else if (nKeyCode == m_nPreKey)
    {
        if (m_nCurKey)
        {
            m_nPreKey = 0;
            if ((m_nPreKey + m_nCurKey) % 'A' ==0)
            {
                m_pPrincipalPlane->Control(LEFT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'D' == 0)
            {
                m_pPrincipalPlane->Control(RIGHT);
            }
            else if ((m_nPreKey + m_nCurKey) % 'W' == 0)
            {
                m_pPrincipalPlane->Control(UP);
            }
            else if ( (m_nPreKey + m_nCurKey) % 'S' == 0)
            {
                m_pPrincipalPlane->Control(DOWN);
            }
        }
        else
        {
            m_nPreKey = 0;
            m_pPrincipalPlane->Control(STOP_MOVE);
        }
    }
    else if ( nKeyCode == 'J' || nKeyCode == 'Z')
    {
        m_pPrincipalPlane->Control(STOP_FIRE);
    }
}
