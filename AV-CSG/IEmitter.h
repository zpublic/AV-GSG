#pragma once

///> ×Óµ¯·¢ÉäÆ÷
class IEmitter
{
public:
    IEmitter(void) {};
    virtual ~IEmitter(void) {};

public:
    virtual void Emit(int nPosX, int nPosY) = 0;
};

