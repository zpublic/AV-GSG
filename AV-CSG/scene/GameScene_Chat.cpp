#include "stdafx.h"
#include "GameScene_Chat.h"
#include "data\resourcedata\PicturePool.h"

#define DF_FONT_WIDTH 5

GameScene_Chat::GameScene_Chat(const std::string& strChatId)
    : m_PictureBackgroud(NULL)
    , m_PictureMessageRect(NULL)
    , m_PresentChat(0)
    , m_ChatPageList(0)
    , m_ChatPage(NULL)
{
    m_ChatPageList = CChatParser::Instance()->GetChat(strChatId);
    if (m_ChatPageList)
    {
        m_ChatPage = CChatPageParser::Instance()->GetChatPage(
            m_ChatPageList->at(m_PresentChat));
        if (m_ChatPage)
        {
            m_PictureBackgroud = CPicturePool::GetInstance()->GetPicture(
                m_ChatPage->BackgroundID);
            m_PictureMessageRect = CPicturePool::GetInstance()->GetPicture(
                m_ChatPage->SpeckerID);
        }
    }
}


GameScene_Chat::GameScene_Chat()
{
}

GameScene_Chat::~GameScene_Chat()
{
}

void GameScene_Chat::Update()
{
    if (InputEngine_->ClickOk())
    {
        m_PresentChat++;
        if (m_PresentChat < (int)m_ChatPageList->size())
        {
            m_ChatPage = CChatPageParser::Instance()->GetChatPage(
                m_ChatPageList->at(m_PresentChat));
            if (m_ChatPage)
            {
                m_PictureBackgroud = CPicturePool::GetInstance()->GetPicture(
                    m_ChatPage->BackgroundID);
                m_PictureMessageRect = CPicturePool::GetInstance()->GetPicture(
                    m_ChatPage->SpeckerID);
            }
        }
        else
        {
            SceneEngine_->Pop();
        }
    }
}

void GameScene_Chat::Reset()
{
    ///> 清空图像
    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameScene_Chat::Output()
{
    if ((!m_ChatPageList) && (!m_ChatPage))
    {
        SceneEngine_->Pop();
        return;
    }
    if (m_PresentChat > (int)m_ChatPageList->size())
    {
        SceneEngine_->Pop();
        return;
    }
    //先绘制背景
    if (m_PictureBackgroud)
    {
        m_PictureBackgroud->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }
    //再绘制对话框
    if (m_PictureMessageRect)
    {
        m_PictureMessageRect->DrawBitmap(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    }

    SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    RECT textRect;
    SIZE FontSize;
    ::SetBkMode(g_hMemDC, TRANSPARENT);
    ::SetTextColor(g_hMemDC, RGB(m_ChatPage->r,m_ChatPage->g,m_ChatPage->b));
    ::GetTextExtentPoint(g_hMemDC, CA2W(m_ChatPage->Content.c_str()),
        m_ChatPage->Content.length(), &FontSize);

    ::SetRect(&textRect, m_ChatPage->x, m_ChatPage->y,
        FontSize.cy, FontSize.cx);
    int rectHeight = ::DrawText(
        g_hMemDC, CA2W(m_ChatPage->Content.c_str()),
        -1, &textRect,
        DT_WORDBREAK | DT_CALCRECT | DT_EDITCONTROL);
    if (rectHeight)
    {
        textRect.bottom = rectHeight;
        textRect.right = SCREEN_WIDTH - m_ChatPage->x;
    }
    ::DrawText(
        g_hMemDC, CA2W(m_ChatPage->Content.c_str()),
        -1, &textRect, DT_EDITCONTROL | DT_WORDBREAK);
    ::BitBlt(g_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
}