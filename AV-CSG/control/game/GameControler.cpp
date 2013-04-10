#include "StdAfx.h"
#include "control\game\GameControler.h"
#include "control\stage_player\GameStagePlayer.h"
#include "control\xml_parser\xmlresource.h"
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

void CGameControler::LoadXML(const std::string& strPath)
{
    CXMLResource::Instance()->LoadXML(strPath);
    CGameStagePlayer::GetInstance().LoadStageXML(&CStageXMLParse::GetInstance());
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
