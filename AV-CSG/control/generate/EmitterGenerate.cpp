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

bool CEmitterGenerate::_IsEnemy(PlaneIEmitterType type)
{
    switch (type)
    {
    case IEMITTER_ENEMY:
        return true;
    case IEMITTER_SELF:
        return false;
    }
    return true;
}

IEmitter* CEmitterGenerate::Generate(
    EmitterType strType,
    bool bFriend,
    int nPower,
    int nSpeed,
    PlaneIEmitterType type)
{
    IEmitter* pIEmitter = NULL;
    if (LINE_EMITTER == strType)
    {
        CLineEmitter* pEmitter = new CLineEmitter();
        if (_IsEnemy(type))
        {
            pEmitter->SetParam(bFriend, nPower, nSpeed, 1.5);
        }
        else
        {
            pEmitter->SetParam(bFriend, nPower, nSpeed, float(PI * 3 / 2.0));
        }
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    else if (LINE3_EMITTER == strType)
    {
        CLine3Emitter* pEmitter = new CLine3Emitter();
        if (_IsEnemy(type))
        {
            pEmitter->SetParam(bFriend, nPower, nSpeed, float(0.3));
        }
        else
        {
            pEmitter->SetParam(bFriend, nPower, nSpeed, 1);
        }
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
        pEmitter->SetParam(bFriend, nPower, nSpeed, PI / 2.0);
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
        pIEmitter->SetFireTimeMax(0.1f);
    }
    else if (AIM_EMITTER == strType)
    {
        CAimEmitter* pEmitter = new CAimEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
        pIEmitter->SetFireTimeMax(0.3f);
    }
    else if (TRACK_EMITTER == strType)
    {
        CTrackEmitter* pEmitter = new CTrackEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
        pIEmitter->SetFireTimeMax(2.0f);
    }

    return pIEmitter;
}

IEmitter* CEmitterGenerate::GenerateEnemyEmitter(
    EmitterType strType,
    bool bFriend,
    int nPower,
    int nSpeed)
{
    return Generate(strType, bFriend, nPower, nSpeed, IEMITTER_ENEMY);
}

IEmitter* CEmitterGenerate::SelectSelfEmitter(
    EmitterType strType,
    bool bFriend,
    int nPower,
    int nSpeed)
{
    return CEmitterGenerate::Generate(strType, bFriend,nPower, nSpeed, IEMITTER_SELF);
}
