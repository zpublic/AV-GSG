#ifndef GAME_STAGE_PLAGER
#define GAME_STAGE_PLAGER

#include "unit\GameDef.h"
#include "control\xml_parser\StageXMLParser.h"
#include <string>

#define FastenFrameNum_Play 60

class CGameStagePlayer
{
public:
    virtual ~CGameStagePlayer();

    static CGameStagePlayer& GetInstance();

    bool Stage(const CStageXMLParse* pStage);
    GameStagePlayStatus PresentStatus() const;
    const CStageXMLStage* PresentObject() const;

    void Updata(int nEnemyNumber);

    void NextStage();

    long Stopwatch() const;

private:
    CGameStagePlayer(CGameStagePlayer&);
    CGameStagePlayer& operator = (CGameStagePlayer&);

    static CGameStagePlayer m_StagePlayer;
    GameStagePlayType m_emType;
    GameStagePlayStatus m_emStatus;
    long m_lnFrame;
    long m_lnStopwatch;
    long m_lnEnemyNumber;
    long m_lnDeadEnemy;
    CGameStagePlayer();
    const CStageXMLStage* m_pStage;
    MapStageList::const_iterator m_StageBegin;
    MapStageList::const_iterator m_StageEnd;
};

#endif