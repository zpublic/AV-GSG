#pragma once

#include "gameobject\emitter\IEmitter.h"

///> ����������
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

    static IEmitter* GenerateEnemyEmitter();

    static IEmitter* SelectSelfEmitter(int nLevel);
};

