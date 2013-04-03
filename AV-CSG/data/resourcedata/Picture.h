#pragma once
/*
*	CPicture�ࣺ��ɶ�ͼƬ��Դ�ļ��غͻ����������ص���ͼƬ���Ǵ���ɫ������λͼ����˲����ñ���ͼ������ͼ�ķ�ʽʵ��͸��λͼ��
*	��������һ�ַ���ʵ�ֶ�̬����ͼ�Դﵽ͸����Ч����ԭ���뿴http://qsjming.blog.51cto.com/1159640/536331��http://blog.csdn.net/suolao/article/details/4582206
*/

class CPicture
{
public:
    CPicture();
    ~CPicture(void);

    //��λͼ����͸������������ָ��DC��
    void DrawBitmap(HDC hdcDest,    //Ŀ��DC
        int nXOriginDest,           //��ʼX����
        int nYOriginDest,           //��ʼY����
        int nWidthDest,             //Ŀ��DC���	
        int nHeightDest,            //Ŀ��DC�߶�
        int nXOriginSrc,            //λͼ��ʼX����
        int nYOriginSrc);           //λͼ��ʼY����

    void ImmediateDrawBitmap(HDC hdcDest,    //Ŀ��DC
        int nXOriginDest,           //��ʼX����
        int nYOriginDest,           //��ʼY����
        int nWidthDest,             //Ŀ��DC���	
        int nHeightDest,            //Ŀ��DC�߶�
        int nXOriginSrc,            //λͼ��ʼX����
        int nYOriginSrc);           //λͼ��ʼY����

    //��Ҫ�ṩ�ļ�������������͸��������ɫ����Ϊ�ҵ���ͼƬ�����а��к����̣���������˴˲���
    void LoadBitmap(const TCHAR *szFileName, COLORREF clTransparent);
    void LoadBitmap(const TCHAR *szFileName, int nWidth, int nHeight);

    //��ȡλͼ��Դ���
    HBITMAP GetBitmap(){ return m_hBitmap; }

    int	GetWidth(){ return m_nWidth; }
    int GetHeight(){ return m_nHeight; }

    void FreeBitmap();
private:
    //����λͼ��Դ
    void LoadBitmap(const TCHAR *szFileName);

    //��ͼƬ����͸������
    void TransparentBitmap();

    HBITMAP     m_hBitmap;
    HBITMAP     m_hMaskBitmap;
    COLORREF    m_TransColor;
    int         m_nWidth;
    int         m_nHeight;
};
