#ifndef BXC_DXGICAPTURE_H
#define BXC_DXGICAPTURE_H


#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <dxgi1_2.h>
#include "DXGICaptureTypes.h"

namespace BXC {
	class DXGICapture
	{
	public:
		DXGICapture();
		~DXGICapture();
		bool InitDevice();

		bool InitDupl(UINT monitorIdx, int& duplWidth, int& duplHeight);
		bool ReInitDupl(UINT monitorIdx, int& duplWidth, int& duplHeight);

		int GetDuplicatorMonitorInfoCount() const;
	public:
		GETFRAMERESULT getFrame(int timeout = 100); //millisecond
		bool copyFrameToBuffer(BYTE** buffer, long bufferSize);
		bool doneWithFrame();

	private:
		HRESULT loadMonitorInfos();
		void freeMonitorInfos();
		void showMonitorInfos();

		ID3D11Device* m_Device;
		IDXGIOutputDuplication* m_DeskDupl;
		bool m_DeskDupl_state = false;

		UINT m_monitorIdx;
		DublicatorMonitorInfoVec  m_monitorInfos;
		ID3D11Texture2D* m_AcquiredDesktopImage;
		ID3D11Texture2D* m_AcquiredDesktopImage_copy;
	};
}

#endif //BXC_DXGICAPTURE_H
