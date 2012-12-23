#pragma once

#include "IEmitter.h"

class CLine8Emitter : public IEmitter
{
public:
    CLine8Emitter(void);
    virtual ~CLine8Emitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);

    void SetParam(
        bool bFriend,
        int nPower,
        int nSpeed);

private:
    bool m_bFriend;
    int m_nPower;
    int m_nSpeed;
};

