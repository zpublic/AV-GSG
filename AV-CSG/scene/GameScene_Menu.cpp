#include "stdafx.h"
#include "GameScene_Menu.h"
#include "control\stage_player\GameStagePlayer.h"
#include "GameScene_Play.h"
#include "control\generate\EnemyGenerate.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\xml_parser\PlaneXMLParser.h"

GameScene_Menu::GameScene_Menu(CMenuBase* pMenu)
    : m_pMenu(pMenu)
    , m_PictureBackgroud(NULL)
{
    m_PictureBackgroud = CPicturePool::GetInstance()->GetPicture(pMenu->GetBackgroudImage());
    ///> 默认指向菜单第一项
    m_nCurPos   = 0;
}

GameScene_Menu::~GameScene_Menu()
{

}

void GameScene_Menu::Update()
{
    ///> 暂定为从上到下一列菜单
    ///> 固接受 上、下、确定（开火）三个按键消息
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
    ///> 先画背景（如果需要的话）
    if (m_PictureBackgroud)
    {
        m_PictureBackgroud->ImmediateDrawBitmap(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }

    ///> 再画所有菜单项（不超过屏幕（翻页/滚动处理？））

    ///> 最后加亮当前光标所在菜单项
}

void GameScene_Menu::Up()
{
    if (m_nCurPos > 0)
    {
        m_nCurPos--;
    }
}

void GameScene_Menu::Down()
{
    if (m_pMenu && m_nCurPos < m_pMenu->GetMenuSize() - 1)
    {
        m_nCurPos++;
    }
}

void GameScene_Menu::Click()
{
    if (m_pMenu && m_nCurPos < m_pMenu->GetMenuSize())
    {
        m_pMenu->OnClick(m_nCurPos);
    }
}
