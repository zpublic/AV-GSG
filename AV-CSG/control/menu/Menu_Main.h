#pragma once
#include "MenuBase.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\xml_parser\PlaneXMLParser.h"
#include "control\stage_player\GameStagePlayer.h"
#include "control\generate\EnemyGenerate.h"
#include "scene\GameScene_Play.h"
#include "scene\GameScene_AuthorList.h"
#include "scene\GameScene_ScoreList.h"
#include "control\game\GameFrame.h"

class CMenu_Main : public CMenuBase
{
public:
    CMenu_Main()
    {
        AddMenuItem(L"��ʼ��Ϸ");
        AddMenuItem(L"�÷ְ�");
        AddMenuItem(L"���ط���");
        AddMenuItem(L"�˳���Ϸ");
    }

    virtual ~CMenu_Main()
    {
    }

    virtual void OnClick(int iPos)
    {
        switch (iPos)
        {
        case 0:
            ClickBegin();
            break;
        case 1:
            SceneEngine_->Push(new GameScene_ScoreList);
            break;
        case 2:
            SceneEngine_->Push(new GameScene_AuthorList);
            break;
        case 3:
            ClickExit();
            break;
        default:
            break;
        }
    }

private:
    void ClickBegin()
    {
        //����������
        ClearFrame();
        //������Ϸ���̳���
        SceneEngine_->Push(new GameScene_Play);
        srand((unsigned)time(0));
        Player_->gamestatus_.ResetGameStatus();
        CSelfPlane::GetInstance()->InitGame(CPlaneXMLParse::GetInstance().GetSelfPlane("SuperSpeedTransportation"));
    }

    void ClickExit()
    {
        SceneEngine_->PopAll();
    }
};
