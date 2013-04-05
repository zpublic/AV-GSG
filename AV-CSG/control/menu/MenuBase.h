#pragma once
#include "MenuItem.h"
#include <vector>

class CMenuBase
{
public:
    CMenuBase() : m_vecMenuItem()
    {
    }

    ~CMenuBase()
    {
    }

    int GetMenuSize()
    {
        return m_vecMenuItem.size();
    }

    int AddMenuItem(CMenuItem* pMenuItem)
    {
        m_vecMenuItem.push_back(pMenuItem);
        return m_vecMenuItem.size();
    }

    int DelMenuItem(int iPos)
    {
        m_vecMenuItem.erase(m_vecMenuItem.begin() + iPos);
    }

    CMenuItem* GetMenuItem(int iPos)
    {
        return m_vecMenuItem[iPos];
    }

    void SetBackgroudImage(const std::wstring& strBackgroud)
    {
        m_strBackgroud = strBackgroud;
    }

    const std::wstring& GetBackgroudImage()
    {
        return m_strBackgroud;
    }

protected:
    std::vector<CMenuItem*> m_vecMenuItem;
    std::wstring m_strBackgroud;
};
