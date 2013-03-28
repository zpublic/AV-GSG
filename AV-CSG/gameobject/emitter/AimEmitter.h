#pragma once

#include "IEmitter.h"

///> ��׼Ŀ��ķ�����
class CAimEmitter : public IEmitter
{
public:
    CAimEmitter(void);
    virtual ~CAimEmitter(void);

    virtual void Emit(int nPosX, int nPosY, BulletType bulletType);

    void SetParam(
        bool bFriend,
        int nPower,
        int nSpeed);

protected:
    bool m_bFriend;
    int m_nPower;
    int m_nSpeed;
};

