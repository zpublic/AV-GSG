#pragma once

#include "unit\Singleton.h"
#include "unit\Unit.h"
#include "chatdef.h"

class CChatPageParser : public Singleton<CChatPageParser>
{
    friend class Singleton<CChatPageParser>;
public:
    ~CChatPageParser();

    virtual bool Initialize();

    ChatPage* GetChatPage(int nChatName) const;

    virtual bool LoadXML(const std::string& strPath);

private:
    CChatPageParser();
    bool _Parse(TiXmlDocument& tiDoc);
    ChatPagePool m_PagePool;
};
