#pragma once
class Unit
{
public:
    Unit(void);
    ~Unit(void);
    static int GetNumX(int nScore, int i);
    static float CalcAngle(int nPosX, int nPosY, int x, int y);
};

