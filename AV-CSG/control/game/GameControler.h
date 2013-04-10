#pragma once

#include "control\menu\Menu_Main.h"

///> 游戏控制器类，主导整个游戏的运行过程，提供信息以便更新各精灵
class CGameControler
{
public:
    CGameControler();
    ~CGameControler();

    //更新游戏场景
    bool UpdateScence();

    void SetWndDC(HDC hDC);
    void LoadXML(const std::string& strPath);
    void SetPlaneXML(const std::string& strPath);
    void SetBulletXML(const std::string& strPath);
    void SetBlastXML(const std::string& strPath);
    void SetEmitterXML(const std::string& strPath);
    void SetWeaponXML(const std::string& strPath);

    void CreateGame();

    void Exit();
private:

    void _InitalizeMenu();

    DWORD       m_dwLastTime;     //上次绘图时间
    CMenu_Main  m_Menu;           //菜单
};

