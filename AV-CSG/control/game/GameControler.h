#pragma once

#include "control/xml_parser/StageXMLParser.h"
#include "control/xml_parser/PlaneXMLParser.h"
#include "control/xml_parser/BlastXMLParser.h"
#include "control/xml_parser/EmitterXMLParser.h"
#include "control/xml_parser/WeaponXMLParser.h"
#include "control/stage_player/GameStagePlayer.h"
#include "control\menu\MenuBase.h"

class CSelfPlane;

///> 游戏控制器类，主导整个游戏的运行过程，提供信息以便更新各精灵
class CGameControler
{
public:
    CGameControler();
    ~CGameControler();

    //更新游戏场景
    void UpdateScence();

    void SetWndDC(HDC hDC);
    void SetStageXML(const std::string& strPath);
    void SetPlaneXML(const std::string& strPath);
    void SetBulletXML(const std::string& strPath);
    void SetBlastXML(const std::string& strPath);
    void SetEmitterXML(const std::string& strPath);
    void SetWeaponXML(const std::string& strPath);

    void StartGame();

    void Exit();
private:

    void _InitalizeMenu();
    void GameOver();
    void GameReady();

    DWORD   m_dwLastTime;       //上次绘图时间
    HBITMAP m_hBitmapMap;
    HBITMAP m_hMemBitmap;
    HDC     m_hMapDC; 
    int     m_nY;               //记录地图被截取的宽度

    int     m_nPreKey;
    int     m_nCurKey;

    int     m_PresentStage;

    CMenuBase m_Menu;           //菜单
    CSelfPlane *m_pSelfPlane;
};

