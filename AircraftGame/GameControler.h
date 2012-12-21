#pragma once
/*
*	add by hels	2012-5-12
*	游戏控制器类，主导整个游戏的运行过程，提供信息以便更新各精灵。也是一个单例模式
*/

class CPrincipalPlane;

class CGameControler
{
public:
	static CGameControler * GetInstance();
	~CGameControler(void);

	//更新游戏场景
	void UpdateScence();
	
	//获取时间间隔
	float GetElapsedTime(){ return m_fElapsedTime;}

	//键盘按键处理
	void KeyDown(WPARAM nKeyCode);
	void KeyUp(WPARAM nKeyCode);

	void SetLastTime(DWORD lastTime){ m_dwLastTime = lastTime; }
	void SetCurrentTime(DWORD currentTime){ m_dwCurrentTime = currentTime; }

	void SetWndDC(HDC hDC);

	void StartGame();

	void GameOver();

	void Exit();
private:
	CGameControler(void);

	//地图循环贴图
	void CirculationMap();

	static CGameControler * pGameControler;
	DWORD m_dwLastTime;//上次绘图时间
	DWORD m_dwCurrentTime;//当前时间
	HDC	  m_hMemDC;
	HBITMAP	m_hBitmapMap;
	HBITMAP m_hMemBitmap;
	HDC		m_hWndDC;
	HDC		m_hMapDC; 
	int		m_nY; //记录地图被截取的宽度
	float	m_fElapsedTime;

	int		m_nPreKey;
	int		m_nCurKey;

	CPrincipalPlane *m_pPrincipalPlane;
};

