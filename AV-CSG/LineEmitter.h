#pragma once

#include "IEmitter.h"

///> 直线子弹发射器
class CLineEmitter : public IEmitter
{
public:
    CLineEmitter(void);
    virtual ~CLineEmitter(void);

    virtual void Emit(int nPosX, int nPosY);

    void SetParam(
        bool bFriend,
        int nPower,
        int nSpeed,
        BulletType bulletType,
        float fAngle);

private:
    bool m_bFriend;
    int m_nPower;
    int m_nSpeed;
    BulletType m_bulletType;
    float m_fAngle;
};

