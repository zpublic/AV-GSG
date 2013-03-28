#include "stdafx.h"
#include "PathBase.h"

PathBase::PathBase( int x /*= 0*/, int y /*= 0*/ )
{

}

PathBase::~PathBase()
{

}

void PathBase::SetPos( int x, int y )
{
    m_Pos.x = x;
    m_Pos.y = y;
}

Pos PathBase::Update( int nFrame /*= 1*/ )
{
    return m_Pos;
}

