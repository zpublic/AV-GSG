#pragma once
/*
*	add by hels	2012-5-10
*	精灵在场景中会有大小，位置。需要进行绘制，碰撞检测，需要知道是否可见（是否到屏幕外了）等等。
*	这里会考虑将所有的精灵组成链表，统一由static void FrameRender（）进行刷新，可以说这个函数是精灵的灵魂。
*	现在设计是基类，那么有些具体的功能就需要子类自行去实现一开始可能想得不全，后续可以补充接口
*/

#define PI	3.141592653f

//定义子弹类型
enum BulletType
{
	AMMO0 = 0,
	AMMO1,
	AMMO2,
	AMMO3,
	AMMO4,
	AMMO5,
	AMMO6,
	WHOLEFRIED
};

//定义动作类型
enum ActionType
{
	LEFT,
	DOWN,
	RIGHT,
	UP,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
	STOP_MOVE,
	FIRE,
	STOP_FIRE,
	FIREALL
};

//敌机类型
enum EnemyType
{
	ENEMY0 = 0,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4
};

//爆炸效果类型
enum BlastType
{
	BULLETBLAST,
	PLANEBLAST
};

enum GameStatus
{
    emGameStatusNone,       ///> 什么都不干
    emGameStatusReady,
    emGameStatusOver,
    emGameStatusPlaying,
};

class CSprite
{
public:
	//精灵位置，定义为图片左上角
	CSprite(int	x, int y);
	virtual ~CSprite(void);

	//刷新一帧画面
	static void FrameRender(HDC hDC);

	//统一更新帧数据
	static void FrameUpdate();
	
	//判断精灵是否可见
	virtual bool IsVisible();

	//渲染，即绘制函数
	virtual void Render(HDC hDC) = 0;

	//更新精灵函数（位置，角度等属性）
	virtual void Update() = 0;

	//以下为设置和获取位置函数
	int GetX(){ return m_nPosX; }
	int GetY(){ return m_nPosY; }
	void SetX(int x){ m_nPosX = x; }
	void SetY(int y){ m_nPosY = y; }
	
protected:
	int	m_nPosX;
	int m_nPosY;
	int m_nFrameStartX;//当前帧，图片开始贴图的X坐标
	int	m_nSpeed;//精灵速度
	int m_nFrameCount;//帧数（如一类子弹有几张图）
	int m_nCurrentFrame;
	int	m_nWidth;
	int m_nHeight;
	float m_fAngle;
	bool	m_bIsVisible;
	static CSprite *pHead;
	CSprite *pNext;
};

