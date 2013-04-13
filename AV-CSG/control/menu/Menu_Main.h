#pragma once
#include "MenuBase.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\xml_parser\PlaneXMLParser.h"
#include "control\stage_player\GameStagePlayer.h"
#include "control\generate\EnemyGenerate.h"
#include "scene\GameScene_Play.h"
#include "scene\GameScene_AuthorList.h"
#include "scene\GameScene_ScoreList.h"
#include "scene\GameScene_Chat.h"
#include "control\game\GameFrame.h"

class CMenu_Main : public CMenuBase
{
public:
    CMenu_Main()
    {
        AddMenuItem(L"开始游戏");
        AddMenuItem(L"得分榜");
        AddMenuItem(L"神秘房间");
        AddMenuItem(L"退出游戏");
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
        //清理精灵链表
        ClearFrame();
        //载入游戏流程场景
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
