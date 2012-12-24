#include "stdafx.h"
#include "Unit.h"


Unit::Unit(void)
{
}


Unit::~Unit(void)
{
}

int Unit::GetNumX(int nScore, int i)
{
    switch (i)
    {
    case 0:
        return (nScore / 10000000) % 10;
        break;
    case 1:
        return (nScore / 1000000) % 10;
        break;
    case 2:
        return (nScore / 100000) % 10;
        break;
    case 3:
        return (nScore / 10000) % 10;
        break;
    case 4:
        return (nScore / 1000) % 10;
        break;
    case 5:
        return (nScore / 100) % 10;
        break;
    case 6:
        return (nScore / 10) % 10;
        break;
    case 7:
        return nScore % 10;
        break;
    default:
        break;
    }
    return 0;
}

float Unit::CalcAngle(int nPosX, int nPosY, int x, int y)
{
    float fAngle;
    if (nPosX == x)
    {
        if (nPosY > y)
            fAngle = PI * 0.5;
        else
            fAngle = PI * 1.5;
    }
    else if (nPosY == y)
    {
        if (nPosX > x)
            fAngle = 0;
        else
            fAngle = PI;
    }
    else
    {
        float Result = atan((float)(nPosY - y) / (nPosX - x));
        if ((x < nPosX) && (y > nPosY))
            fAngle = Result + PI;
        else if ((x < nPosX) && (y < nPosY))
            fAngle = Result + PI;
        else if ((x > nPosX) && (y < nPosY))
            fAngle = Result + 2 * PI;
        else 
            fAngle = Result;
    }
    return fAngle;
}
