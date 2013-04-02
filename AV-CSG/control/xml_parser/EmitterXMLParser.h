#ifndef EMITTER_XML_PARSE_
#define EMITTER_XML_PARSE_

#include "unit\Singleton.h"
#include "tinyxml.h"
#include "Parse_def.h"
#include "EmitterXMLObject.h"
#include <string>
#include <map>

typedef std::map<std::string, CEmitterXMLObject*> BlastList;

class CEmitterXMLParse : public Singleton<CEmitterXMLParse>
{
    friend Singleton<CEmitterXMLParse>;
public:
    ~CEmitterXMLParse();

    virtual bool Initialize();

    bool LoadXML(const std::string& strPath);

    const CEmitterXMLObject* Get(const std::string& strId) const;
    const int Size() const;

private:
    CEmitterXMLParse();
    bool _Parse(TiXmlDocument& TinyXML);
    void _Close();
private:
    BlastList m_mapEmitter;
};

#endif