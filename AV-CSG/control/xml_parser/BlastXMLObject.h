#ifndef BLAST_XML_OBJECT_
#define BLAST_XML_OBJECT_

#include <string>
#include "XMLObject.h"

class CBlastXMLObject : public CXMLObject
{
public:
    CBlastXMLObject();
    virtual ~CBlastXMLObject();

    void SetWidth(int nWidth);
    const int GetWidth() const;

    void SetHeight(int nHeight);
    const int GetHeight() const;

    void SetFrameCount(int nFrameCount);
    const int GetFrameCount() const;

    void SetSkinId(const std::string& strSkinPath);
    const std::string& GetSkinId() const;

private:
    int m_Width;
    int m_Height;
    int m_FrameCount;
    std::string m_SkinId;
};

#endif