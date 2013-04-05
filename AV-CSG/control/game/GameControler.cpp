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
<<<<<<< HEAD
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    if (m_hMemBitmap) DeleteObject(m_hMemBitmap);
}

void CGameControler::GameOver()
{
    SceneEngine_->PopAll();
    SceneEngine_->Push(new GameScene_FixedScene(
        _T("Resource\\gameover.bmp")));

    int nMaxScore = Player_->gamestatus_.GetScore();
    if(Player_->gamestatus_.SetMaxScore(nMaxScore))
    {
        Player_->savedata_.Save();
    }
    
    TCHAR szOut[150] = {0};
    wsprintf(szOut, L"本场最终得分：%d\n玩家最高得分: %d,    再接再厉", nMaxScore, Player_->gamestatus_.GetMaxScore());
    ::MessageBox(0, szOut, L"", 0);
=======
>>>>>>> 3017b4f28ace9898212b0a3bdd12fcea4480d481
}

void CGameControler::_InitalizeMenu()
{
    m_Menu.SetBackgroudImage(L"Resource\\MenuBackgroud.bmp");
}

void CGameControler::CreateGame()
{
    _InitalizeMenu();
    //载入游戏菜单
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
