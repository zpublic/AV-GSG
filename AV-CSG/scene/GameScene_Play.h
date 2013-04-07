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
    ///> ��ǰ�ؿ����зɻ�
    int m_nEnemyPlane;
    ///> �������ɻ�
    int m_nDeadPlane;
    ///> ֡��
    long m_lnFrame;
    ///> ����
    long m_lnSecond;
    //��ǰ�ؿ�
    CStageXMLStage* m_pStage;
};
