#pragma once

#include "IEmitter.h"

class CBigBulletEmitter : public IEmitter
{
public:
    CBigBulletEmitter(void);
    virtual ~CBigBulletEmitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);
};

