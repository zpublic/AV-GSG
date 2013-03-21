#ifndef PLANE_XML_OBJECT_
#define PLANE_XML_OBJECT_

#include "XMLObject.h"
#include <string>

class CPlaneXMLObject : public CXMLObject
{
public:
    CPlaneXMLObject();
    virtual ~CPlaneXMLObject();

    void SetHP(long lnHP);
    const long GetHP() const;

    void SetBulletType(int nBulletType);
    const int GetBulletType() const;

    void SetSpeed(int nSpeed);
    const int GetSpeed() const;

    void SetSkinId(const std::string& strSkinPath);
    const std::string& GetSkinId() const;

private:
    long m_HP;
    std::string m_SkinId;
    int m_BulletType;
    int m_Speed;
};

#endif