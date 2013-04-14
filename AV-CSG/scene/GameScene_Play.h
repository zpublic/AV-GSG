#pragma once
#include "GameScene.h"
#include "control\stage_player\GameStagePlayer.h"
#include "data\resourcedata\Picture.h"

#define FastenFrameNum_Play 60

class GameScene_Play : public GameScene
{
public:
    GameScene_Play();
    virtual ~GameScene_Play();

    virtual void Update();
    virtual void Output();

private:
    void ControlSelfPlane();
    void CirculationMap();
    void ControlGameTiming();
    void TestGameOver();
    void UpdateScore();
    CPicture* m_Picture;
    int m_nY;
    int m_nPresentStage;
    ///> 当前关卡所有飞机
    int m_nEnemyPlane;
    ///> 已死亡飞机
    int m_nDeadPlane;
    ///> 帧数
    long m_lnFrame;
    ///> 秒数
    long m_lnSecond;
    //当前关卡
    CStageXMLStage* m_pStage;
    //是否有对话场景
    bool m_IsChat;
};
