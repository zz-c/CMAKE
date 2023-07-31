#include <Windows.h>
#include <strsafe.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#pragma warning( disable : 4996 )

static std::string logTime() {
	const char* time_fmt = "%Y-%m-%d %H:%M:%S";
	time_t t = time(nullptr);
	char time_str[64];
	strftime(time_str, sizeof(time_str), time_fmt, localtime(&t));

	return time_str;
}


//  __FILE__ 获取源文件的相对路径和名字
//  __LINE__ 获取该行代码在文件中的行号
//  __func__ 或 __FUNCTION__ 获取函数名

#define LOGI(format, ...)  fprintf(stderr,"[INFO]%s [%s:%d] " format "\n", logTime().data(),__func__,__LINE__,##__VA_ARGS__)
#define LOGE(format, ...)  fprintf(stderr,"[ERROR]%s [%s:%d] " format "\n",logTime().data(),__func__,__LINE__,##__VA_ARGS__)


static int64_t getCurTime()// 获取当前系统启动以来的毫秒数
{
	long long now = std::chrono::steady_clock::now().time_since_epoch().count();
	return now / 1000000;
}
static int64_t getCurTimestamp()// 获取毫秒级时间戳（13位）
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()).
		count();

}

using namespace std;

DWORD failureMessage() {

	DWORD dw = GetLastError();

	//LPVOID lpMsgBuf;
	wchar_t* lpMsgBuf;
	//LPVOID lpDisplayBuf;


	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,//自动在末尾加 换行符
		0, NULL);

	// Display the error message and exit the process
	/*lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)L"DhcpV4FailoverGetClientInfo") + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		L"DhcpV4FailoverGetClientInfo", dw, lpMsgBuf);*/
		//MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		//wprintf(L"DhcpV4FailoverGetClientInfo failed with Error = %d,Error Message = %ws\n", dw, lpMsgBuf);

		//wstring errMsg = lpMsgBuf;//OK
	if (0 != dw) {
		wcout << "Error Code = " << dw << ",Error Message = " << lpMsgBuf;// errMsg;// << endl;//不需要endl
	}

	LocalFree(lpMsgBuf);
	/*LocalFree(lpDisplayBuf);*/

	return dw;
}


class Screenshot_Winapi {

public:
	Screenshot_Winapi() {
	


		if (failureMessage()) {//ERROR_SUCCESS == 0
			printf("GetDC error\n");
			return;
		}
		
		int screenX = GetSystemMetrics(SM_CXSCREEN);

		if (failureMessage()) {//ERROR_SUCCESS == 0
			LOGE("GetSystemMetrics(SM_CXSCREEN)");
			return;
		}
		int screenY = GetSystemMetrics(SM_CYSCREEN);
		if (failureMessage()) {//ERROR_SUCCESS == 0
			LOGE("GetSystemMetrics(SM_CYSCREEN)");
			return;
		}

		LOGI("screenX=%d,screenY=%d", screenX, screenY);

		//screenX = 1920;
		//screenY = 1080;




		mInitState = true;
	}
	~Screenshot_Winapi() {}
public:
	int save(int imageNum);

private:
	bool mInitState = false;

