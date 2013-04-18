#ifndef STAGE_PARSERXML_
#define STAGE_PARSERXML_

#include "XMLParser.h"
#include "StageXMLStageObject.h"

typedef std::map<int, CStageXMLStage*> MapStageList;

class CStageXMLParse
    : public CXMLParser
{
public:
    ~CStageXMLParse();

    static CStageXMLParse& GetInstance();
    bool LoadXML(const std::string& strPath);
    CStageXMLStage* Get(int nId) const;

    const MapStageList::const_iterator Begin() const;
    const MapStageList::const_iterator End() const;

    int Size() const;
    bool Empty() const;

private:
    void _Close();
    bool _Parse(TiXmlDocument& TinyXML);

private:
    CStageXMLParse();
    CStageXMLParse(CStageXMLParse&);
    CStageXMLParse& operator = (CStageXMLParse&);

    bool _ParseItem(TiXmlElement* pElement, CStageXMLItem* pItem);
    bool _ParseEnemy(TiXmlElement* pElement, CStageXMLEnemy* pEnemy);
    static CStageXMLParse m_XMLParse;

private:
    MapStageList m_mapStage;
};

#endif