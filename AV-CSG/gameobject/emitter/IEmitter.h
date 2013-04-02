#pragma once
#include "unit\GameDef.h"

#define LINE_EMITTER "lineemitter"
#define LINE3_EMITTER "line3emitter"
#define LINE8_EMITTER "line8emitter"
#define AIM_EMITTER "aimemitter"
#define SPIN_EMITTER "spinemitter"
#define TRACK_EMITTER "trackemitter"
#define CURVE_EMITTER "curveemitter"
#define BIGBULLET_EMITTER "bigbulletemitter"

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

