#pragma once
#include "gameobject\sprite\Sprite.h"
#include "control\xml_parser\BulletXMLParser.h"

// ��ըЧ���࣬��Ҫ�Ǹ��ݸ�������������ͣ���ʾ��ը��Ч���Ϳɡ�
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
