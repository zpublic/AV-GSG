#pragma once
#include "GameDef.h"

///> ×Óµ¯·¢ÉäÆ÷
class IEmitter
{
public:
    IEmitter(void) : m_fFireTimeMax(1.0f) {};
    virtual ~IEmitter(void) {};

public:
    virtual void Emit(int nPosX, int nPosY, BulletType bulletType) = 0;

    float GetFireTimeMax()
    {
        return m_fFireTimeMax;
    }
    void SetFireTimeMax(float t)
    {
        m_fFireTimeMax = t;
    }

protected:
    float m_fFireTimeMax;
};

