#pragma once
#include "LineEmitter.h"

///> S���ӵ�������
class CCurveEmitter : public CLineEmitter
{
public:
    CCurveEmitter(void);
    virtual ~CCurveEmitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);
};

