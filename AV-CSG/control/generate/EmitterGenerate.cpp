#include "stdafx.h"
#include "EmitterGenerate.h"
#include "gameobject\emitter\LineEmitter.h"
#include "gameobject\emitter\Line3Emitter.h"
#include "gameobject\emitter\Line8Emitter.h"
#include "gameobject\emitter\CurveEmitter.h"
#include "gameobject\emitter\BigBulletEmitter.h"
#include "gameobject\emitter\SpinEmitter.h"
#include "gameobject\emitter\AimEmitter.h"
#include "gameobject\emitter\TrackEmitter.h"

CEmitterGenerate::CEmitterGenerate(void)
{
}

CEmitterGenerate::~CEmitterGenerate(void)
{
}

IEmitter* CEmitterGenerate::Generate(
    int nType,
    bool bFriend,
    int nPower,
    int nSpeed,
    float fAngle )
{
    IEmitter* pIEmitter = NULL;
    if (1 == nType)
    {
        CLineEmitter* pEmitter = new CLineEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed, fAngle);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (2 == nType)
    {
        CLine3Emitter* pEmitter = new CLine3Emitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }

    else if (3 == nType)
    {
        CLine8Emitter* pEmitter = new CLine8Emitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (4 == nType)
    {
        CCurveEmitter* pEmitter = new CCurveEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed, fAngle);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (5 == nType)
    {
        static CBigBulletEmitter BigBulletEmitter;
        pIEmitter = static_cast<IEmitter *>(&BigBulletEmitter);
    }
    else if (6 == nType)
    {
        CSpinEmitter* pEmitter = new CSpinEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (7 == nType)
    {
        CAimEmitter* pEmitter = new CAimEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (8 == nType)
    {
        CTrackEmitter* pEmitter = new CTrackEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }

    return pIEmitter;
}

IEmitter* CEmitterGenerate::GenerateEnemyEmitter()
{
    IEmitter* piEmitter = NULL;
    int nEmitterRandom = rand() % 100;
    if (nEmitterRandom < 5)
    {
        piEmitter = CEmitterGenerate::Generate(
            3, false,
            1, 200, 0);
    }
    else if (nEmitterRandom < 20)
    {
        piEmitter = CEmitterGenerate::Generate(
            4, false,
            1, 200, PI / 2.0);
    }
    else if (nEmitterRandom < 25)
    {
        piEmitter = CEmitterGenerate::Generate(
            6, false,
            1, 200, 0);
        piEmitter->SetFireTimeMax(0.1f);
    }
    else if (nEmitterRandom < 30)
    {
        piEmitter = CEmitterGenerate::Generate(
            7, false,
            1, 300, 0);
        piEmitter->SetFireTimeMax(0.3f);
    }
    else if (nEmitterRandom < 33)
    {
        piEmitter = CEmitterGenerate::Generate(
            8, false,
            1, 300, 0);
        piEmitter->SetFireTimeMax(2.0f);
    }
    else
    {
        piEmitter = CEmitterGenerate::Generate(
            1, false,
            5, 220, PI / 2.0);
    }
    return piEmitter;
}

IEmitter* CEmitterGenerate::SelectSelfEmitter( int nLevel )
{
    IEmitter* piEmitter = NULL;
    switch (nLevel)
    {
    case 1:
        piEmitter = CEmitterGenerate::Generate(
            1, true,
            3, 200, float(PI * 3 / 2.0));
        break;
    case 2:
        piEmitter = CEmitterGenerate::Generate(
            2, true,
            3, 200, 0);
        break;
    case 3:
        piEmitter = CEmitterGenerate::Generate(
            3, true,
            3, 200, 0);
        break;
    case 4:
        piEmitter = CEmitterGenerate::Generate(
            8, true,
            10, 800, 0);
        break;
    default:
        piEmitter = CEmitterGenerate::Generate(
            1, true,
            3, 200, float(PI * 3 / 2.0));
        break;
    }
    return piEmitter;
}
