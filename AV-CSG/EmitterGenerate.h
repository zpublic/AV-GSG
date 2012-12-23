#pragma once

#include "IEmitter.h"

///> ·¢ÉäÆ÷Éú³ÉÆ÷
class CEmitterGenerate
{
public:
    CEmitterGenerate(void);
    ~CEmitterGenerate(void);

    static IEmitter* Generate(
        int nType,
        bool bFriend,
        int nPower,
        int nSpeed,
        float fAngle);
};

