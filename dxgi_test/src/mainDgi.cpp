//#include "stdafx.h"
#include <windows.h>
#include <gdiplus.h>
//use  cstring
#include <atlstr.h>

#pragma comment(lib, "gdiplus.lib")
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <iostream>
#include <chrono>

using namespace Gdiplus;

bool UpdateDesktop()
{
	HWINSTA station = OpenWindowStation(L"winsta0", FALSE, GENERIC_ALL);
	//HWINSTA station = GetProcessWindowStation();
	//HWINSTA station = OpenWindowStation(L"winlogon", FALSE, GENERIC_ALL);
	if (!station)
	{
		printf("[UpdateDesktop]OpenWindowStation Error:%d\n", GetLastError());
		return false;
	}
	if (!SetProcessWindowStation(station))
	{
		printf("[UpdateDesktop]SetProcessWindowStation Error:%d\n", GetLastError());
		return false;
	}

	bool result = false;
	HDESK desktop = OpenInputDesktop(0, FALSE, GENERIC_ALL);
	if (desktop)
	{
		if (SetThreadDesktop(desktop))
		{
			result = true;
		}
		else {
			printf("[UpdateDesktop]SetThreadDesktop Error:%d\n", GetLastError());
		}
		CloseDesktop(desktop);
	}
	else {
		printf("[UpdateDesktop]OpenInputDesktop Error:%d\n", GetLastError());
	}


	CloseWindowStation(station);
	return result;
}


int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders  
	UINT  size = 0;         // size of the image encoder array in bytes  

	ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure  

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure  

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success  
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure  
}

static int64_t getCurTimestamp()// 获取毫秒级时间戳（13位）
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()).
		count();

}
void scheenshoe_gdi(int imageNum) {
	printf("--------------------saveScreen imageNum=%d-------------------- \n", imageNum);

	if (!UpdateDesktop()) {
	
		return;
	}

	int nScreenWidth = 1920;//GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = 1080;//GetSystemMetrics(SM_CYSCREEN);

	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);


	printf("screenX=%d,screenY=%d \n", nScreenWidth, nScreenHeight);

	//HDESK hDesk = OpenInputDesktop(0, FALSE, READ_CONTROL);
	//SetThreadDesktop(hDesk);
	//CloseDesktop(hDesk);
	//EnumDesktopWindows



	HWINSTA hWinsta = GetProcessWindowStation();
	if (!hWinsta) {
		printf("获取窗口站的句柄失败\n");
		return;
	}
	//OpenWindowStation(hWinsta, FALSE, READ_CONTROL);
	//SetProcessWindowStation(hWinsta);

	//HWND hDesktopWnd = GetDesktopWindow();
	HWND hDesktopWnd = GetActiveWindow();


	HDC hDesktopDC = GetDC(hDesktopWnd);
	//HDC hDesktopDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);

	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);
	BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0,0, SRCCOPY);

	//保存
	//初始化GDI
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	if (Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Ok)
	{
		;
	}

	SYSTEMTIME Systime;
	GetLocalTime(&Systime);//Systime.wYear, Systime.wMonth, Systime.wDay
	CString szFileName;
	//szFileName.Format(L"D:\\file\\out\\screenshot_gdi-%d.png",imageNum);
	szFileName.Format(L"screenshot_gdi-%d.png", getCurTimestamp());
	//szFileName.Format(L"screenshot_gdi-%d.png",imageNum);

	CLSID pngClsid;
	GetEncoderClsid(L"image/png", &pngClsid);
	/*
	DWORD quality = 30;
	EncoderParameters encoderParameters;
	encoderParameters.Count = 1;
	encoderParameters.Parameter[0].Guid = EncoderQuality;
	encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues = 1;
	encoderParameters.Parameter[0].Value = &quality;
	*/

	Gdiplus::Bitmap* pbmSrc = Gdiplus::Bitmap::FromHBITMAP(hCaptureBitmap, NULL);
	if (pbmSrc->Save(szFileName, &pngClsid) == Ok) {
		;
	}
	//卸载GDI
	Gdiplus::GdiplusShutdown(gdiplusToken);

	DeleteObject(hCaptureBitmap);
	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);

}

int main(int argc, _TCHAR* argv[])
{
	//saveScreen(0);
	int imageNum = 1;
	while (true)
	{
		scheenshoe_gdi(imageNum);
		Sleep(2000);
		++imageNum;
	}
	system("pause");
	return 0;
}

