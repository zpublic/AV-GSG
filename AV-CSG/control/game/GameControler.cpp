#include "StdAfx.h"
#include "control/game/GameControler.h"
#include "gameobject\sprite\Sprite.h"
#include "gameobject\plane\SelfPlane.h"
#include "gameobject\bullet\Bullet.h"
#include "gameobject\plane\EnemyPlane.h"
#include "gameobject\explosion\Explosion.h"
#include "GameFrame.h"
#include "control\generate\EnemyGenerate.h"
#include "GameStatus.h"
#include "scene\GameScene_Play.h"
#include "scene\GameScene_FixedScene.h"
#include "scene\GameScene_Menu.h"
#include "control\stage_player\GameStagePlayer.h"


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
    if (m_hMapDC)
    {
        DeleteDC(m_hMapDC);
    }
    if (m_hBitmapMap) DeleteObject(m_hBitmapMap);
    if (m_hMemBitmap) DeleteObject(m_hMemBitmap);
}

void CGameControler::GameOver()
{
    //弹出游戏流程场景
    SceneEngine_->Pop();
    //载入游戏结束画面
    SceneEngine_->Push(new GameScene_FixedScene(
        _T("Resource\\gameover.bmp")));
    TCHAR szOut[100] = {0};
    wsprintf(szOut, L"最终得分：%d", Player_->gamestatus_.GetScore());
    ::MessageBox(0, szOut, L"", 0);
}

void CGameControler::_InitalizeMenu()
{
    m_Menu.SetBackgroudImage(L"Resource\\MenuBackgroud.bmp");
}

void CGameControler::GameReady()
{
    //载入游戏流程场景
    SceneEngine_->Push(new GameScene_Play(
        CA2W(CGameStagePlayer::GetInstance().PresentObject()->GetMap().c_str())));
    m_dwLastTime = GetTickCount();
    srand((unsigned)time(0));
    Player_->gamestatus_.ResetGameStatus();
    CEnemyGenerate::ClearEnemy();
    CEnemyGenerate::IniEnemy(CGameStagePlayer::GetInstance().PresentObject());
    m_pSelfPlane->InitGame(CPlaneXMLParse::GetInstance().GetSelfPlane("SuperSpeedTransportation"));
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
    _InitalizeMenu();
    //载入游戏菜单
    SceneEngine_->Push(new GameScene_Menu(&m_Menu));
    CGameStatus::ReadyingGame();
}

void CGameControler::UpdateScence()
{
    if (CGameStatus::GetGameOver())
    {
        GameOver();
        CGameStatus::SetGameOvered();
        Sleep(100);
        return;
    }
    if (CGameStatus::GetGameReady())
    {
        GameReady();
        CGameStatus::StartGame();
        Sleep(100);
        return;
    }
    if (CGameStatus::GetGameReadying() || CGameStatus::GetGameOvered())
    {
        SceneEngine_->Update();
        SceneEngine_->Output();
        return;
    }

    DWORD dwElapsed = ::GetTickCount() - m_dwLastTime;
    if (dwElapsed < MSPERFRAME)
    {
        Sleep((DWORD)MSPERFRAME - dwElapsed);
    }
    m_dwLastTime = ::GetTickCount();

    if (CGameStagePlayer::GetInstance().PresentStatus() == emGameStagePlayStatusNone)
    {
        CGameStagePlayer::GetInstance().NextStage();
        if (CGameStagePlayer::GetInstance().PresentStatus() == emGameStagePlayStatusWin)
        {
            //完成所有关卡 胜利
            //弹出游戏控制器
            SceneEngine_->Pop();
            //载入胜利场景
            SceneEngine_->Push(new GameScene_FixedScene(
                _T("Resource\\AmmoSb.bmp")));
        }
        else
        {
            if (CGameStagePlayer::GetInstance().PresentObject())
            {
                CEnemyGenerate::ClearEnemy();
                CEnemyGenerate::IniEnemy(CGameStagePlayer::GetInstance().PresentObject());
                SceneEngine_->Pop();
                SceneEngine_->Push(new GameScene_Play(
                    CA2W(CGameStagePlayer::GetInstance().PresentObject()->GetMap().c_str())));
            }
        }
    }
    SceneEngine_->Update();
    SceneEngine_->Output();
}
