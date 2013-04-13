#pragma once
#include "GameScene.h"
#include "data\resourcedata\Picture.h"
#include "control\chat\chat.h"
#include "control\chat\chat_page.h"
#include <string>

class GameScene_Chat : public GameScene
{
public:
    GameScene_Chat(const std::string& strChatId);
    virtual ~GameScene_Chat();

    virtual void Update();
    virtual void Output();
    virtual void Reset();

private:
    GameScene_Chat();
    int m_PresentChat;
    const ChatPageList* m_ChatPageList;
    ChatPage* m_ChatPage;
    CPicture* m_PictureBackgroud;
    CPicture* m_PictureMessageRect;
};