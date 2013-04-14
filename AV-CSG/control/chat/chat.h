#pragma once

#include "unit\Unit.h"
#include "unit\Singleton.h"
#include "chatdef.h"

class CChatParser : public Singleton<CChatParser>
{
    friend Singleton<CChatParser>;
public:

    ~CChatParser();

    virtual bool Initialize();

    const ChatPageList* GetChat(const std::string& sChatName) const;

    virtual bool LoadXML(const std::string& strPath);

private:
    CChatParser();
    bool _Parse(TiXmlDocument& tiDoc);
    int _ParseContect(const std::string& strContect, ChatPageList& vecContect);
    ChatPool m_ChatPool;
};
