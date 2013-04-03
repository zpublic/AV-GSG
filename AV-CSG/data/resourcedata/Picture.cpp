#include "StdAfx.h"
#include "Picture.h"

CPicture::CPicture()
    : m_hBitmap(NULL)
    , m_hMaskBitmap(NULL)
{
}

CPicture::~CPicture(void)
{
}

void CPicture::FreeBitmap()
{
    if (m_hBitmap)
    {
        DeleteObject(m_hBitmap);
    }

    if (m_hMaskBitmap)
    {
        DeleteObject(m_hMaskBitmap);
    }
}

void CPicture::LoadBitmap(const TCHAR *szFileName)
{
    if (m_hBitmap)
    {
        DeleteObject(m_hBitmap);
    }
    m_hBitmap = (HBITMAP)LoadImage(
        NULL, szFileName, IMAGE_BITMAP,
        0, 0, LR_LOADFROMFILE);
    //获取位图宽高
    BITMAP bmpTemp;
    GetObject(m_hBitmap, sizeof(BITMAP), &bmpTemp);
    m_nWidth = bmpTemp.bmWidth;
    m_nHeight = bmpTemp.bmHeight;
}

void CPicture::LoadBitmap(const TCHAR *szFileName, int nWidth, int nHeight)
{
    if (m_hBitmap)
    {
        DeleteObject(m_hBitmap);
    }
    m_hBitmap = (HBITMAP)LoadImage(
        NULL, szFileName, IMAGE_BITMAP,
        nWidth, nHeight, LR_LOADFROMFILE);
    //获取位图宽高
    BITMAP bmpTemp;
    GetObject(m_hBitmap, sizeof(BITMAP), &bmpTemp);
    m_nWidth = bmpTemp.bmWidth;
    m_nHeight = bmpTemp.bmHeight;
}

void CPicture::LoadBitmap(const TCHAR *szFileName, COLORREF clTransparent)
{
    LoadBitmap(szFileName);
    m_TransColor = clTransparent;
    TransparentBitmap();
}

void CPicture::DrawBitmap(HDC hdcDest,
                          int nXOriginDest, int nYOriginDest,
                          int nWidthDest, int nHeightDest,
                          int nXOriginSrc, int nYOriginSrc)
{
    //透明贴图
    HDC hBitmapDC = CreateCompatibleDC(hdcDest);
    SelectObject(hBitmapDC, m_hBitmap);
    HDC hMaskDC=CreateCompatibleDC(hdcDest);
    SelectObject(hMaskDC, m_hMaskBitmap);

    SetBkColor(hdcDest, RGB(255, 255, 255));
    SetTextColor(hdcDest, RGB(0, 0, 0));
    BitBlt(
        hdcDest,
        nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest,
        hMaskDC,
        nXOriginSrc, nYOriginSrc,
        SRCAND);// 生成掩码洞
    BitBlt(
        hdcDest,
        nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest,
        hBitmapDC,
        nXOriginSrc, nYOriginSrc,
        SRCPAINT); // 透明效果

    DeleteObject(hBitmapDC);
    DeleteObject(hMaskDC);
}

void CPicture::ImmediateDrawBitmap(HDC hdcDest,
                          int nXOriginDest, int nYOriginDest,
                          int nWidthDest, int nHeightDest,
                          int nXOriginSrc, int nYOriginSrc)
{
    HDC hBitmapDC = CreateCompatibleDC(hdcDest);
    SelectObject(hBitmapDC, m_hBitmap);
    BitBlt(
        hdcDest,
        nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest,
        hBitmapDC,
        nXOriginSrc, nYOriginSrc,
        SRCCOPY);
    DeleteObject(hBitmapDC);
}

void CPicture::TransparentBitmap()
{
    //创建兼容DC和位图，以便制作透明效果
    HDC	hMaskDC, hBitmapDC;

    m_hMaskBitmap = CreateBitmap(m_nWidth, m_nHeight, 1, 1, NULL);//单色位图
    hBitmapDC = CreateCompatibleDC(0);
    hMaskDC = CreateCompatibleDC(0);

    SelectObject(hBitmapDC, m_hBitmap);
    SelectObject(hMaskDC, m_hMaskBitmap);

    //下面是进行透明处理前奏，原理请参看头文件列出的网址
    SetBkColor(hBitmapDC, m_TransColor);	
    BitBlt(hMaskDC, 0, 0, m_nWidth, m_nHeight, hBitmapDC, 0, 0, SRCCOPY);//生成掩码位图

    SetBkColor( hBitmapDC, RGB(0, 0, 0) );
    SetTextColor(hBitmapDC, RGB(255, 255, 255) );

    BitBlt(hBitmapDC, 0, 0, m_nWidth, m_nHeight, hMaskDC, 0, 0, SRCAND);//黑色背景图

    DeleteObject(hBitmapDC);
    DeleteObject(hMaskDC);
}