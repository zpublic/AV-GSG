#pragma once

#include "Bullet.h"

///> �����ӵ�
class CTrackBullet : public CBullet
{
public:
    CTrackBullet( 
        int x, int y,
        bool bFriend,
        BulletType bulletType,
        float fAngle);
    virtual ~CTrackBullet(void);

    virtual void Update();

private:
    bool m_bNeedTrack;
};
