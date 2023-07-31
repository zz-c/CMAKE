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


//  __FILE__ ��ȡԴ�ļ������·��������
//  __LINE__ ��ȡ���д������ļ��е��к�
//  __func__ �� __FUNCTION__ ��ȡ������

#define LOGI(format, ...)  fprintf(stderr,"[INFO]%s [%s:%d] " format "\n", logTime().data(),__func__,__LINE__,##__VA_ARGS__)
#define LOGE(format, ...)  fprintf(stderr,"[ERROR]%s [%s:%d] " format "\n",logTime().data(),__func__,__LINE__,##__VA_ARGS__)


static int64_t getCurTime()// ��ȡ��ǰϵͳ���������ĺ�����
{
	long long now = std::chrono::steady_clock::now().time_since_epoch().count();
	return now / 1000000;
}
static int64_t getCurTimestamp()// ��ȡ���뼶ʱ�����13λ��
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
		(LPTSTR)&lpMsgBuf,//�Զ���ĩβ�� ���з�
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
		wcout << "Error Code = " << dw << ",Error Message = " << lpMsgBuf;// errMsg;// << endl;//����Ҫendl
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
		LOGE("��ʼ�����ʧ��");
		return -1;
	}


	int64_t t1 = 0;
	int64_t t2 = 0;


	//set locale env for output
	//set first env
	setlocale(LC_CTYPE, "");//�������ã�����wcout�������

	hwnd = GetDesktopWindow();
	hdc = GetDC(hwnd);


	//HBITMAP ����ֻ�Ǹ���������Ǹ������ݵ�ָ��
	//�������� &BITMAP ��������ȫ������ͬ���ݽṹ
	//�о������ľ���һ���ն��󣬻���Ҫ��hdcCopy
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

	//�ⲽ�ܹؼ�������hdc���ݣ�����hbitmap����û�����ݣ����ǿյ�
	//�������ݵ�λͼ
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

	//Ҫ���ȡbitmap����Ϣ����Ҫʹ�� BITMAP
	//HBITMA �� BITMAP ��ȫ�ǲ�ͬ��
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GetObject error\n");
		return -1;
	}

	BITMAPINFOHEADER bitmapInfoHeader;
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);    // ���ṹ��ռ���ֽ�
	bitmapInfoHeader.biWidth = bitmap.bmWidth;            // λͼ��
	bitmapInfoHeader.biHeight = bitmap.bmHeight;            // λͼ��
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = bitmap.bmBitsPixel;    // ÿһͼ�ص�λ��
	bitmapInfoHeader.biCompression = BI_RGB;            // ��ѹ��
	bitmapInfoHeader.biSizeImage = 0;  //  λͼ��С
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	//  ��ɫ�峤��
	int colorSize = 0;
	//  ��ɫ���С
	DWORD paletteSize = 0;
	//  λͼ��С
	DWORD bitmapSize = 0;

	bitmapSize = 4 * ((bitmap.bmWidth * bitmap.bmBitsPixel + 31) / 32) * bitmap.bmHeight;
	//  ���ͼ��λ <= 8bit�����е�ɫ��
	if (bitmapInfoHeader.biBitCount <= 8)
	{
		//?
		colorSize = (1 << bitmap.bmBitsPixel);
	}
	//  �����ɫ���С ��
	paletteSize = colorSize * sizeof(RGBQUAD);

	//�����ڴ�
	HGLOBAL memoryForBitmap = GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER) + paletteSize + bitmapSize);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GlobalAlloc error\n");
		return -1;
	}

	//�����ڴ�
	LPBITMAPINFOHEADER bitmapInfoHeaderPtr = (LPBITMAPINFOHEADER)GlobalLock(memoryForBitmap);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GlobalLock error\n");
		return -1;
	}

	//core function
	//��bitmapInfoHeader�е�����д�������ڴ��У���һ�������������������bitmap���������������С��
	*bitmapInfoHeaderPtr = bitmapInfoHeader;
	// ��λͼ�е�������bits����ʽ����lpData�С�
	//core core core function !!!
	//��Ҫͨ�� ��ʾ hdc �� hBitmap ������ ���Ƶ� �ڴ��У�Ȼ�������
	GetDIBits(hdcCopy, hBitmap, 0, bitmapInfoHeader.biHeight, (LPBYTE)bitmapInfoHeaderPtr + sizeof(BITMAPINFOHEADER) + paletteSize/*�����Ǹ��������*/, (LPBITMAPINFO)bitmapInfoHeaderPtr/*�����Ǹ��������*/, DIB_RGB_COLORS);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("GetDIBits error\n");
		return -1;
	}

	BITMAPFILEHEADER bitmapFileHeader;
	bitmapFileHeader.bfType = 0x4D42;  // λͼ�ļ����ͣ�BM
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paletteSize + bitmapSize;  // λͼ��С
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paletteSize;  // λͼ�������ļ�ͷ����ƫ����


	//�����������д���ļ���
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (failureMessage()) {//ERROR_SUCCESS == 0

		printf("CreateFile error\n");
		//return -1;
	}


	DWORD numberOfWritten = 0;

	//  д��λͼ�ļ�ͷ
	WriteFile(hFile, &bitmapFileHeader, sizeof(BITMAPFILEHEADER), &numberOfWritten, NULL);
	if (failureMessage()) {//ERROR_SUCCESS == 0
		printf("WriteFile1 error\n");
		//return -1;
	}
	//  д��λͼ����
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
	
	//����Ҫ��ǰ׺ L�� �������������
	wcout <<"\t" << screenX << "-" << screenY << L",HDC ���:" << hdc << L",HBITMAP ���:" << hBitmap << L",HDC ���:" << hdcCopy << endl;

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