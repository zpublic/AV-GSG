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

    bool LoadStageXML(const CStageXMLParse* pStage);

    int StageCount() const;

    int FirstStageId() const;

    CStageXMLStage* GetStage(int nId);

private:
    CGameStagePlayer(CGameStagePlayer&);
    CGameStagePlayer& operator = (CGameStagePlayer&);
    CGameStagePlayer();
    const CStageXMLParse* m_pStage;
    static CGameStagePlayer m_StagePlayer;
};

#endif