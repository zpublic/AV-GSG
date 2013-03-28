#pragma once

///> ������Ľӿڶ���
class ISprite
{
public:
    ISprite() : pNext(NULL) {}
    virtual ~ISprite() {}

    //�жϾ����Ƿ�ɼ�
    virtual bool IsVisible() = 0;

    //��Ⱦ�������ƺ���
    virtual void Render(HDC hDC) = 0;

    //���¾��麯����λ�ã��Ƕȵ����ԣ�
    virtual void Update() = 0;

    ISprite* pNext;
};