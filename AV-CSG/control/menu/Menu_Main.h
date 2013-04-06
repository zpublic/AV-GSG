#pragma once
#include "MenuBase.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\xml_parser\PlaneXMLParser.h"
#include "control\stage_player\GameStagePlayer.h"
#include "control\generate\EnemyGenerate.h"
#include "scene\GameScene_Play.h"
#include "scene\GameScene_AuthorList.h"
#include "scene\GameScene_ScoreList.h"

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
        //初始化关卡
        CGameStagePlayer::GetInstance().FirstStage();
        //载入游戏流程场景
        if (CGameStagePlayer::GetInstance().PresentObject())
        {
            SceneEngine_->Push(new GameScene_Play(
                CGameStagePlayer::GetInstance().PresentObject()->GetMap()));

            srand((unsigned)time(0));
            Player_->gamestatus_.ResetGameStatus();
            CEnemyGenerate::ClearEnemy();
            CEnemyGenerate::IniEnemy(CGameStagePlayer::GetInstance().PresentObject());
            CSelfPlane::GetInstance()->InitGame(CPlaneXMLParse::GetInstance().GetSelfPlane("SuperSpeedTransportation"));
        }
    }

    void ClickExit()
    {
        SceneEngine_->PopAll();
    }
};
