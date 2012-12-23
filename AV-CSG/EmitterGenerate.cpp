#include "stdafx.h"
#include "EmitterGenerate.h"
#include "LineEmitter.h"

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
    switch (nType)
    {
    case 1:
        CLineEmitter* pEmitter = new CLineEmitter();
        pEmitter->SetParam(bFriend, nPower, nSpeed, fAngle);
        pIEmitter = static_cast<IEmitter *>(pEmitter);
    }
    return pIEmitter;
}
