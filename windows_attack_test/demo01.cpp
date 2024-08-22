#include <windows.h>
#include <stdio.h>

#define ID_WIN_BUTTON 1
#define ID_READ_BUTTON 2
#define IDC_EDIT 3
#define ID_WRITE_BUTTON 4
#define ID_CALL_BUTTON 5
#define ID_TEXT_AREA 6
int valueAddress = 0x00F87170;
int value = 0;
int callAddress = 0x00F83150;
HWND hEditDataAddress, hEditDataVal, hEditMethod, hTextArea;


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
        600, 500,
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

// 获取窗口句柄
void getWinHwnd() {
    HWND hwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
    if (hwnd == NULL) {
        // MessageBox(hwnd, "无法找到窗口句柄", "提示", MB_OK);
        SetWindowText(hTextArea, "无法找到窗口句柄");
    }
    else {
        char msg[200];
        snprintf(msg, sizeof(msg), "被攻击程序句柄: %p", hwnd);
        SetWindowText(hTextArea, msg);
    }
}

// 读取edit内存地址刷新
void freshValueAddress() {
    //int valueAddress = 0x00F87170;
    //int callAddress = 0x00F83150;
    char valueBuffer[11];

    GetWindowText(hEditDataAddress, valueBuffer, sizeof(valueBuffer));
    printf("valueBuffer: %s\n", valueBuffer);
    sscanf(valueBuffer, "%x", &valueAddress);
    printf("valueAddress: 0x%08X\n", valueAddress);

    GetWindowText(hEditMethod, valueBuffer, sizeof(valueBuffer));
    printf("valueBuffer: %s\n", valueBuffer);
    sscanf(valueBuffer, "%x", &callAddress);
    printf("callAddress: 0x%08X\n", callAddress);
}

