#pragma once
#include "unit/Singleton.h"
#include "player_gamestatus.h"
#include "player_property.h"
#include "player_savedata.h"
#include "player_skill.h"

class Player : public Singleton<Player>
{
    friend class Singleton<Player>;
public:
    Player();
    ~Player();

private:

public:
    Player_GameStatus   gamestatus_;
    Player_Property     property_;
    Player_SaveData     savedata_;
    Player_Skill        skill_;
};

