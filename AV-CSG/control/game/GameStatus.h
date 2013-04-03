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
    static bool GetGamePause();
    static bool GetGameReadying();
    static bool GetGameOvered();

    static void ClearGameStatus();
    static bool IsNeedUpdate();
    static void StartGame();
    static void SetGameOver();
    static void SetGameOvered();
    static void PauseGame();
    static void ReadyingGame();

private:
    static GameStatus           m_emGameStatus;
};