	HWND hwnd;
	HDC hdc;
	int screenX = 0;
	int screenY = 0;



};
int Screenshot_Winapi::save(int imageNum) {

	LOGI("imageNum=%d ----------------", imageNum);

	if (!mInitState) {
		LOGE("初始化句柄失败");
		return -1;
	}


	int64_t t1 = 0;
	int64_t t2 = 0;


	//set locale env for output
	//set first env
	setlocale(LC_CTYPE, "");//必须设置，否则wcout输出错误

	hwnd = GetDesktopWindow();
	hdc = GetDC(hwnd);


	//HBITMAP 仅仅只是个句柄，就是个无数据的指针
	//它绝不是 &BITMAP 是两个完全根本不同数据结构
	//感觉创建的就是一个空对象，还需要绑定hdcCopy
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, screenX, screenY);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("CreateCompatibleBitmap error\n");
		return -1;
	}


	HDC hdcCopy = CreateCompatibleDC(hdc);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("CreateCompatibleDC error\n");
		return -1;
	}


	SelectObject(hdcCopy, hBitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("SelectObject error\n");
		return -1;
	}

	//这步很关键，复制hdc数据，否则hbitmap就是没有数据，就是空的
	//复制数据到位图
	BitBlt(hdcCopy, 0, 0, screenX, screenY, hdc, 0, 0, SRCCOPY);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("BitBlt error\n");
		return -1;
	}


	std::wstring fileName_ws;
	{
		std::wstringstream wss;
		wss << "screenshot_winapi-" << imageNum << L".bmp";
		//wss <<imageNum << L".bmp";
		fileName_ws = wss.str();
	}

	//LPCTSTR fileName = L"d:\\output.bmp";
	LPCTSTR fileName = fileName_ws.c_str();

	BITMAP bitmap;

	//要想获取bitmap的信息必须要使用 BITMAP
	//HBITMA 和 BITMAP 完全是不同的
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GetObject error\n");
		return -1;
	}

	BITMAPINFOHEADER bitmapInfoHeader;
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);    // 本结构所占的字节
	bitmapInfoHeader.biWidth = bitmap.bmWidth;            // 位图宽
	bitmapInfoHeader.biHeight = bitmap.bmHeight;            // 位图高
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = bitmap.bmBitsPixel;    // 每一图素的位数
	bitmapInfoHeader.biCompression = BI_RGB;            // 不压缩
	bitmapInfoHeader.biSizeImage = 0;  //  位图大小
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	//  调色板长度
	int colorSize = 0;
	//  调色表大小
	DWORD paletteSize = 0;
	//  位图大小
	DWORD bitmapSize = 0;

	bitmapSize = 4 * ((bitmap.bmWidth * bitmap.bmBitsPixel + 31) / 32) * bitmap.bmHeight;
	//  如果图素位 <= 8bit，则有调色板
	if (bitmapInfoHeader.biBitCount <= 8)
	{
		//?
		colorSize = (1 << bitmap.bmBitsPixel);
	}
	//  计算调色板大小 ？
	paletteSize = colorSize * sizeof(RGBQUAD);

	//分配内存
	HGLOBAL memoryForBitmap = GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER) + paletteSize + bitmapSize);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GlobalAlloc error\n");
		return -1;
	}

	//锁定内存
	LPBITMAPINFOHEADER bitmapInfoHeaderPtr = (LPBITMAPINFOHEADER)GlobalLock(memoryForBitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GlobalLock error\n");
		return -1;
	}

	//core function
	//将bitmapInfoHeader中的内容写入分配的内存中，这一步必须做，好像是输出bitmap的条件参数，如大小等
	*bitmapInfoHeaderPtr = bitmapInfoHeader;
	// 将位图中的数据以bits的形式放入lpData中。
	//core core core function !!!
	//需要通过 显示 hdc 和 hBitmap 把数据 复制到 内存中，然后输出！
	GetDIBits(hdcCopy, hBitmap, 0, bitmapInfoHeader.biHeight, (LPBYTE)bitmapInfoHeaderPtr + sizeof(BITMAPINFOHEADER) + paletteSize/*这里是个输出参数*/, (LPBITMAPINFO)bitmapInfoHeaderPtr/*这里是个输入参数*/, DIB_RGB_COLORS);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GetDIBits error\n");
		return -1;
	}

	BITMAPFILEHEADER bitmapFileHeader;
	bitmapFileHeader.bfType = 0x4D42;  // 位图文件类型：BM
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paletteSize + bitmapSize;  // 位图大小
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paletteSize;  // 位图数据与文件头部的偏移量


	//把上面的数据写入文件中
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("CreateFile error\n");
		//return -1;
	}


	DWORD numberOfWritten = 0;

	//  写入位图文件头
	WriteFile(hFile, &bitmapFileHeader, sizeof(BITMAPFILEHEADER), &numberOfWritten, NULL);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("WriteFile1 error\n");
		//return -1;
	}
	//  写入位图数据
	WriteFile(hFile, (LPBITMAPINFOHEADER)bitmapInfoHeaderPtr, bitmapFileHeader.bfSize - sizeof(BITMAPFILEHEADER), &numberOfWritten, NULL);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("WriteFile2 error\n");
		//return -1;
	}

	GlobalUnlock(memoryForBitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("GlobalUnlock error\n");
		return -1;
	}

	GlobalFree(memoryForBitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("GlobalFree error\n");
		return -1;
	}

	CloseHandle(hFile);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("CloseHandle error\n");
		return -1;
	}
	
	//必须要有前缀 L， 否则输出有问题
	wcout <<"\t" << screenX << "-" << screenY << L",HDC 句柄:" << hdc << L",HBITMAP 句柄:" << hBitmap << L",HDC 句柄:" << hdcCopy << endl;

	return 0;
}


int main() {
	Screenshot_Winapi ss_winapi;

	int imageNum = 1;
	while (true)
	{
	
		ss_winapi.save(imageNum);
		Sleep(3000);
		++imageNum;
	}
	system("pause");

	return 0;
}