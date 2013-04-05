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
    virtual void Reset();

private:
    void Up();
    void Down();
    void Click();

private:
    ///> 当前光标位置
    int             m_nCurPos;
    CMenuBase*      m_pMenu;
    CPicture* m_PictureBackgroud;
};
