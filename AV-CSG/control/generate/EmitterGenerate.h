#pragma once

#include "gameobject\emitter\IEmitter.h"
#include <string>

typedef std::string EmitterType;

///> ·¢ÉäÆ÷Éú³É
class CEmitterGenerate
{
public:
    CEmitterGenerate(void);
    ~CEmitterGenerate(void);

    static IEmitter* Generate(
        EmitterType strType,
        bool bFriend,
        int nPower,
        int nSpeed,
        float fAngle);

    static IEmitter* GenerateEnemyEmitter(
        EmitterType strType,
        bool bFriend,
        int nPower,
        int nSpeed,
        float fAngle);

    static IEmitter* SelectSelfEmitter( int nLevel);
};

