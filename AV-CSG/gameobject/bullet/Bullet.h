#pragma once
#include "gameobject\sprite\Sprite.h"
#include "control/xml_parser/BulletXMLParser.h"

///> �ӵ����࣬����Ϊ�ҷ��ӵ��͵з��ӵ�
class CBullet : public CSprite
{
public:
    CBullet(
        int x, int y,
        bool bFriend,
        BulletType bulletType,
        float fAngle);
    virtual ~CBullet(void);

    virtual bool IsVisible();
    virtual void Render(HDC hDC);
    virtual void Update();
protected:
    int                       m_nPower;           //����
    const CBulletXMLObject* m_Bullet;
    BulletType                m_BulletType;      //�ӵ�����
    bool                      m_bFriend;          //����
    int                       m_nSpeed;           //�ӵ��ٶ�
    float                     m_fAngle;           //�Ƕ�
};

