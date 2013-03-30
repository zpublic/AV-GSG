#include "stdafx.h"
#include "BlastXMLParser.h"

bool CBlasXMLParse::LoadXML(const std::string& strPath)
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

const CBlastXMLObject* CBlasXMLParse::Get(const std::string& strId) const
{
    auto it = m_mapBlast.find(strId);
    if (it == m_mapBlast.end())
    {
        return NULL;
    }
    return it->second;
}

bool CBlasXMLParse::_Parse(TiXmlDocument& TinyXML)
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
        if (tiElement->Attribute(ID_OBJECT) != NULL)
        {
            pBlast->SetId(tiElement->Attribute(ID_OBJECT));
        }
        if (tiElement->Attribute(NAME_OBJECT) != NULL)
        {
            pBlast->SetName(tiElement->Attribute(NAME_OBJECT));
        }
        if (tiElement->Attribute(PLANE_SKIN_OBJECT) != NULL)
        {
            pBlast->SetSkinId(tiElement->Attribute(PLANE_SKIN_OBJECT));
        }
        if (tiElement->Attribute(TYPE_OBJECT) != NULL)
        {
            pBlast->SetType(tiElement->Attribute(TYPE_OBJECT));
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