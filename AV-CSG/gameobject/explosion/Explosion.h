#pragma once
#include "gameobject\sprite\Sprite.h"
#include "control\xml_parser\BlastXMLParser.h"

// ��ըЧ���࣬��Ҫ�Ǹ��ݸ�������������ͣ���ʾ��ը��Ч���Ϳɡ�
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
