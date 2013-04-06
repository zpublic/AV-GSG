#pragma once

class CMenuBase
{
public:
    CMenuBase()
    {
    }

    virtual ~CMenuBase()
    {
    }

    virtual void OnClick(int iPos)
    {
        ;
    }

    int GetMenuSize()
    {
        return m_vecMenuText.size();
    }

    int AddMenuItem(const std::wstring& MenuItem)
    {
        m_vecMenuText.push_back(MenuItem);
        return m_vecMenuText.size();
    }

    int DelMenuItem(int iPos)
    {
        m_vecMenuText.erase(m_vecMenuText.begin() + iPos);
    }

    std::wstring& GetMenuItem(int iPos)
    {
        return m_vecMenuText[iPos];
    }

    void SetBackgroudImage(const std::string& strBackgroud)
    {
        m_strBackgroud = strBackgroud;
    }

    const std::string& GetBackgroudImage()
    {
        return m_strBackgroud;
    }

protected:
    std::vector<std::wstring> m_vecMenuText;
    std::string m_strBackgroud;
};
