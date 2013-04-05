#include "StdAfx.h"
#include "control/game/GameControler.h"
#include "gameobject\sprite\Sprite.h"
#include "gameobject\plane\SelfPlane.h"
#include "gameobject\bullet\Bullet.h"
#include "gameobject\plane\EnemyPlane.h"
#include "gameobject\explosion\Explosion.h"
#include "GameFrame.h"
#include "control\generate\EnemyGenerate.h"
#include "scene\GameScene_Play.h"
#include "scene\GameScene_FixedScene.h"
#include "scene\GameScene_Menu.h"
#include "control\stage_player\GameStagePlayer.h"


HDC         g_hMemDC = NULL;
HDC         g_hWndDC = NULL;

CGameControler::CGameControler()
{
    m_hBitmapMap = NULL;
    m_hMemBitmap = NULL;
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

void CGameControler::SetBlastXML(const std::string& strPath)
{
    CBlastXMLParse::Instance()->LoadXML(strPath);
}

void CGameControler::SetEmitterXML(const std::string& strPath)
{
    CEmitterXMLParse::Instance()->LoadXML(strPath);
}

void CGameControler::SetWeaponXML(const std::string& strPath)
{
    CWeaponXMLParse::Instance()->LoadXML(strPath);
}

void CGameControler::SetBulletXML(const std::string& strPath)
{
    CBulletXMLParse::GetInstance().LoadXML(strPath);
}

void CGameControler::Exit()
{
    CPicturePool::GetInstance()->FreeImage();
    if (g_hMemDC)
    {
        DeleteDC(g_hMemDC);
    }
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    if (m_hMemBitmap) DeleteObject(m_hMemBitmap);
}

void CGameControler::_InitalizeMenu()
{
    m_Menu.SetBackgroudImage(L"Resource\\MenuBackgroud.bmp");
}

void CGameControler::SetWndDC(HDC hDC)
{
    g_hWndDC = hDC;
    g_hMemDC = CreateCompatibleDC(hDC);

    if (m_hMemBitmap) DeleteObject(m_hBitmapMap);
    m_hMemBitmap = CreateCompatibleBitmap(hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
    SelectObject(g_hMemDC, m_hMemBitmap);
}

void CGameControler::CreateGame()
{
    _InitalizeMenu();
    //ÔØÈëÓÎÏ·²Ëµ¥
    SceneEngine_->Push(new GameScene_Menu(&m_Menu));
}

void CGameControler::UpdateScence()
{
    DWORD dwElapsed = ::GetTickCount() - m_dwLastTime;
    if (dwElapsed < MSPERFRAME)
    {
        Sleep((DWORD)MSPERFRAME - dwElapsed);
    }
    m_dwLastTime = ::GetTickCount();

    SceneEngine_->Update();
    SceneEngine_->Output();
}
