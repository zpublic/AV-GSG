#ifndef BLAST_XML_PARSE_
#define BLAST_XML_PARSE_

#include "unit\Singleton.h"
#include "tinyxml.h"
#include "Parse_def.h"
#include "BlastXMLObject.h"
#include <string>
#include <map>

typedef std::map<std::string, CBlastXMLObject*> BlastList;

class CBlasXMLParse : public Singleton<CBlasXMLParse>
{
public:
    ~CBlasXMLParse();

    bool LoadXML(const std::string& strPath);

    const CBlastXMLObject* Get(const std::string& strId) const;
    const int Size() const;

private:
    CBlasXMLParse();
    bool _Parse(TiXmlDocument& TinyXML);
    void _Close();
private:
    BlastList m_mapBlast;
};

#endif
