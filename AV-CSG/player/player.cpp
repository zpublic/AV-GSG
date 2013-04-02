#include "stdafx.h"
#include "player.h"

template<> Player* Singleton<Player>::m_pInst = NULL;

Player::Player()
{

}

Player::~Player()
{

}
