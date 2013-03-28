#pragma once

#include "IEmitter.h"

class CSpinEmitter : public IEmitter
{
public:
    CSpinEmitter(void);
    virtual ~CSpinEmitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);

    void SetParam(
        bool bFriend,
        int nPower,
        int nSpeed);

private:
    bool m_bFriend;
    int m_nPower;
    int m_nSpeed;
    int m_nAngle;
};

