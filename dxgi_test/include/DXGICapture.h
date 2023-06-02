#pragma once


#include <d3d11.h>
#include <dxgi1_2.h>


class DxgiCapture
{
public:
	DxgiCapture();
	~DxgiCapture();
	bool GetFrame(int timeout=100); //millisecond
	bool copyFrameDataToBuffer(BYTE** buffer,int& width,int& height);
	bool DoneWithFrame();
	bool InitDevice();
	bool InitDupl(UINT Output);
	//void saveFrameToBmp(PCWSTR FileName);
	//static void saveTextureToBmp(PCWSTR FileName, ID3D11Texture2D* Texture);

private:
	// vars
	IDXGIOutputDuplication* m_DeskDupl;
	ID3D11Texture2D* m_AcquiredDesktopImage;
	UINT m_OutputNumber;
	DXGI_OUTPUT_DESC m_OutputDesc;
	ID3D11Device* m_Device;
};
