#include "StdAfx.h"
#include "SelfPlane.h"
#include "EnemyPlane.h"
#include "control\generate\EnemyGenerate.h"
#include "control\xml_parser\BulletXMLParser.h"
#include "control\xml_parser\WeaponXMLParser.h"
#include "control\xml_parser\EmitterXMLParser.h"

CSelfPlane * CSelfPlane::pCSelfPlane = NULL;

CSelfPlane * CSelfPlane::GetInstance()
{
    if (NULL == pCSelfPlane)
    {
        pCSelfPlane = new CSelfPlane(SCREEN_WIDTH/2 - 24, 350);
    }
    return pCSelfPlane;
}

CSelfPlane::CSelfPlane(int x, int y)
    : SelfPlaneBase(x, y)
    , m_FirstHP(0)
{
}

CSelfPlane::~CSelfPlane()
{
}

void CSelfPlane::InitGame(const CPlaneXMLObject* pPlane)
{
    if (!pPlane)
    {
        return;
    }

    const CWeaponXMLObject* pWeaponXML = CWeaponXMLParse::Instance()->Get(pPlane->GetWeapon());
    if (!pWeaponXML)
    {
        return;
    }
    m_WeaponType = pPlane->GetWeapon();
    const CBulletXMLObject* pBullet = CBulletXMLParse::GetInstance().Get(pWeaponXML->GetBulletType());
    if (!pBullet)
    {
        return;
    }
    const CEmitterXMLObject* pEmitterXML = CEmitterXMLParse::Instance()->Get(pWeaponXML->GetEmitter());
    if (!pEmitterXML)
    {
        return;
    }
    Player_->gamestatus_.ResetGameStatus();
    SetWeapon(pEmitterXML->GetType(), true, pBullet->GetPower(), pBullet->GetSpeed());
    m_nAction = STOP_MOVE;
    m_nWidth = 20;
    m_nHeight = 26;
    m_nSpeed = pPlane->GetSpeed();
    m_FirstHP = pPlane->GetHP();
    InitPlane(m_FirstHP);
}

void CSelfPlane::InitPlane(int nHP)
{
    m_bIsStopMove = true;
    m_fHpDot = (float)(105 / nHP);
    m_nHP = nHP;
    m_nPosX = SCREEN_WIDTH/2 - 24;
    m_nPosY = 480;
    m_fBulletFrequency = 0.2f;//ÿ�뷢��5���ӵ�
    m_fFrequencyTime = 0.0f;
    m_fInvincibletime = 1.0;
    m_bUnDead = true;
    m_bFire = false;
    m_nWholeFired = 3;
}

void CSelfPlane::Update()
{
    float fDis = ElapsedTime * m_nSpeed;

    if (m_bUnDead)
    {
        if (m_bIsStopMove && (m_nPosY > 2 * SCREEN_HEIGHT / 3))
        {
            m_nPosY -= (int)fDis;
        }

        m_fInvincibletime -= ElapsedTime;
        if (m_fInvincibletime <= 0)
        {
            m_bUnDead = false;
            m_fInvincibletime = 1.0;
        }
    }
    m_fFrequencyTime += ElapsedTime;

    if (!m_bIsStopMove)
    {
        m_nPosX += int(cos(m_fAngle) * fDis);
        m_nPosY += int(sin(m_fAngle) * fDis);
        if(m_nPosX < 0.0f)
            m_nPosX = 0;
        if(m_nPosY < 0.0f)
            m_nPosY = 0;
        if(m_nPosX > SCREEN_WIDTH - m_nWidth)
            m_nPosX = SCREEN_WIDTH - m_nWidth;
        if(m_nPosY > SCREEN_HEIGHT - m_nHeight)
            m_nPosY = SCREEN_HEIGHT - m_nHeight;
    }

    if (m_bFire && m_fFrequencyTime >= m_fBulletFrequency)
    {
        if (m_piEmitter == NULL)
        {
            return;
        }
        const CWeaponXMLObject* pWeapon = CWeaponXMLParse::Instance()->Get(m_WeaponType);
        if (!pWeapon)
        {
            return;
        }
        m_piEmitter->Emit(m_nPosX + m_nWidth / 2 - 8, m_nPosY - 16, pWeapon->GetBulletType());

        while(m_fFrequencyTime > m_fBulletFrequency)
        {
            m_fFrequencyTime -= m_fBulletFrequency;
        }
    }
}

