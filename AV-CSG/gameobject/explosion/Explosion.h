#pragma once
#include "gameobject\sprite\Sprite.h"
#include "control\xml_parser\BulletXMLParser.h"

// 爆炸效果类，主要是根据给定的坐标和类型，显示爆炸的效果就可。
class CExplosion : CSprite
{
public:
    CExplosion(int x, int y, BlastType blastType);
    virtual ~CExplosion(void);

    virtual void Update();
    virtual void Render(HDC hDC);
private:
    const CBulletXMLObject* m_Blast;
    BlastType m_emBlastType;
};
