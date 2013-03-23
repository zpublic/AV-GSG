#ifndef GAME_STAGE_PLAGER
#define GAME_STAGE_PLAGER

#include "GameDef.h"
#include "StageXMLParser.h"
#include <string>

#define FastenFrameNum_Play 60

class CGameStagePlayer
{
public:
    CGameStagePlayer();
    virtual ~CGameStagePlayer();

    bool Stage(const CStageXMLParse* pStage);
    GameStagePlayStatus PresentStatus() const;
    const CStageXMLStage* PresentObject() const;

    void Updata(int nEnemyNumber);

    void NextStage();

    long Stopwatch() const;

private:
    CGameStagePlayer(CGameStagePlayer&);
    CGameStagePlayer& operator = (CGameStagePlayer&);

    GameStagePlayType m_emType;
    GameStagePlayStatus m_emStatus;
    long m_lnFrame;
    long m_lnStopwatch;
    long m_lnEnemyNumber;
    long m_lnDeadEnemy;
    const CStageXMLStage* m_pStage;
    MapStageList::const_iterator m_StageBegin;
    MapStageList::const_iterator m_StageEnd;
};

#endif