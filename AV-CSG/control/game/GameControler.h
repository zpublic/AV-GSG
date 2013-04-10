#pragma once

#include "control\menu\Menu_Main.h"

///> ��Ϸ�������࣬����������Ϸ�����й��̣��ṩ��Ϣ�Ա���¸�����
class CGameControler
{
public:
    CGameControler();
    ~CGameControler();

    //������Ϸ����
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

    DWORD       m_dwLastTime;     //�ϴλ�ͼʱ��
    CMenu_Main  m_Menu;           //�˵�
};

