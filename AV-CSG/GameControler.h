#pragma once

#include "StageXMLParser.h"
#include "PlaneXMLParse.h"

class CSelfPlane;

///> 游戏控制器类，主导整个游戏的运行过程，提供信息以便更新各精灵
class CGameControler
{
public:
    CGameControler();
    ~CGameControler();

    //更新游戏场景
    void UpdateScence();

    //键盘按键处理
    void KeyDown(WPARAM nKeyCode);
    void KeyUp(WPARAM nKeyCode);

    void SetWndDC(HDC hDC);
    void SetStageXML(const std::string& strPath);
    void SetPlaneXML(const std::string& strPath);

    void StartGame();

    void Exit();
private:
    //地图循环贴图
    void CirculationMap();

    void GameOver();
    void GameReady();
    void ProcessInput();

    DWORD   m_dwLastTime;       //上次绘图时间
    HDC     m_hMemDC;
    HBITMAP m_hBitmapMap;
    HBITMAP m_hMemBitmap;
    HDC     m_hWndDC;
    HDC     m_hMapDC; 
    int     m_nY;               //记录地图被截取的宽度

    int     m_nPreKey;
    int     m_nCurKey;

    int     m_PresentStage;

    CSelfPlane *m_pSelfPlane;
};

