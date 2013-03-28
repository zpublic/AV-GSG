#pragma once
#include "EmitterGenerate.h"
#include "EnemyGenerate.h"

class CGenerator
{
public:
    CGenerator();
    ~CGenerator();

private:
    CEnemyGenerate      m_EnemyGen;
    CEmitterGenerate    m_EmitterGen;
};
