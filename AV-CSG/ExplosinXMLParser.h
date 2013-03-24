#ifndef EXPLOSIN_XML_PARSE_
#define EXPLOSIN_XML_PARSE_

#include "Parse_def.h"
#include "../Import/tinyxml-2.6.2/tinyxml.h"
#include "ExplosinXMLObject.h"
#include <map>
#include <string>

typedef std::map<std::string, CExplosinXMLObject*> MapExplosinList;

class CExplosinXMLParse
{
public:
    ~CExplosinXMLParse();
    static CExplosinXMLParse& GetInstance();
    bool LoadXML(const std::string& strPath);

    const CExplosinXMLObject* Get(const std::string& strId) const;
    const int Size() const;

private:
    bool _Parse(TiXmlDocument& TinyXML);
    void _Close();

private:
    CExplosinXMLParse(CExplosinXMLParse&);
    CExplosinXMLParse& operator = (CExplosinXMLParse&);
    CExplosinXMLParse();
    static CExplosinXMLParse m_Explosin;

    MapExplosinList m_mapExplosin;
};

#endif