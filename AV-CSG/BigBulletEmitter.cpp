#include "stdafx.h"
#include "BigBulletEmitter.h"
#include "BigBullet.h"

CBigBulletEmitter::CBigBulletEmitter(void)
{
}


CBigBulletEmitter::~CBigBulletEmitter(void)
{
}

void CBigBulletEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    new CBigBullet(0, SCREEN_HEIGHT / 2 - 320 /2);
    new CBigBullet(SCREEN_WIDTH/2 - 224 /2, SCREEN_HEIGHT / 2 - 320 /2);
    new CBigBullet(SCREEN_WIDTH - 224, SCREEN_HEIGHT / 2 - 320 /2);
}