// 目标进程内存读取
void readMemAddress() {
    freshValueAddress();
    // 获取窗口句柄
    HWND hwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
    if (hwnd == NULL) {
        SetWindowText(hTextArea, "无法找到窗口句柄");
        return;
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
    int buffer;
    SIZE_T bytesRead;
    // 打开目标进程
    hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processId);
    if (hProcess == NULL) {
        printf("Failed to open process. Error: %lu\n", GetLastError());
        SetWindowText(hTextArea, "打开目标进程失败");
        return;
    }
    else {
        printf("hProcess ID: %lu\n", hProcess);
    }
    // 读取数据
    if (ReadProcessMemory(hProcess, (LPCVOID)valueAddress, &buffer, sizeof(buffer), &bytesRead)) {
        printf("Successfully read %zu bytes. Value: %d\n", bytesRead, buffer);
        char msg[200];
        snprintf(msg, sizeof(msg), "成功读取%zu字节，值: % d\n", bytesRead, buffer);
        SetWindowText(hTextArea, msg);
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

// 目标进程内存写入
void writeMemAddress() {
    freshValueAddress();
    // 要写入的数据值
    char valueBuffer[100];
    GetWindowText(hEditDataVal, valueBuffer, sizeof(valueBuffer));
    int value = strtol(valueBuffer, NULL, 10);

    HWND hwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
    if (hwnd == NULL) {
        MessageBox(hwnd, "无法找到窗口句柄", "提示", MB_OK);
        return;
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
    // 写内存
    HANDLE hProcess;
    int buffer;
    SIZE_T bytesRead;

    // 打开目标进程
    // hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processId);
    hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processId);
    if (hProcess == NULL) {
        printf("Failed to open process. Error: %lu\n", GetLastError());
        return;
    }
    else {
        printf("hProcess ID: %lu\n", hProcess);
    }

    // 将 int 数据写入目标内存
    SIZE_T bytesWritten;
    if (WriteProcessMemory(hProcess, (LPVOID)valueAddress, &value, sizeof(value), &bytesWritten)) {
        printf("Memory written successfully.\n");
        printf("Bytes written: %zu\n", bytesWritten);
        SetWindowText(hTextArea, "写入内存成功");
    }
    else {
        printf("Failed to write memory. Error: %lu\n", GetLastError());
    }

    // 关闭进程句柄
    CloseHandle(hProcess);
}

// 目标进程函数触发
void callMethod() {
    // 获取窗口句柄
    HWND hwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
    if (hwnd == NULL) {
        MessageBox(hwnd, "无法找到窗口句柄", "提示", MB_OK);
        return;
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
    // LPCVOID baseAddress = (LPCVOID)0x00257174; // 目标进程中的起始地址
    int buffer;
    SIZE_T bytesRead;

    // 打开目标进程
    // hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processId);
    hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processId);
    if (hProcess == NULL) {
        printf("Failed to open process. Error: %lu\n", GetLastError());
        return;
    }
    else {
        printf("hProcess ID: %lu\n", hProcess);
    }

    // 读取数据
    if (ReadProcessMemory(hProcess, (LPCVOID)valueAddress, &buffer, sizeof(buffer), &bytesRead)) {
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

    // 在目标进程中创建线程并执行
    HANDLE hThread;
    // 在目标进程中创建线程并执行 shellcode
    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)callAddress, NULL, 0, &threadId);
    if (hThread == NULL) {
        printf("Failed to create remote thread. Error: %lu\n", GetLastError());
        CloseHandle(hProcess);
        return;
    }

    printf("Remote thread created successfully.\n");
    printf("Thread ID: %lu\n", threadId);
    SetWindowText(hTextArea, "调用成功");
    // 等待线程完成
    WaitForSingleObject(hThread, INFINITE);
    // 清理
    CloseHandle(hThread);

    // 关闭进程句柄
    CloseHandle(hProcess);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        char valueAddressStr[11];
        sprintf(valueAddressStr, "0x%08X", valueAddress);
        char callAddressStr[11];
        sprintf(callAddressStr, "0x%08X", callAddress);

        CreateWindowEx(0, "STATIC", "数据地址:",WS_CHILD | WS_VISIBLE, 
            50, 50, 80, 25, hwnd, NULL, NULL, NULL);
        hEditDataAddress = CreateWindowEx(0, "EDIT", valueAddressStr, WS_CHILD | WS_VISIBLE | WS_BORDER,
            150, 50, 120, 25, hwnd, (HMENU)IDC_EDIT, NULL, NULL);
        CreateWindowEx(0, "STATIC", "写入值:", WS_CHILD | WS_VISIBLE,
            300, 50, 80, 25, hwnd, NULL, NULL, NULL);
        hEditDataVal = CreateWindowEx(0, "EDIT", "100", WS_CHILD | WS_VISIBLE | WS_BORDER,
            400, 50, 120, 25, hwnd, (HMENU)IDC_EDIT, NULL, NULL);

        CreateWindowEx(0, "STATIC", "函数地址:",WS_CHILD | WS_VISIBLE, 
            50, 100, 80, 25, hwnd, NULL, NULL, NULL);
        hEditMethod = CreateWindowEx(0, "EDIT", callAddressStr, WS_CHILD | WS_VISIBLE | WS_BORDER,
            150, 100, 120, 25, hwnd, (HMENU)IDC_EDIT, NULL, NULL);

        CreateWindowEx(0, "BUTTON", "获取句柄", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            50, 200, 80, 30, hwnd, (HMENU)ID_WIN_BUTTON, NULL, NULL);
        CreateWindowEx(0, "BUTTON", "读取内存", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            150, 200, 80, 30, hwnd, (HMENU)ID_READ_BUTTON, NULL, NULL);
        CreateWindowEx(0, "BUTTON", "修改内存", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 200, 80, 30, hwnd, (HMENU)ID_WRITE_BUTTON, NULL, NULL);
        CreateWindowEx(0, "BUTTON", "函数触发", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            350, 200, 80, 30, hwnd, (HMENU)ID_CALL_BUTTON, NULL, NULL);
        // 信息提示
        hTextArea = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE,
            50, 250, 380, 20, hwnd, (HMENU)ID_TEXT_AREA, NULL, NULL);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
            case ID_WIN_BUTTON:
                getWinHwnd();
                return 0;
            case ID_READ_BUTTON:
                readMemAddress();
                return 0;
            case ID_WRITE_BUTTON:
                writeMemAddress();
                return 0;
            case ID_CALL_BUTTON:
                callMethod();
                return 0;
            default:
                return 1;
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
