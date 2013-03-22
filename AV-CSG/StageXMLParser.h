#ifndef STAGE_PARSERXML_
#define STAGE_PARSERXML_

#include "tinyxml.h"
#include "Parse_def.h"
#include "StageXMLStageObject.h"

typedef std::map<int, CStageXMLStage*> MapStageList;

class CStageXMLParse
{
public:
    ~CStageXMLParse();

    static CStageXMLParse& GetInstance();
    bool LoadXML(const std::string& strPath);
    CStageXMLStage* Get(int nId) const;

    const MapStageList::const_iterator Begin() const;
    const MapStageList::const_iterator End() const;

private:
    void _Close();
    bool _Parse(TiXmlDocument& TinyXML);

private:
    CStageXMLParse();
    CStageXMLParse(CStageXMLParse&);
    CStageXMLParse& operator = (CStageXMLParse&);

    static CStageXMLParse m_XMLParse;

private:
    MapStageList m_mapStage;
};

#endif