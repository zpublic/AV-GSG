#ifndef EMITTER_XML_PARSE_
#define EMITTER_XML_PARSE_

#include "unit\Singleton.h"
#include "XMLParser.h"
#include "EmitterXMLObject.h"
#include <string>
#include <map>

typedef std::map<std::string, CEmitterXMLObject*> EmitterList;

class CEmitterXMLParse
    : public Singleton<CEmitterXMLParse>
    , public CXMLParser
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
    EmitterList m_mapEmitter;
};

#endif