void CSelfPlane::Control(ActionType actionType)
{
    m_nAction = actionType;
    switch(actionType)
    {
    case LEFT:
        m_fAngle = PI;
        m_bIsStopMove = false;
        break;
    case RIGHT:
        m_fAngle = 0.0f;
        m_bIsStopMove = false;
        break;
    case UP:
        m_fAngle = 3.0f * PI / 2.0f;
        m_bIsStopMove = false;
        break;
    case DOWN:
        m_fAngle = PI / 2.0f;
        m_bIsStopMove = false;
        break;
    case LEFT_UP:
        m_fAngle = 5.0f * PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case LEFT_DOWN:
        m_fAngle = 3.0f * PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case RIGHT_UP:
        m_fAngle = 2.0f * PI - PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case RIGHT_DOWN:
        m_fAngle = PI / 4.0f;
        m_bIsStopMove = false;
        break;
    case STOP_MOVE:
        m_bIsStopMove = true;
        break;
    case FIRE:
        m_bFire = true;
        break;
    case STOP_FIRE:
        m_bFire = false;
        break;
    case FIREALL:
        if (m_nWholeFired > 0)
        {
            IEmitter* iEmitter = CEmitterGenerate::Generate(BIGBULLET_EMITTER, true, 0, 0, IEMITTER_SELF);
            iEmitter->Emit(0, 0, "emBulletTypeAmmoAll1");
            CEnemyPlane* temp = CEnemyGenerate::spEnemyHead;
            for(;temp!=NULL;temp=temp->m_pEmnemyNext)
            {
                temp->CheckCollision(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 100);
            }
            m_nWholeFired--;
        }
        break;
    }
}

void CSelfPlane::Render(HDC hDC)
{
    CPicture* pOurfighter =  CPicturePool::GetInstance()->GetPicture("ourfighter");
    if (pOurfighter)
    {
        pOurfighter->DrawBitmap(
            hDC,
            m_nPosX, m_nPosY,
            m_nWidth, m_nHeight,
            0, 0);
    }

    CPicture* pLife = CPicturePool::GetInstance()->GetPicture("life");
    if (pLife)
    {
        for (int i = 0; i < Player_->gamestatus_.GetLife() - 1; ++i)
        {
            pLife->DrawBitmap(hDC, 25 + i * 18, 10, 18, 24, 0, 0);
        }
    }

    int nScore = Player_->gamestatus_.GetScore();

    CPicture* pNum = CPicturePool::GetInstance()->GetPicture("num");
    ///> ��ʾ��λ�÷�
    if (pNum)
    {
        for (int i = 0; i < 8; ++i)
        {
            pNum->DrawBitmap(hDC, SCREEN_WIDTH - 170 + i * 16, 25, 16, 18, Unit::GetNumX(nScore, i) * 16, 0);
        }
    }

    CPicture* pHPSide = CPicturePool::GetInstance()->GetPicture("hpbarside");
    if (pHPSide)
    {
        pHPSide->DrawBitmap(hDC, 20, 40, 105, 13, 0, 0);
    }

    CPicture* pHP = CPicturePool::GetInstance()->GetPicture("hpbar");
    if (pHP)
    {
        pHP->DrawBitmap(hDC, 22, 42, (int)(m_nHP * m_fHpDot), 9, 0, 0);
    }
}

bool CSelfPlane::CheckCollision(int x, int y, int width, int height, int power)
{
    /*
    ��ײ���򵥵��������ཻ������
    �ж��������ε����������ˮƽ�ʹ�ֱ���룬ֻҪ������ֵ����ĳ�������Ϳ����ཻ��
    ����A�Ŀ� Wa = Xa2-Xa1 �� Ha = Ya2-Ya1
    ����B�Ŀ� Wb = Xb2-Xb1 �� Hb = Yb2-Yb1
    ����A���������� (Xa3,Ya3) = �� (Xa2+Xa1)/2 ��(Ya2+Ya1)/2 ��
    ����B���������� (Xb3,Yb3) = �� (Xb2+Xb1)/2 ��(Yb2+Yb1)/2 ��
    ����ֻҪͬʱ������������ʽ�ӣ��Ϳ���˵�����������ཻ��
    1�� | Xb3-Xa3 | <= Wa/2 + Wb/2 
    2�� | Yb3-Ya3 | <= Ha/2 + Hb/2
    ����
    | Xb2+Xb1-Xa2-Xa1 | <= Xa2-Xa1 + Xb2-Xb1
    | Yb2+Yb1-Ya2-Ya1 | <=Y a2-Ya1 + Yb2-Yb1
    */

    if (m_bUnDead)
    {
        return false;
    }

    int Xa3 = m_nPosX + m_nWidth / 2;
    int Ya3 = m_nPosY + m_nHeight / 2;
    int Xb3 = x + width / 2;
    int Yb3 = y + height / 2;

    //����ͼƬ�ĳߴ����⣬��΢����
    if ( (abs( Xb3 - Xa3 ) + m_nWidth / 5) <= (m_nWidth + width)/2 &&
        ( abs( Yb3 - Ya3 ) + m_nHeight / 5) <= (m_nHeight + height)/2)
    {
        m_nHP -= power;
        if (m_nHP <= 0)
        {
            if (Player_->gamestatus_.SubLife())
            {
                //new blast
                InitPlane(m_FirstHP);
            }
        }
        return true;
    }
    return false;
}

void CSelfPlane::SetWeapon(
    EmitterType strType,
        bool bFriend,
        int nPower,
        int nSpeed)
{
    delete m_piEmitter;
    m_piEmitter = CEmitterGenerate::SelectSelfEmitter(strType,
        bFriend,
        nPower,
        nSpeed);
}