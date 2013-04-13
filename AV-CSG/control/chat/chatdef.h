#ifndef CHAT_DEF_
#define CHAT_DEF_

#include <string>
#include <vector>
#include <map>

typedef struct _ChatPage
{
    std::string BackgroundID;
    std::string SpeckerID;
    std::string Content;
}ChatPage;

typedef std::map<int, ChatPage*> ChatPagePool;
typedef std::vector<int> ChatPageList;
typedef std::map<std::string, ChatPageList> ChatPool;

#define CHATPAGE_ROOT_GAME "gamechatpage"
#define CHATPAGE_BKID "backgroudid"
#define CHATPAGE_SKID "speckerid"

#define CHAT_OBJECT "chat"
#define CHAT_ID "id"

#define CHAT_ROOT_GAME "gamechat"
#define CHAT_CONTECT "contect"
#define CHAT_ID "id"

#endif