#pragma once

typedef struct _ChatPage
{
    std::string BackgroundID;
    std::string SpeckerID;
    std::string Content;
}ChatPage;

typedef std::map<int, ChatPage*> ChatPagePool;

class CChatPageParser
{
public:
    CChatPageParser();
    ~CChatPageParser();

private:
    ChatPagePool m_PagePool;
};
