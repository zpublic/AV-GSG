#pragma once

#include "StageXMLParser.h"
#include "PlaneXMLParse.h"
#include "GameStagePlayer.h"

class CSelfPlane;

///> ��Ϸ�������࣬����������Ϸ�����й��̣��ṩ��Ϣ�Ա���¸�����
class CGameControler
{
public:
    CGameControler();
    ~CGameControler();

    //������Ϸ����
    void UpdateScence();

    //���̰�������
    void KeyDown(WPARAM nKeyCode);
    void KeyUp(WPARAM nKeyCode);

    void SetWndDC(HDC hDC);
    void SetStageXML(const std::string& strPath);
    void SetPlaneXML(const std::string& strPath);
    void SetExplosionXML(const std::string& strPath);

    void StartGame();

    void Exit();
private:
    //��ͼѭ����ͼ
    void CirculationMap();

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

    CSelfPlane *m_pSelfPlane;
};

