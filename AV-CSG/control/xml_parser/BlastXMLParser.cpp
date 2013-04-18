#include "stdafx.h"
#include "BlastXMLParser.h"

CBlastXMLParse* Singleton<CBlastXMLParse>::m_pInst = NULL;

CBlastXMLParse::CBlastXMLParse()
{
}

CBlastXMLParse::~CBlastXMLParse()
{
}

bool CBlastXMLParse::Initialize()
{
    return true;
}

bool CBlastXMLParse::LoadXML(const std::string& strPath)
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

const CBlastXMLObject* CBlastXMLParse::Get(const std::string& strId) const
{
    auto it = m_mapBlast.find(strId);
    if (it == m_mapBlast.end())
    {
        return NULL;
    }
    return it->second;
}

bool CBlastXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != BLAST_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(BLAST_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CBlastXMLObject* pBlast = new CBlastXMLObject;
        if (!BaseParse(pBlast, tiElement))
        {
            continue;
        }
        if (tiElement->Attribute(PLANE_SKIN_OBJECT) != NULL)
        {
            pBlast->SetSkinId(tiElement->Attribute(PLANE_SKIN_OBJECT));
        }
        if (tiElement->Attribute(FRAMECOUNT_OBJECT) != NULL)
        {
            pBlast->SetFrameCount(::atol(tiElement->Attribute(FRAMECOUNT_OBJECT)));
        }
        if (tiElement->Attribute(WIDTH_OBJCET) != NULL)
        {
            pBlast->SetWidth(::atol(tiElement->Attribute(WIDTH_OBJCET)));
        }
        if (tiElement->Attribute(HEIGHT_OBJECT) != NULL)
        {
            pBlast->SetHeight(::atol(tiElement->Attribute(HEIGHT_OBJECT)));
        }
        m_mapBlast[pBlast->GetId()] = pBlast;
    }
    return true;
}