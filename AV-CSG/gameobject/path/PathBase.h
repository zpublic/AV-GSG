#pragma once

class PathBase
{
public:
    PathBase(int x = 0, int y = 0);

    virtual ~PathBase();

    void SetPos(int x, int y);

    ///> ȡ�ø���n֡��pos
    Pos Update(int nFrame = 1);

private:
    Pos m_Pos;
};
