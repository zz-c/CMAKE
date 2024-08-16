#include <windows.h>
#include <stdio.h>

#define ID_SAVE_BUTTON 1
#define ID_SHOW_BUTTON 2
#define IDC_EDIT 3
HINSTANCE hInst;
int value = 0;; // 用于保存输入的数字变量


// 窗口过程的回调函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 注册窗口类
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    // 创建窗口实例
    HWND hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "Demo Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit;
    switch (uMsg)
    {
    case WM_CREATE:
        // 创建编辑框
        hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 50, 200, 25, hwnd, (HMENU)IDC_EDIT, hInst, NULL);
        // 创建保存按钮
        CreateWindowEx(0, "BUTTON", "保存", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            50, 100, 80, 30, hwnd, (HMENU)ID_SAVE_BUTTON, hInst, NULL);
        // 创建显示按钮
        CreateWindowEx(0, "BUTTON", "读取", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            150, 100, 80, 30, hwnd, (HMENU)ID_SHOW_BUTTON, hInst, NULL);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_SAVE_BUTTON:
        {
            // 获取编辑框中的文本
            char buffer[100];
            GetWindowText(hEdit, buffer, sizeof(buffer));
            // 将文本转换为整数
            value = strtol(buffer, NULL, 10);
            MessageBox(hwnd, "保存成功", "提示", MB_OK);
        }
        break;

        case ID_SHOW_BUTTON:
        {
            // 显示保存的文本
            char msg[200];
            snprintf(msg, sizeof(msg), "Saved value: %d", value);
            MessageBox(hwnd, msg, "提示", MB_OK);
        }
        break;
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
