#include "stdafx.h"
#include "EmitterGenerate.h"
#include "LineEmitter.h"
#include "Line3Emitter.h"
#include "Line8Emitter.h"
#include "CurveEmitter.h"
#include "BigBulletEmitter.h"
#include "SpinEmitter.h"

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

    return pIEmitter;
}
