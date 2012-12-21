#pragma once
/*
*	add by hels 2012-5-12
*	具体子弹类（敌方子弹）,实现子弹逻辑以及显示。
*/

#include "Bullet.h"

class CEnemyBullet : public CBullet
{
public:
	CEnemyBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~CEnemyBullet(void);

	//渲染
	void Render(HDC hDC);

	//更新精灵函数（位置，角度等属性）
	void Update();

	bool IsVisible();
};

