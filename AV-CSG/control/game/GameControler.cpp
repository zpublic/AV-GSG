#include "StdAfx.h"
#include "control\game\GameControler.h"
#include "control\stage_player\GameStagePlayer.h"
#include "control\xml_parser\PlaneXMLParser.h"
#include "control\xml_parser\EmitterXMLParser.h"
#include "control\xml_parser\BlastXMLParser.h"
#include "control\xml_parser\WeaponXMLParser.h"
#include "control\xml_parser\BulletXMLParser.h"
#include "scene\GameScene_Menu.h"
#include "data\resourcedata\PicturePool.h"

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
    m_Menu.SetBackgroudImage("menubackgroud");
}

void CGameControler::CreateGame()
{
    _InitalizeMenu();
    //ÔØÈëÓÎÏ·²Ëµ¥
    SceneEngine_->Push(new GameScene_Menu(&m_Menu));
}

bool CGameControler::UpdateScence()
{
    DWORD dwElapsed = ::GetTickCount() - m_dwLastTime;
    if (dwElapsed < MSPERFRAME)
    {
        Sleep((DWORD)MSPERFRAME - dwElapsed);
    }
    m_dwLastTime = ::GetTickCount();

    if (!SceneEngine_->Update())
        return false;
    SceneEngine_->Output();
    return true;
}
