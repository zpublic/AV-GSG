#pragma once

#include "control/xml_parser/StageXMLParser.h"
#include "control/xml_parser/PlaneXMLParser.h"
#include "control/xml_parser/BlastXMLParser.h"
#include "control/xml_parser/EmitterXMLParser.h"
#include "control/xml_parser/WeaponXMLParser.h"
#include "control/stage_player/GameStagePlayer.h"
#include "control\menu\MenuBase.h"

class CSelfPlane;

///> ��Ϸ�������࣬����������Ϸ�����й��̣��ṩ��Ϣ�Ա���¸�����
class CGameControler
{
public:
    CGameControler();
    ~CGameControler();

    //������Ϸ����
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

    DWORD   m_dwLastTime;       //�ϴλ�ͼʱ��
    HBITMAP m_hBitmapMap;
    HBITMAP m_hMemBitmap;
    HDC     m_hMapDC; 
    int     m_nY;               //��¼��ͼ����ȡ�Ŀ��

    int     m_nPreKey;
    int     m_nCurKey;

    int     m_PresentStage;

    CMenuBase m_Menu;           //�˵�
    CSelfPlane *m_pSelfPlane;
};

