#pragma once
#include "MenuItem.h"
#include <vector>

class CMenuBase
{
public:
    CMenuBase()
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

protected:
    std::vector<CMenuItem*> m_vecMenuItem;
};
