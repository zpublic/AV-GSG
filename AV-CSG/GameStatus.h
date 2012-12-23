#pragma once

///> ”Œœ∑◊¥Ã¨π‹¿Ì
class CGameStatus
{
public:
    CGameStatus(void);
    ~CGameStatus(void);

    static bool GetGameOver();
    static bool GetGameReady();
    static bool GetGameRuning();

    static void ClearGameStatus();
    static bool IsNeedUpdate();
    static void StartGame();
    static void SetGameOver();

private:
    static GameStatus           m_emGameStatus;
};

