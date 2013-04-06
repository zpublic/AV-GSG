#pragma once

#include "IEmitter.h"

class CLine3Emitter : public IEmitter
{
public:
    CLine3Emitter(void);
    virtual ~CLine3Emitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);

    void SetParam(
        bool bFriend,
        int nPower,
        int nSpeed,
        float fAngle);

private:
    bool m_bFriend;
    int m_nPower;
    int m_nSpeed;
    float m_fAngle;
};
