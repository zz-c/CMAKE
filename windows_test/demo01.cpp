#include <windows.h>
#include <stdio.h>

#define ID_EDIT 1
#define ID_SAVE_BUTTON 2
#define ID_SHOW_BUTTON 3
#define ID_TEXT_AREA 4
int value = 0;; // 用于保存输入的数字变量
HWND hEdit, hTextArea;

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
        400, 300,
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

void save() {
    // 获取编辑框中的文本
    char buffer[100];
    GetWindowText(hEdit, buffer, sizeof(buffer));
    // 将文本转换为整数
    value = strtol(buffer, NULL, 10);
    SetWindowText(hTextArea, "保存成功");
}

void read() {
    // 显示保存的文本
    char msg[200];
    snprintf(msg, sizeof(msg), "当前值: %d", value);
    SetWindowText(hTextArea, msg);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg)
    {
        case WM_CREATE:
            // 创建编辑框
            hEdit = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER,
                50, 50, 200, 25, hwnd, (HMENU)ID_EDIT, NULL, NULL);
            // 创建保存按钮
            CreateWindowEx(0, "BUTTON", "保存", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                50, 100, 80, 30, hwnd, (HMENU)ID_SAVE_BUTTON, NULL, NULL);
            // 创建显示按钮
            CreateWindowEx(0, "BUTTON", "读取", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                150, 100, 80, 30, hwnd, (HMENU)ID_SHOW_BUTTON, NULL, NULL);
            // 信息提示
            hTextArea = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE,
                50, 150, 200, 20, hwnd, (HMENU)ID_TEXT_AREA, NULL, NULL);
            return 0;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_SAVE_BUTTON:
                    save();
                    break;
                case ID_SHOW_BUTTON:
                    read();
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
