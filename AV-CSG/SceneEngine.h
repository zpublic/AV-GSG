#pragma once
#include "Singleton.h"
#include "GameScene.h"
#include <vector>

class SceneEngine : public Singleton<SceneEngine>
{
    friend class Singleton<SceneEngine>;

public:
    virtual ~SceneEngine();

    virtual bool Initialize();

    void Push(GameScene* pScene);
    void Pop();
    void PopAll();

    void Update();
    void Output();

private:
    SceneEngine();

    std::vector<GameScene*>     m_GameStack;
    std::vector<GameScene*>     m_PushStack;
    bool                        m_bStatusChange;
    int                         m_nPopCount;
};
