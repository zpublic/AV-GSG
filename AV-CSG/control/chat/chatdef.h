#ifndef CHAT_DEF_
#define CHAT_DEF_

#include <string>
#include <vector>
#include <map>

typedef struct _ChatPage
{
    _ChatPage()
    {
        x = 0;
        y = 0;
        r = 0;
        g = 0;
        b = 0;
    }
    std::string BackgroundID;
    std::string SpeckerID;
    std::string Content;
    int x,y;
    int r,g,b;
}ChatPage;

typedef std::map<int, ChatPage*> ChatPagePool;
typedef std::vector<int> ChatPageList;
typedef std::map<std::string, ChatPageList> ChatPool;

#define CHATPAGE_ROOT_GAME "gamechatpage"
#define CHATPAGE_BKID "backgroudid"
#define CHATPAGE_SKID "speckerid"

#define CHAT_OBJECT "chat"
#define CHAT_ID "id"
#define CHAT_X "x"
#define CHAT_Y "y"
#define CHAT_R "r"
#define CHAT_G "g"
#define CHAT_B "b"

#define CHAT_ROOT_GAME "gamechat"
#define CHAT_CONTECT "contect"
#define CHAT_ID "id"

#endif