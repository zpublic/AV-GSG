#include "stdafx.h"
#include "Prop.h"

CProp::CProp(int x, int y)
    : CSprite(x, y)
    , m_nStatus(0)
{

}

CProp::~CProp()
{

}

void CProp::Render( HDC hDC )
{

}

void CProp::Update()
{
    ++m_nCurrentFrame;
}

bool CProp::IsVisible()
{
    if (m_nCurrentFrame > 300)
    {
        return false;
    }
    return true;
}
