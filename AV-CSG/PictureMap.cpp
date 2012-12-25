#include "stdafx.h"
#include "PictureMap.h"

CPictureMap::CPictureMap(void)
{
}

CPictureMap::~CPictureMap(void)
{
}

bool CPictureMap::LoadXml(
    LPCWSTR lpFilePath,
    std::map<int, PictureNode>& mapPicture )
{
    mapPicture.clear();
    TiXmlDocument doc;
    if (doc.LoadFile(CW2A(lpFilePath)))
    {
        TiXmlElement* pRoot = doc.RootElement();
        LPCSTR lpRootNodeName = pRoot->Value();
        if (!lpRootNodeName || 0 != _stricmp(lpRootNodeName, XML_ROOT_ELEMENT_NAME))
        {
            return FALSE;
        }
        TiXmlElement* pNodeElement = pRoot->FirstChildElement();
        if (!pNodeElement)
        {
            return FALSE;
        }
        do
        {
            GetPictureNode(pNodeElement, mapPicture);
        }while (pNodeElement = pNodeElement->NextSiblingElement());
    }
    return !mapPicture.empty();
}

void CPictureMap::GetPictureNode(
    TiXmlElement* pElement,
    std::map<int, PictureNode>& mapPicture )
{
    int nId = 0;
    PictureNode picNode;
    if (Unit::GetXmlStrAttribute(pElement, XML_PIC_ELEMENT_PATH, picNode.strPath)
        && Unit::GetXmlIntAttribute(pElement, XML_PIC_ELEMENT_R, picNode.r)
        && Unit::GetXmlIntAttribute(pElement, XML_PIC_ELEMENT_G, picNode.g)
        && Unit::GetXmlIntAttribute(pElement, XML_PIC_ELEMENT_B, picNode.b)
        && Unit::GetXmlIntAttribute(pElement, XML_PIC_ELEMENT_ID, nId))
    {
        mapPicture[nId] = picNode;
    }
}
