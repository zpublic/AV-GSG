#pragma once

#include "IEmitter.h"

///> 直线子弹发射器
class CLineEmitter : public IEmitter
{
public:
    CLineEmitter(void);
    virtual ~CLineEmitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);

    void SetParam(
        bool bFriend,
        int nPower,
        int nSpeed,
        float fAngle);

protected:
    bool m_bFriend;
    int m_nPower;
    int m_nSpeed;
    float m_fAngle;
};

