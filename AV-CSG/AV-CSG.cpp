// AV-CSG.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AV-CSG.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE g_hInst;                        // current instance
TCHAR g_szTitle[MAX_LOADSTRING];          // The title bar text
TCHAR g_szWindowClass[MAX_LOADSTRING];    // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


#include "control/game/GameControler.h"
CGameControler *g_pGameControl = NULL;
HDC g_hdc;

InputEngine* InputEngine_ = NULL;
SceneEngine* SceneEngine_ = NULL;
AudioEngine* AudioEngine_ = NULL;
bool AUDIO_ENABLE = true;

void InitEngine()
{
    InputEngine_ = InputEngine::Instance();
    InputEngine_->Initialize();
    SceneEngine_ = SceneEngine::Instance();
    SceneEngine_->Initialize();
    AudioEngine_ = AudioEngine::Instance();
    AudioEngine_->Initialize();
}

void UninitEngine()
{
    InputEngine::Destroy();
    SceneEngine::Destroy();
    AudioEngine::Destroy();
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, g_szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_AIRCRAFTGAME, g_szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    InitEngine();
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AIRCRAFTGAME));

    //ÓÎÏ·Ñ­»·
    while (msg.message != WM_QUIT)
    {


        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        g_pGameControl->UpdateScence();
    }

    g_pGameControl->Exit();
    UninitEngine();

    return (int) msg.wParam;
}

BOOL CenterWindow(HWND hwndWindow)
{
    HWND hwndParent;
    RECT rectWindow, rectParent;

    hwndParent = GetParent(hwndWindow);
    if (!hwndParent)
        hwndParent = GetDesktopWindow();
    if (hwndParent)
    {
        GetWindowRect(hwndWindow, &rectWindow);
        GetWindowRect(hwndParent, &rectParent);

        int nWidth = rectWindow.right - rectWindow.left;
        int nHeight = rectWindow.bottom - rectWindow.top;

        int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
        int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

        int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
        int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

        // make sure that the dialog box never moves outside of the screen
        if (nX < 0) nX = 0;
        if (nY < 0) nY = 0;
        if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
        if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

        MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);

        return TRUE;
    }

    return FALSE;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AIRCRAFTGAME));
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_AIRCRAFTGAME);
    wcex.lpszClassName	= g_szWindowClass;
    wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    g_hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(
        g_szWindowClass,
        g_szTitle,
        WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_POPUP,
        CW_USEDEFAULT, 0,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    if (!CenterWindow(hWnd))
    {
        MoveWindow(hWnd, 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, true);
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    g_hdc = GetDC(hWnd);

    g_pGameControl = new CGameControler;
    g_pGameControl->SetWndDC(g_hdc);

    char filePath[MAX_PATH] = {0};
    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "Resource/stage/stage.xml");
    g_pGameControl->SetStageXML(filePath);

    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "Resource/plane/plane.xml");
    g_pGameControl->SetPlaneXML(filePath);

    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "Resource/bullet/bullet.xml");
    g_pGameControl->SetBulletXML(filePath);

    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "Resource/weapon/weapon.xml");
    g_pGameControl->SetWeaponXML(filePath);

    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "Resource/emitter/emitter.xml");
    g_pGameControl->SetEmitterXML(filePath);

    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "Resource/blast/blast.xml");
    g_pGameControl->SetBlastXML(filePath);
    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    switch (message)
    {
    case WM_KEYDOWN:
        InputEngine_->KeyDown(wParam);
        break;
    case WM_KEYUP:
        InputEngine_->KeyUp(wParam);
        break;
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_BEGIN:
            g_pGameControl->StartGame();
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:
        ReleaseDC(hWnd, g_hdc);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
