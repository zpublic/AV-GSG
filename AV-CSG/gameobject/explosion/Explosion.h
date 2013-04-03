#pragma once
#include "gameobject\sprite\Sprite.h"
#include "control\xml_parser\BlastXMLParser.h"

// 爆炸效果类，主要是根据给定的坐标和类型，显示爆炸的效果就可。
class CExplosion : CSprite
{
public:
    CExplosion(int x, int y, BlastType blastType);
    virtual ~CExplosion(void);

    virtual void Update();
    virtual void Render(HDC hDC);
private:
    const CBlastXMLObject* m_Blast;
    BlastType m_emBlastType;
};
