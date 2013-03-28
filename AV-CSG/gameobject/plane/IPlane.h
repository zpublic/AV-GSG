#pragma once
#include "gameobject\sprite\Sprite.h"
#include "gameobject\emitter\IEmitter.h"

typedef std::string PlaneType;

///> �ɻ������
class PlaneBase : public CSprite
{
public:
    PlaneBase(int x, int y, IEmitter* piEmitter= NULL)
        : CSprite(x, y)
        , m_nHP(0)
        , m_piEmitter(piEmitter)
    {
    }
    virtual ~PlaneBase()
    {
        delete m_piEmitter;
    }

    //��ײ���
    virtual bool CheckCollision(
        int x, int y,
        int width, int height,
        int power) = 0;

protected:
    int         m_nHP;      ///> Ѫ��
    IEmitter*   m_piEmitter; ///> �ӵ�������
};