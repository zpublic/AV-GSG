#pragma once
/*
*	CPicture类：完成对图片资源的加载和绘制由于下载到的图片都是带单色背景的位图，因此不能用背景图加屏蔽图的方式实现透明位图。
*	但是有另一种方法实现动态屏蔽图以达到透明的效果。原理请看http://qsjming.blog.51cto.com/1159640/536331和http://blog.csdn.net/suolao/article/details/4582206
*/

class CPicture
{
public:
    CPicture();
    ~CPicture(void);

    //将位图进行透明处理，并贴到指定DC上
    void DrawBitmap(HDC hdcDest,    //目的DC
        int nXOriginDest,           //起始X坐标
        int nYOriginDest,           //起始Y坐标
        int nWidthDest,             //目标DC宽度	
        int nHeightDest,            //目标DC高度
        int nXOriginSrc,            //位图起始X坐标
        int nYOriginSrc);           //位图起始Y坐标

    void ImmediateDrawBitmap(HDC hdcDest,    //目的DC
        int nXOriginDest,           //起始X坐标
        int nYOriginDest,           //起始Y坐标
        int nWidthDest,             //目标DC宽度	
        int nHeightDest,            //目标DC高度
        int nXOriginSrc,            //位图起始X坐标
        int nYOriginSrc);           //位图起始Y坐标

    void LoadBitmap(const TCHAR *szFileName, int nWidth, int nHeight);
    //需要提供文件名和用于设置透明的掩码色，因为找到的图片背景有白有红有绿，因此设置了此参数
    void LoadBitmap(const TCHAR *szFileName, COLORREF clTransparent, int nWidth, int nHeight);

    //获取位图资源句柄
    HBITMAP GetBitmap(){ return m_hBitmap; }

    int	GetWidth(){ return m_nWidth; }
    int GetHeight(){ return m_nHeight; }

    void FreeBitmap();
private:
    //加载位图资源
    void LoadBitmap(const TCHAR *szFileName);

    //将图片进行透明处理
    void TransparentBitmap();

    HBITMAP     m_hBitmap;
    HBITMAP     m_hMaskBitmap;
    COLORREF    m_TransColor;
    int         m_nWidth;
    int         m_nHeight;
};
