#pragma once
#include "GameScene.h"
#include "control\menu\MenuBase.h"
#include "data\resourcedata\Picture.h"

class GameScene_Menu : public GameScene
{
public:
    GameScene_Menu(CMenuBase* pMenu);
    virtual ~GameScene_Menu();

    virtual void Update();
    virtual void Output();

private:
    void Up();
    void Down();
    void Click();

private:
    ///> ��ǰ���λ��
    int             m_nCurPos;
    CMenuBase*      m_pMenu;
    CPicture m_PictureBackgroud;
};
