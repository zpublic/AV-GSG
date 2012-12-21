#pragma once
#include "Sprite.h"
#include "Picture.h"

/*
*	add by hels	2012-5-11
*	设计子弹基类，划分为我方子弹和敌方子弹，子弹主要是区分类型和行为。这里用到了一个方法，
*	这个方法是参考别人的设计，预先将所有子弹图片全部加载起来，理由我想到两个：1.本身从磁盘中加载图片到内存中相对是耗时的，
*	如果能提前加载会方便很多。2.子弹图片都较小，一直存在于内存中可以接受
*/

class CBullet : public CSprite
{
public:
	CBullet(int x, int y);
	virtual ~CBullet(void);

	//渲染
	virtual void Render(HDC hdc) = 0;

	//更新精灵函数（位置，角度等属性）
	virtual void Update() = 0;

	static void LoadBullet();
	static void FreeBullet();
protected:
	int					m_nPower;//火力
	BulletType			m_nBulletType;
	static CPicture *	m_pPictureAmmo[8];
};

