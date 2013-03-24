#ifndef EXPLOSIN_XML_OBJECT_
#define EXPLOSIN_XML_OBJECT_

#include "XMLObject.h"
#include <string>

class CExplosinXMLObject : public CXMLObject
{
public:
    CExplosinXMLObject();
    virtual ~CExplosinXMLObject();

    void SetPower(int nPower);
    const int GetPower() const;

    void SetSpeed(int nSpeed);
    const int GetSpeed() const;

    void SetWidth(int nWidth);
    const int GetWidth() const;

    void SetHeight(int nHeight);
    const int GetHeight() const;

    void SetFrameCount(int nFrameCount);
    const int GetFrameCount() const;

    void SetSkinId(const std::string& strSkinPath);
    const std::string& GetSkinId() const;

private:
    std::string m_SkinId;
    int m_Power;
    int m_Speed;
    int m_Width;
    int m_Height;
    int m_FrameCount;
};

#endif