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
    EmitterType strType,
    bool bFriend,
    int nPower,
    int nSpeed,
    float fAngle )
{
    IEmitter* pIEmitter = NULL;
    if (LINE_EMITTER == strType)
    {
        CLineEmitter* pEmitter = new CLineEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed, fAngle);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (LINE3_EMITTER == strType)
    {
        CLine3Emitter* pEmitter = new CLine3Emitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }

    else if (LINE8_EMITTER == strType)
    {
        CLine8Emitter* pEmitter = new CLine8Emitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (CURVE_EMITTER == strType)
    {
        CCurveEmitter* pEmitter = new CCurveEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed, fAngle);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (BIGBULLET_EMITTER == strType)
    {
        static CBigBulletEmitter BigBulletEmitter;
        pIEmitter = static_cast<IEmitter *>(&BigBulletEmitter);
    }
    else if (SPIN_EMITTER == strType)
    {
        CSpinEmitter* pEmitter = new CSpinEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (AIM_EMITTER == strType)
    {
        CAimEmitter* pEmitter = new CAimEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (TRACK_EMITTER == strType)
    {
        CTrackEmitter* pEmitter = new CTrackEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }

    return pIEmitter;
}

IEmitter* CEmitterGenerate::GenerateEnemyEmitter(
    EmitterType strType,
    bool bFriend,
    int nPower,
    int nSpeed,
    float fAngle)
{
    return Generate(strType, bFriend, nPower, nSpeed, fAngle);
}

IEmitter* CEmitterGenerate::SelectSelfEmitter( int nLevel )
{
    IEmitter* piEmitter = NULL;
    switch (nLevel)
    {
    case 1:
        piEmitter = CEmitterGenerate::Generate(
            LINE_EMITTER, true,
            3, 200, float(PI * 3 / 2.0));
        break;
    case 2:
        piEmitter = CEmitterGenerate::Generate(
            LINE3_EMITTER, true,
            3, 200, 0);
        break;
    case 3:
        piEmitter = CEmitterGenerate::Generate(
            LINE3_EMITTER, true,
            3, 200, 0);
        break;
    case 4:
        piEmitter = CEmitterGenerate::Generate(
            LINE3_EMITTER, true,
            10, 800, 0);
        break;
    default:
        piEmitter = CEmitterGenerate::Generate(
            LINE_EMITTER, true,
            3, 200, float(PI * 3 / 2.0));
        break;
    }
    return piEmitter;
}
