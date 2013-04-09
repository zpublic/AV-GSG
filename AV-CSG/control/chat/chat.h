#pragma once

typedef std::vector<int> ChatPageList;
typedef std::map<std::string, ChatPageList> ChatPool;


class CChatParser
{
public:
    CChatParser()
    {
    }

    ~CChatParser()
    {
    }

    ChatPageList& GetChat(const std::string& sChatName)
    {
        return m_ChatPool.begin()->second;
    }


private:
    ChatPool m_ChatPool;
};
