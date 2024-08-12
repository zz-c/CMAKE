#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

// 回调函数，枚举窗口时调用
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    // 获取窗口标题
    if (GetWindowText(hwnd, windowTitle, sizeof(windowTitle))) {
        // 检查标题是否包含“记事本”
        if (strstr(windowTitle, "记事本") != NULL) {
            printf("句柄: %p, 标题: %s\n", hwnd, windowTitle);
            // 找到目标窗口，保存句柄并停止枚举
            HWND* pHwnd = (HWND*)lParam;
            *pHwnd = hwnd;
            return FALSE; // 停止枚举
        }
    }
    return TRUE; // 继续枚举
}

// 获取记事本窗口句柄
HWND GetNotepadWindowHandle() {
    HWND notepadHwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&notepadHwnd);
    return notepadHwnd;
}

// 根据窗口句柄获取对应的进程ID
DWORD GetProcessIDByHandle(HWND hwnd) {
    DWORD processID = 0;
    // 获取窗口所属的进程ID
    GetWindowThreadProcessId(hwnd, &processID);
    return processID;
}

int main() {
    HWND notepadHwnd = GetNotepadWindowHandle();
    if (notepadHwnd == NULL) {
        printf("无法找到记事本窗口。\n");
        return 1;
    }
    std::cout << "notepadHwnd Value: " << notepadHwnd << std::endl;

    DWORD processID =  GetProcessIDByHandle(notepadHwnd);
    std::cout << "processID Value: " << processID << std::endl;

    // 打开目标进程
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
        return 1;
    }

    //// 目标进程内存中的地址
    //LPCVOID baseAddress = (LPCVOID)0x00000200;  // 示例，需替换为实际地址
    //// 用于接收读取数据的缓冲区
    //int buffer = 0;
    //// 读取目标进程内存
    //SIZE_T bytesRead;
    //if (ReadProcessMemory(hProcess, baseAddress, &buffer, sizeof(buffer), &bytesRead)) {
    //    std::cout << "Read success. Value: " << buffer << std::endl;
    //}
    //else {
    //    std::cerr << "Failed to read process memory. Error: " << GetLastError() << std::endl;
    //}
    //// 关闭目标进程句柄
    //CloseHandle(hProcess);

    return 0;
}
