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
        std::string strSkinId;
        int nFrameCount = 0;
        if (!BaseParse(pBlast, tiElement))
        {
            continue;
        }
        Unit::GetXmlStrAttributeA(tiElement ,PLANE_SKIN_OBJECT, strSkinId);
        Unit::GetXmlIntAttribute(tiElement ,FRAMECOUNT_OBJECT, nFrameCount);
        pBlast->SetSkinId(strSkinId);
        pBlast->SetFrameCount(nFrameCount);

        ShapeObject shapeobj;
        BaseShape(&shapeobj, tiElement);
        pBlast->SetWidth(shapeobj.nWidth);
        pBlast->SetHeight(shapeobj.nHeight);
        m_mapBlast[pBlast->GetId()] = pBlast;
    }
    return true;
}