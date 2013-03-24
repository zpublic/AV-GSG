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

    void SetBulletType(const std::string& strBulletType);
    const std::string& GetBulletType() const;

    void SetSpeed(int nSpeed);
    const int GetSpeed() const;

    void SetSkinId(const std::string& strSkinPath);
    const std::string& GetSkinId() const;

private:
    long m_HP;
    std::string m_SkinId;
    std::string m_BulletType;
    int m_Speed;
};

#endif