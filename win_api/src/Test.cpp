#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

// �ص�������ö�ٴ���ʱ����
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    // ��ȡ���ڱ���
    if (GetWindowText(hwnd, windowTitle, sizeof(windowTitle))) {
        // �������Ƿ���������±���
        if (strstr(windowTitle, "���±�") != NULL) {
            printf("���: %p, ����: %s\n", hwnd, windowTitle);
            // �ҵ�Ŀ�괰�ڣ���������ֹͣö��
            HWND* pHwnd = (HWND*)lParam;
            *pHwnd = hwnd;
            return FALSE; // ֹͣö��
        }
    }
    return TRUE; // ����ö��
}

// ��ȡ���±����ھ��
HWND GetNotepadWindowHandle() {
    HWND notepadHwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&notepadHwnd);
    return notepadHwnd;
}

// ���ݴ��ھ����ȡ��Ӧ�Ľ���ID
DWORD GetProcessIDByHandle(HWND hwnd) {
    DWORD processID = 0;
    // ��ȡ���������Ľ���ID
    GetWindowThreadProcessId(hwnd, &processID);
    return processID;
}

int main() {
    HWND notepadHwnd = GetNotepadWindowHandle();
    if (notepadHwnd == NULL) {
        printf("�޷��ҵ����±����ڡ�\n");
        return 1;
    }
    std::cout << "notepadHwnd Value: " << notepadHwnd << std::endl;

    DWORD processID =  GetProcessIDByHandle(notepadHwnd);
    std::cout << "processID Value: " << processID << std::endl;

    // ��Ŀ�����
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
        return 1;
    }

    //// Ŀ������ڴ��еĵ�ַ
    //LPCVOID baseAddress = (LPCVOID)0x00000200;  // ʾ�������滻Ϊʵ�ʵ�ַ
    //// ���ڽ��ն�ȡ���ݵĻ�����
    //int buffer = 0;
    //// ��ȡĿ������ڴ�
    //SIZE_T bytesRead;
    //if (ReadProcessMemory(hProcess, baseAddress, &buffer, sizeof(buffer), &bytesRead)) {
    //    std::cout << "Read success. Value: " << buffer << std::endl;
    //}
    //else {
    //    std::cerr << "Failed to read process memory. Error: " << GetLastError() << std::endl;
    //}
    //// �ر�Ŀ����̾��
    //CloseHandle(hProcess);

    return 0;
}
