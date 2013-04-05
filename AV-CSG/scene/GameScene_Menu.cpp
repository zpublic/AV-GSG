#include "stdafx.h"
#include "GameScene_Menu.h"
#include "control\game\GameStatus.h"

GameScene_Menu::GameScene_Menu(CMenuBase* pMenu)
    : m_pMenu(pMenu)
{
    m_PictureBackgroud.LoadBitmap(pMenu->GetBackgroudImage().c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);
    ///> Ĭ��ָ��˵���һ��
    m_nCurPos   = 0;
}

GameScene_Menu::~GameScene_Menu()
{

}

void GameScene_Menu::Update()
{
    ///> �ݶ�Ϊ���ϵ���һ�в˵�
    ///> �̽��� �ϡ��¡�ȷ������������������Ϣ
    if (InputEngine_->ClickUp())
    {
        Up();
    }
    else if (InputEngine_->ClickDown())
    {
        Down();
    }
    else if (InputEngine_->ClickOk())
    {
        Click();
    }
}

void GameScene_Menu::Output()
{
    ///> �Ȼ������������Ҫ�Ļ���
    m_PictureBackgroud.ImmediateDrawBitmap(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    ///> �ٻ����в˵����������Ļ����ҳ/������������

    ///> ��������ǰ������ڲ˵���
}

void GameScene_Menu::Up()
{
    if (m_pMenu && m_nCurPos < m_pMenu->GetMenuSize() - 1)
    {
        m_nCurPos++;
    }
}

void GameScene_Menu::Down()
{
    if (m_nCurPos > 0)
    {
        m_nCurPos--;
    }
}

void GameScene_Menu::Click()
{
    if (m_pMenu && m_nCurPos < m_pMenu->GetMenuSize() - 1)
    {
        m_pMenu->GetMenuItem(m_nCurPos)->OnClick();
    }
    CGameStatus::SetGameReady();
}

