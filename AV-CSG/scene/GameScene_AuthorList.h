#pragma once
#include "GameScene.h"

class GameScene_AuthorList : public GameScene
{
public:
    GameScene_AuthorList();
    virtual ~GameScene_AuthorList();

    virtual void Update();
    virtual void Output();
    virtual void Reset();
};
