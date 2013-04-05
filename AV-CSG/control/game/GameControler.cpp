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
#include "..\xml_parser\PlaneXMLParser.h"
#include "..\xml_parser\EmitterXMLParser.h"


HDC         g_hMemDC = NULL;
HDC         g_hWndDC = NULL;
HBITMAP     g_hMemBitmap = NULL;

CGameControler::CGameControler()
{
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
    if (g_hMemBitmap)
    {
        DeleteObject(g_hMemBitmap);
    }
}

void CGameControler::_InitalizeMenu()
{
    m_Menu.SetBackgroudImage(L"Resource\\MenuBackgroud.bmp");
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
