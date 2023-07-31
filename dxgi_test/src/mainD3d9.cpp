#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
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

static std::string logTimeNameStr() {
	const char* time_fmt = "%H_%M_%S";
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


#include <d3d9.h>
#pragma  comment(lib,"d3d9.lib")
#include <opencv2/opencv.hpp>
using namespace std;
class Screenshot_D3D9 {

public:
	Screenshot_D3D9() {
		//screenW = GetSystemMetrics(SM_CXSCREEN);
		//screenH = GetSystemMetrics(SM_CYSCREEN);

		screenW = 1920;
		screenH = 1080;

		mInitState = true;
	}
	~Screenshot_D3D9() {}
public:
	int save(int imageNum, void* data);

private:
	bool mInitState = false;
	int screenW = 0;
	int screenH = 0;

	IDirect3D9* d3d = nullptr;
	IDirect3DDevice9* device = nullptr;
	IDirect3DSurface9* sur = nullptr;
};

int Screenshot_D3D9::save(int imageNum, void* data)
{

	LOGI("imageNum=%d ----------------", imageNum);


	//1 创建directx3d对象

	if (!d3d)
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
	}
	if (!d3d) {
		LOGE("Direct3DCreate9 error");
		return -1;
	}


	//2 创建显卡设备对象
	if (!device)
	{
		D3DPRESENT_PARAMETERS pa;
		ZeroMemory(&pa, sizeof(D3DPRESENT_PARAMETERS));
		pa.Windowed = true;
		pa.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		pa.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pa.hDeviceWindow = GetDesktopWindow();
		d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 0,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &pa, &device);

		if (!device) {
			LOGE("CreateDevice error");
			return -1;
		}

	}



	//3 创建离屏表面
	if (!sur)
	{
		device->CreateOffscreenPlainSurface(
			screenW,
			screenH,
			D3DFMT_A8R8G8B8,//像素格式
			D3DPOOL_SCRATCH,//存储位置	
			&sur, 0);
	}
	if (!sur) {
		LOGE("CreateOffscreenPlainSurface error");
		return -1;
	}

	//4 截取屏幕
	device->GetFrontBufferData(0, sur);

	//5 取出数据
	D3DLOCKED_RECT rect;
	ZeroMemory(&rect, sizeof(rect));
	if (sur->LockRect(&rect, 0, 0) != S_OK)
	{
		LOGE("sur->LockRect error");
		return -1;
	}
	memcpy(data, rect.pBits, screenW * screenH * 4);
	sur->UnlockRect();//解锁

}


int main()
{
	int w = 1920;
	int h = 1080;
	int c = 4;
	int size = h * w * c;
	int64_t t1 = 0;
	int64_t t2 = 0;

	char* buffer = new char[size];

	Screenshot_D3D9 ss_d3d9;

	for (int i = 0; i < 200; i++)
	{
		std::string lt = logTimeNameStr();
		std::string fname = "screenshot_d3d9-"+ lt + ".jpg";

		//FILE* fp = fopen(fname.data(), "wb");
		t1 = getCurTimestamp();
		ss_d3d9.save(i,buffer);
		t2 = getCurTimestamp();
		//fwrite(buffer, 1, size, fp);

		LOGI("get 1 frame spend %lld ms", (t2 - t1));
		cv::Mat bgra_image(h, w, CV_8UC4, buffer);
		cv::imwrite(fname, bgra_image);


		//fclose(fp);

		Sleep(3000);
	}

	delete[]buffer;


	system("pause");

	return 0;
}