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
        "Demo Attack Window",
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

// 回调函数，枚举窗口时调用
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    // 获取窗口标题
    if (GetWindowText(hwnd, windowTitle, sizeof(windowTitle))) {
        // 检查标题是否包含“记事本”网络调试助手 Demo Window
        if (strstr(windowTitle, "Demo Window") != NULL) {
            printf("句柄: %p, 标题: %s\n", hwnd, windowTitle);
            // 找到目标窗口，保存句柄并停止枚举
            HWND* pHwnd = (HWND*)lParam;
            *pHwnd = hwnd;
            return FALSE; // 停止枚举
        }
    }
    return TRUE; // 继续枚举
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit;
    switch (uMsg)
    {
    case WM_CREATE:
        hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 50, 200, 25, hwnd, (HMENU)IDC_EDIT, hInst, NULL);
        CreateWindowEx(0, "BUTTON", "获取句柄", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            50, 100, 80, 30, hwnd, (HMENU)ID_SAVE_BUTTON, hInst, NULL);
        CreateWindowEx(0, "BUTTON", "读取内存", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            150, 100, 80, 30, hwnd, (HMENU)ID_SHOW_BUTTON, hInst, NULL);
        CreateWindowEx(0, "BUTTON", "事件触发", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 100, 80, 30, hwnd, (HMENU)ID_SHOW_BUTTON, hInst, NULL);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_SAVE_BUTTON:
        {
            HWND hwnd = NULL;
            EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
            if (hwnd == NULL) {
                MessageBox(hwnd, "无法找到窗口句柄", "提示", MB_OK);
            }
            else {
                char msg[200];
                snprintf(msg, sizeof(msg), "被攻击程序句柄: %p", hwnd);
                MessageBox(hwnd, msg, "提示", MB_OK);
            }
            // MessageBox(hwnd, "被攻击程序句柄", "提示", MB_OK);
        }
        break;

        case ID_SHOW_BUTTON:
        {
            // 获取窗口句柄
            HWND hwnd = NULL;
            EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
            if (hwnd == NULL) {
                MessageBox(hwnd, "无法找到窗口句柄", "提示", MB_OK);
                return 0;
            }
            // 获取进程di
            DWORD processId;
            DWORD threadId = GetWindowThreadProcessId(hwnd, &processId);
            if (threadId != 0) {
                printf("Thread ID: %lu\n", threadId);
                printf("Process ID: %lu\n", processId);
            }
            else {
                printf("Failed to get thread and process IDs. Error: %lu\n", GetLastError());
            }
            // 读取内存

            HANDLE hProcess;
            LPCVOID baseAddress = (LPCVOID)0x00FE7134; // 目标进程中的起始地址
            int buffer;
            SIZE_T bytesRead;

            // 打开目标进程
            // hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processId);
            hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processId);
            if (hProcess == NULL) {
                printf("Failed to open process. Error: %lu\n", GetLastError());
                return 1;
            }
            else {
                printf("hProcess ID: %lu\n", hProcess);
            }


            // 读取数据
            if (ReadProcessMemory(hProcess, baseAddress, &buffer, sizeof(buffer), &bytesRead)) {
                printf("Successfully read %zu bytes. Value: %d\n", bytesRead, buffer);
            }
            else {
                // printf("Failed to read memory. Error: %lu\n", GetLastError());
                DWORD error = GetLastError();
                if (error == ERROR_PARTIAL_COPY) {
                    printf("Failed to read memory. Error: %lu (Partial copy)\n", error);
                }
                else {
                    printf("Failed to read memory. Error: %lu\n", error);
                }
            }

            // 关闭进程句柄
            CloseHandle(hProcess);
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
