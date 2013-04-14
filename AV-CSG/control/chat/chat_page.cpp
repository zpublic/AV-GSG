#include "stdafx.h"
#include "chat_page.h"

CChatPageParser* Singleton<CChatPageParser>::m_pInst = NULL;

CChatPageParser::CChatPageParser()
{
}

CChatPageParser::~CChatPageParser()
{
}

bool CChatPageParser::Initialize()
{
    return true;
}

bool CChatPageParser::LoadXML(const std::string& strPath)
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

ChatPage* CChatPageParser::GetChatPage(int nChatName) const
{
    auto It = m_PagePool.find(nChatName);
    if (It == m_PagePool.end())
    {
        return NULL;
    }
    return It->second;
}

bool CChatPageParser::_Parse(TiXmlDocument& tiDoc)
{
    TiXmlElement* tiRoot = tiDoc.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != CHATPAGE_ROOT_GAME)
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
        ChatPage* pChatPage = new ChatPage;
        int nId = 0;
        if (Unit::GetXmlStrAttributeA(tiElement, CHATPAGE_BKID, pChatPage->BackgroundID)
            && Unit::GetXmlStrAttributeA(tiElement, CHATPAGE_SKID, pChatPage->SpeckerID)
            && Unit::GetXmlIntAttribute(tiElement, CHAT_ID, nId))
        {
            pChatPage->Content = tiElement->GetText();
            m_PagePool[nId] = pChatPage;
        }
    }
    return true;
}