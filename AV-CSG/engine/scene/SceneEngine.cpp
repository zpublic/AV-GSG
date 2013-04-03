#include "stdafx.h"
#include "SceneEngine.h"

template<> SceneEngine* Singleton<SceneEngine>::m_pInst = NULL;

SceneEngine::~SceneEngine()
{
    while (m_GameStack.size() != 0)
    {
        delete m_GameStack.back();
        m_GameStack.pop_back();
    }

    while (m_PushStack.size() != 0)
    {
        delete m_PushStack.back();
        m_PushStack.pop_back();
    }
}

SceneEngine::SceneEngine()
{
    m_bStatusChange = false;
    m_nPopCount     = 0;
}

bool SceneEngine::Initialize()
{
    return true;
}

void SceneEngine::Push( GameScene* pScene )
{
    m_PushStack.push_back(pScene);
    m_bStatusChange = true;
}

void SceneEngine::Pop()
{
    m_nPopCount++;
    m_bStatusChange = true;
}

void SceneEngine::PopAll()
{
    m_nPopCount = m_GameStack.size();
    m_bStatusChange = true;
}

void SceneEngine::Update()
{
    if (m_bStatusChange == true)
    {
        while (m_nPopCount != 0)
        {
            delete m_GameStack.back();
            m_GameStack.pop_back();
            m_nPopCount--;
        }

        while (m_PushStack.size() != 0)
        {
            m_GameStack.push_back(m_PushStack.back());
            m_PushStack.pop_back();
        }

        if (m_GameStack.empty())
        {
            //ControlEngine->ExitGame();
        }

        m_GameStack.back()->Reset();

        m_bStatusChange = false;
    }
    m_GameStack.back()->Update();
}

void SceneEngine::Output()
{
    if (!m_GameStack.empty())
    {
        m_GameStack.back()->Output();
    }
}
