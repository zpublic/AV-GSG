#pragma once

#include "AimEmitter.h"

class CTrackEmitter : public CAimEmitter
{
public:
    CTrackEmitter(void);
    ~CTrackEmitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);
};

