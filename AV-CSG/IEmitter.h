#pragma once
#include "GameDef.h"

///> ×Óµ¯·¢ÉäÆ÷
class IEmitter
{
public:
    IEmitter(void) {};
    virtual ~IEmitter(void) {};

public:
    virtual void Emit(int nPosX, int nPosY, BulletType bulletType) = 0;
};

