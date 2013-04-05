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
    //��ȡλͼ���
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
    //��ȡλͼ���
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

void CPicture::LoadBitmap(const TCHAR *szFileName, COLORREF clTransparent, int nWidth, int nHeight)
{
    LoadBitmap(szFileName, nWidth, nHeight);
    m_TransColor = clTransparent;
    TransparentBitmap();
}

void CPicture::DrawBitmap(HDC hdcDest,
                          int nXOriginDest, int nYOriginDest,
                          int nWidthDest, int nHeightDest,
                          int nXOriginSrc, int nYOriginSrc)
{
    //͸����ͼ
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
        SRCAND);// �������붴
    BitBlt(
        hdcDest,
        nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest,
        hBitmapDC,
        nXOriginSrc, nYOriginSrc,
        SRCPAINT); // ͸��Ч��

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
    //��������DC��λͼ���Ա�����͸��Ч��
    HDC	hMaskDC, hBitmapDC;

    m_hMaskBitmap = CreateBitmap(m_nWidth, m_nHeight, 1, 1, NULL);//��ɫλͼ
    hBitmapDC = CreateCompatibleDC(0);
    hMaskDC = CreateCompatibleDC(0);

    SelectObject(hBitmapDC, m_hBitmap);
    SelectObject(hMaskDC, m_hMaskBitmap);

    //�����ǽ���͸������ǰ�࣬ԭ����ο�ͷ�ļ��г�����ַ
    SetBkColor(hBitmapDC, m_TransColor);	
    BitBlt(hMaskDC, 0, 0, m_nWidth, m_nHeight, hBitmapDC, 0, 0, SRCCOPY);//��������λͼ

    SetBkColor( hBitmapDC, RGB(0, 0, 0) );
    SetTextColor(hBitmapDC, RGB(255, 255, 255) );

    BitBlt(hBitmapDC, 0, 0, m_nWidth, m_nHeight, hMaskDC, 0, 0, SRCAND);//��ɫ����ͼ

    DeleteObject(hBitmapDC);
    DeleteObject(hMaskDC);
}