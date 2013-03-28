#pragma once
#include <string>

class IMenuItemCallback
{
public:
    IMenuItemCallback() {};
    virtual ~IMenuItemCallback() {};

    virtual void OnClick() {};
};

class CMenuItem
{
public:
    CMenuItem() : m_pCallback(NULL) {};
    CMenuItem(IMenuItemCallback* pCallback) : m_pCallback(pCallback) {}
    virtual ~CMenuItem() {};

    std::wstring Text() const { return m_sText; }
    void Text(std::wstring val) { m_sText = val; }

    IMenuItemCallback* Callback() const { return m_pCallback; }
    void Callback(IMenuItemCallback* val) { m_pCallback = val; }

    void OnClick()
    {
        if (m_pCallback)
        {
            m_pCallback->OnClick();
        }
    }

protected:
    IMenuItemCallback* m_pCallback;
    std::wstring m_sText;
};
