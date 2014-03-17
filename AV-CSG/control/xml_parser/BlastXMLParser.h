#ifndef BLAST_XML_PARSE_
#define BLAST_XML_PARSE_

#include "unit\Singleton.h"
#include "BlastXMLObject.h"
#include "XMLParser.h"
#include <string>
#include <map>

typedef std::map<std::string, CBlastXMLObject*> BlastList;

class CBlastXMLParse
    : public Singleton<CBlastXMLParse>
    , public CXMLParser
{
    friend Singleton<CBlastXMLParse>;
public:
    ~CBlastXMLParse();

    virtual bool Initialize();

    bool LoadXML(const std::string& strPath);

    const CBlastXMLObject* Get(const std::string& strId) const;
    const int Size() const;

private:
    CBlastXMLParse();
    bool _Parse(TiXmlDocument& TinyXML);
    void _Close();
private:
    BlastList m_mapBlast;
};

#endif
