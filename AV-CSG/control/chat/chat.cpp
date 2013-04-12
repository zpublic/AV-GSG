#include "stdafx.h"
#include "chat.h"

CChatParser* Singleton<CChatParser>::m_pInst = NULL;

CChatParser::CChatParser()
{
}

CChatParser::~CChatParser()
{
}

bool CChatParser::Initialize()
{
    return true;
}

const ChatPageList* CChatParser::GetChat(const std::string& sChatName) const
{
    auto It = m_ChatPool.find(sChatName);
    if (It == m_ChatPool.end())
    {
        return NULL;
    }
    return (&It->second);
}

bool CChatParser::LoadXML(const std::string& strPath)
{
    TiXmlDocument XmlParse;

    if (strPath.empty())
    {
        return false;
    }

    if (XmlParse.LoadFile(strPath.c_str()))
    {
        return _Parse(XmlParse);
    }
    return true;
}

bool CChatParser::_Parse(TiXmlDocument& tiDoc)
{
    TiXmlElement* tiRoot = tiDoc.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != CHAT_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(CHAT_OBJECT);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        std::string strId;
        std::string strContect;
        ChatPageList vecContect;
        if (Unit::GetXmlStrAttributeA(tiElement, CHAT_ID, strId)
            && Unit::GetXmlStrAttributeA(tiElement, CHAT_CONTECT, strContect))
        {
            if(_ParseContect(strContect, vecContect))
            {
                m_ChatPool[strId] = vecContect;
            }
        }
    }
    return true;
}

int CChatParser::_ParseContect(const std::string& strContect, ChatPageList& vecContect)
{
    if (strContect.empty())
    {
        return 0;
    }
    int index = 0;
    for (; index < strContect.size(); index++)
    {
        std::string::size_type pos;
        pos = strContect.find(',', index);
        if (pos != std::string::npos)
        {
            vecContect.push_back(atoi(strContect.substr(index, pos - 1).c_str()));
        }
    }
    return index;
}