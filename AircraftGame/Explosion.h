#pragma once
/*
*	add by hels	2012-5-13
*	爆炸效果类，主要是根据给定的坐标和类型，显示爆炸的效果就可。
*/
#include "Sprite.h"
#include "Picture.h"

class CExplosion : CSprite
{
public:
	CExplosion(int x, int y, BlastType blastType);
	virtual ~CExplosion(void);
	static void LoadImage();
	static void FreeImage();

	void Update();
	void Render(HDC hDC);
private:
	static	CPicture *pPictureBlast[2];
	BlastType m_nBlastType;
};

