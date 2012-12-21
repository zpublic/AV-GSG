#pragma once
/*
*	add by hels	2012-5-13
*	敌机类，记录生命，提供渲染，进行碰撞检测，记录子弹类型等。
*/
#include "IPlane.h"
#include "Picture.h"

class CEnemyPlane : public PlaneBase
{
public:
	CEnemyPlane(EnemyType enemyType);
	virtual ~CEnemyPlane(void);

	//碰撞检测
	bool CheckCollision(int x, int y, int width, int height, int power);

	static void CreateEnemy();

	//渲染
	void Render(HDC hDC);

	//更新精灵函数（位置，角度等属性）
	void Update();

	//加载飞机图片
	static void LoadBimap();
	static void FreeBitmap();

	bool IsVisible();

	static CEnemyPlane *spEnemyHead;
	CEnemyPlane * m_pEmnemyNext;

private:
	static CPicture * spPictureEnemy[6];
	static int snEnemyCount;
	static float sfLastCreateTime;
	float	m_fFireTime;
	int		m_nHP;
	EnemyType	m_nEnemyType;
};

