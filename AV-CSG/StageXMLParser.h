#ifndef STAGE_PARSERXML_
#define STAGE_PARSERXML_

#include "tinyxml-2.6.2\tinyxml.h"
#include "Parse_def.h"
#include "StageXMLStageObject.h"

class CStageXMLParse
{
public:
    ~CStageXMLParse();

    static CStageXMLParse& GetInstance();
    bool LoadXML(const std::string& strPath);
    CStageXMLStage* Get(const std::string strId) const;

    const std::map<std::string, CStageXMLStage*>::const_iterator Begin() const;
    const std::map<std::string, CStageXMLStage*>::const_iterator End() const;

private:
    void _Close();
    bool _Parse(TiXmlDocument& TinyXML);

private:
    CStageXMLParse();
    CStageXMLParse(CStageXMLParse&);
    CStageXMLParse& operator = (CStageXMLParse&);

    static CStageXMLParse m_XMLParse;

private:
    std::map<std::string, CStageXMLStage*> m_mapStage;
};

#endif