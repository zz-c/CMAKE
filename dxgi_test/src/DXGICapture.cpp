#include "DXGICapture.h"
#include "Common.h"
#include "DXGICaptureHelper.h"

namespace BXC {

	bool UpdateDesktop()
	{
		HWINSTA station = OpenWindowStation("winsta0", FALSE, GENERIC_ALL);
		//HWINSTA station = GetProcessWindowStation();
		//HWINSTA station = OpenWindowStation(L"winlogon", FALSE, GENERIC_ALL);
		if (!station)
		{
			//printf("[UpdateDesktop]OpenWindowStation Error:%d\n", GetLastError());
			return false;
		}
		if (!SetProcessWindowStation(station))
		{
			//printf("[UpdateDesktop]SetProcessWindowStation Error:%d\n", GetLastError());
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
				//printf("[UpdateDesktop]SetThreadDesktop Error:%d\n", GetLastError());
			}
			CloseDesktop(desktop);
		}
		else {
			//printf("[UpdateDesktop]OpenInputDesktop Error:%d\n", GetLastError());
		}

		CloseWindowStation(station);
		return result;
	}

	DXGICapture::DXGICapture() :
		m_Device(nullptr),
		m_DeskDupl(nullptr),
		m_AcquiredDesktopImage(nullptr),
		m_AcquiredDesktopImage_copy(nullptr),
		m_monitorIdx(0)
	{
	}

	DXGICapture::~DXGICapture()
	{
		LOGI("DXGICapture::~DXGICapture()");

		this->freeMonitorInfos();

		if (m_AcquiredDesktopImage)
		{
			m_AcquiredDesktopImage->Release();
			m_AcquiredDesktopImage = nullptr;
		}
		if (m_AcquiredDesktopImage_copy)
		{
			m_AcquiredDesktopImage_copy->Release();
			m_AcquiredDesktopImage_copy = nullptr;
		}

		if (m_DeskDupl)
		{
			m_DeskDupl->Release();
			m_DeskDupl = nullptr;
		}

		if (m_Device)
		{
			m_Device->Release();
			m_Device = nullptr;
		}
	}

	bool DXGICapture::InitDevice()
	{
		HRESULT hr = S_OK;

		// Driver types supported
		D3D_DRIVER_TYPE DriverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT NumDriverTypes = ARRAYSIZE(DriverTypes);

		// Feature levels supported
		D3D_FEATURE_LEVEL FeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_1
		};
		UINT NumFeatureLevels = ARRAYSIZE(FeatureLevels);

		D3D_FEATURE_LEVEL FeatureLevel;

		// Create device
		for (UINT DriverTypeIndex = 0; DriverTypeIndex < NumDriverTypes; ++DriverTypeIndex)
		{
			hr = D3D11CreateDevice(
				nullptr,
				DriverTypes[DriverTypeIndex],
				nullptr,
				/* D3D11_CREATE_DEVICE_BGRA_SUPPORT
			* This flag adds support for surfaces with a different
			* color channel ordering than the API default.
			* You need it for compatibility with Direct2D. */
				D3D11_CREATE_DEVICE_BGRA_SUPPORT,
				FeatureLevels,
				NumFeatureLevels,
				D3D11_SDK_VERSION,
				&m_Device,
				&FeatureLevel,
				nullptr);

			if (SUCCEEDED(hr))// Device creation success, no need to loop anymore
			{
				return true;
			}
		}


		return false;
	}

	bool DXGICapture::InitDupl(UINT monitorIdx, int& duplWidth, int& duplHeight)
	{
		UpdateDesktop();

		m_monitorIdx = monitorIdx;

		HRESULT hr = S_FALSE;

		//freeMonitorInfos();
		//hr = loadMonitorInfos();
		//if (FAILED(hr)) {
		//	WRITELOG("loadMonitorInfos error");
		//	return false;
		//}


		// Take a reference on the device
		//m_Device->AddRef();

		// Get DXGI device
		IDXGIDevice* DxgiDevice = nullptr;
		hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DxgiDevice));
		if (FAILED(hr))
		{
			LOGE("[0x%08X]: m_Device->QueryInterface failed.", hr);
			return false;
		}

		// Get DXGI adapter
		IDXGIAdapter* DxgiAdapter = nullptr;
		hr = DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DxgiAdapter));
		DxgiDevice->Release();
		DxgiDevice = nullptr;
		if (FAILED(hr))
		{
			LOGE("[0x%08X]: DxgiDevice->GetParent failed.", hr);
			return false;
		}

		// Get output
		IDXGIOutput* DxgiOutput = nullptr;
		hr = DxgiAdapter->EnumOutputs(m_monitorIdx, &DxgiOutput);
		DxgiAdapter->Release();
		DxgiAdapter = nullptr;
		if (FAILED(hr))
		{
			LOGE("[0x%08X]: DxgiAdapter->EnumOutputs failed.", hr);
			return false;
		}

		//DXGI_OUTPUT_DESC outPutDesc;
		//DxgiOutput->GetDesc(&outPutDesc);

		// QI for Output 1
		IDXGIOutput1* DxgiOutput1 = nullptr;
		hr = DxgiOutput->QueryInterface(__uuidof(DxgiOutput1), reinterpret_cast<void**>(&DxgiOutput1));

		DxgiOutput->Release();
		DxgiOutput = nullptr;

		if (FAILED(hr))
		{
			LOGE("[0x%08X]: DxgiOutput->QueryInterface failed.", hr);
			return false;
		}

		// Create desktop duplication
		hr = DxgiOutput1->DuplicateOutput(m_Device, &m_DeskDupl);
		DxgiOutput1->Release();
		DxgiOutput1 = nullptr;

		if (FAILED(hr))
		{
			if (hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE)
			{
				WRITELOG("DXGI_ERROR_NOT_CURRENTLY_AVAILABLE");
			}
			//�л���Ļ����duplicationʧ��ʱ�����Ĵ���
			char log[100];
			sprintf_s(log, "[0x%08X]: DxgiOutput1->DuplicateOutput failed.", hr);
			WRITELOG(log);
			//LOGE("[0x%08X]: DxgiOutput1->DuplicateOutput failed.", hr);

			return false;
		}

		DXGI_OUTDUPL_DESC outDuplDesc;
		m_DeskDupl->GetDesc(&outDuplDesc);

		duplWidth = outDuplDesc.ModeDesc.Width;
		duplHeight = outDuplDesc.ModeDesc.Height;

		m_DeskDupl_state = true;

		//this->showMonitorInfos();
		return true;
	}

	bool DXGICapture::ReInitDupl(UINT monitorIdx, int& duplWidth, int& duplHeight)
	{
		if (m_DeskDupl_state) {
			LOGI("Current duplication normal, no reinit required");
			return true;
		}

		if (m_DeskDupl)
		{
			m_DeskDupl->Release();
			m_DeskDupl = nullptr;
		}

		return InitDupl(monitorIdx, duplWidth, duplHeight);

	}
	HRESULT DXGICapture::loadMonitorInfos() {

		// Get DXGI device
		IDXGIDevice* DxgiDevice = nullptr;
		HRESULT hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DxgiDevice));
		if (FAILED(hr))
		{
			LOGE("[0x%08X]: m_Device->QueryInterface failed.", hr);
			return hr;
		}

		// Get DXGI adapter
		IDXGIAdapter* DxgiAdapter = nullptr;
		hr = DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DxgiAdapter));
		DxgiDevice->Release();
		DxgiDevice = nullptr;
		if (FAILED(hr))
		{
			LOGE("[0x%08X]: DxgiDevice->GetParent failed.", hr);
			return hr;
		}


		for (UINT i = 0; SUCCEEDED(hr); ++i)
		{
			// Get output
			IDXGIOutput* DxgiOutput = nullptr;
			hr = DxgiAdapter->EnumOutputs(i, &DxgiOutput);

			if (FAILED(hr))
			{
				//LOGE("[0x%08X]: DxgiAdapter->EnumOutputs(%d) failed.", hr,i);
				continue;
			}
			DXGI_OUTPUT_DESC DxgiOutputDesc;
			hr = DxgiOutput->GetDesc(&DxgiOutputDesc);
			if (FAILED(hr))
			{
				//LOGE("[0x%08X]: DxgiOutput->GetDesc(%d) failed.", hr, i);
				continue;
			}


			tagDublicatorMonitorInfo* pInfo;
			pInfo = new (std::nothrow) tagDublicatorMonitorInfo;
			if (nullptr == pInfo) {
				return E_OUTOFMEMORY;
			}
			hr = DXGICaptureHelper::ConvertDxgiOutputToMonitorInfo(&DxgiOutputDesc, i, pInfo);
			if (FAILED(hr)) {
				delete pInfo;
				continue;
			}

			m_monitorInfos.push_back(pInfo);

			//printf("\ti=%d\n", i);

		}

		DxgiAdapter->Release();
		DxgiAdapter = nullptr;

		if (0 == m_monitorInfos.size()) {
			return S_FALSE;
		}
		return S_OK;
	}
	void DXGICapture::freeMonitorInfos()
	{
		size_t nCount = m_monitorInfos.size();
		if (nCount == 0) {
			return;
		}
		DublicatorMonitorInfoVec::iterator it = m_monitorInfos.begin();
		DublicatorMonitorInfoVec::iterator end = m_monitorInfos.end();
		for (size_t i = 0; (i < nCount) && (it != end); i++, it++) {
			tagDublicatorMonitorInfo* pInfo = *it;
			if (nullptr != pInfo) {
				delete pInfo;
			}
		}
		m_monitorInfos.clear();
	}
	void DXGICapture::showMonitorInfos() {
		setlocale(LC_ALL, "");

		size_t s = m_monitorInfos.size();
		if (s == 0) {
			return;
		}
		DublicatorMonitorInfoVec::iterator it = m_monitorInfos.begin();
		DublicatorMonitorInfoVec::iterator end = m_monitorInfos.end();
		for (size_t i = 0; (i < s) && (it != end); i++, it++) {
			tagDublicatorMonitorInfo* pInfo = *it;
			if (nullptr != pInfo) {
				LOGI("i=%lld,Idx=%d,DisplayName=%ls,X=%d,Y=%d,Width=%d,Height=%d",
					i, pInfo->Idx, pInfo->DisplayName, pInfo->Bounds.X, pInfo->Bounds.Y, pInfo->Bounds.Width, pInfo->Bounds.Height);

			}
		}

	}
	int DXGICapture::GetDuplicatorMonitorInfoCount() const
	{
		return (int)m_monitorInfos.size();
	}

	GETFRAMERESULT DXGICapture::getFrame(int timeout)
	{
		if (!m_DeskDupl_state) {
			LOGE("Duplication Abnormal, unable to getFrame");
			return GETFRAME_DUPLICATION_ERROR;
		}
		// If still holding old frame, destroy it
		if (m_AcquiredDesktopImage)
		{
			m_AcquiredDesktopImage->Release();
			m_AcquiredDesktopImage = nullptr;
		}

		IDXGIResource* DesktopResource = nullptr;
		DXGI_OUTDUPL_FRAME_INFO FrameInfo;

		// Get new frame
		HRESULT hr = m_DeskDupl->AcquireNextFrame(timeout, &FrameInfo, &DesktopResource);

		if (FAILED(hr))
		{
			if (hr == DXGI_ERROR_WAIT_TIMEOUT) {
				//��Ļ�ޱ仯��������ô���
				//LOGE("[0x%08X]: AcquireNextFrame failed.(May be caused by timeout)", hr);

				if (DesktopResource) {
					DesktopResource->Release();
					DesktopResource = nullptr;
				}

				return GETFRAME_ERROR;
			}
			else {
				//�л���Ļ��������������ô���һ������ô�����Ҫ����Duplication��������ʹ��
				char log[100];
				sprintf_s(log, "[0x%08X]: AcquireNextFrame failed.(May be caused by screen switching)", hr);
				WRITELOG(log);

				if (DesktopResource) {
					DesktopResource->Release();
					DesktopResource = nullptr;
				}
				m_DeskDupl_state = false;
				return GETFRAME_DUPLICATION_ERROR;
			}
		}

		// QI for IDXGIResource
		hr = DesktopResource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_AcquiredDesktopImage));

		DesktopResource->Release();
		DesktopResource = nullptr;

		if (FAILED(hr))
		{
			//char log[60];
			//sprintf_s(log, "[0x%08X]: QueryInterface failed.", hr);
			//WRITELOG(log);

			LOGE("[0x%08X]: QueryInterface failed.", hr);

			return GETFRAME_ERROR;
		}
		return GETFRAME_SUCCESS;
	}

	bool DXGICapture::copyFrameToBuffer(BYTE** buffer, long bufferSize)
	{
		HRESULT hr;
		ID3D11DeviceContext* context;
		m_Device->GetImmediateContext(&context);

		if (!m_AcquiredDesktopImage_copy) {
			D3D11_TEXTURE2D_DESC desc;
			m_AcquiredDesktopImage->GetDesc(&desc);
			// Create CPU access texture m_AcquiredDesktopImage_copy
			D3D11_TEXTURE2D_DESC copyImageDesc;
			copyImageDesc.Width = desc.Width;
			copyImageDesc.Height = desc.Height;
			copyImageDesc.Format = desc.Format;
			copyImageDesc.ArraySize = 1;
			copyImageDesc.BindFlags = 0;
			copyImageDesc.MiscFlags = 0;
			copyImageDesc.SampleDesc.Count = 1;
			copyImageDesc.SampleDesc.Quality = 0;
			copyImageDesc.MipLevels = 1;
			copyImageDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
			copyImageDesc.Usage = D3D11_USAGE_STAGING;
			hr = m_Device->CreateTexture2D(&copyImageDesc, NULL, &m_AcquiredDesktopImage_copy);

			if (FAILED(hr)) {
				LOGE("[0x%08X]: CreateTexture2D failed.", hr);
				return false;
			}

		}


		context->CopyResource(m_AcquiredDesktopImage_copy, m_AcquiredDesktopImage);//ԴTexture2D��Ŀ��Texture2D��Ҫ����ͬ�Ķ��ز�������������ʱ������һЩ������ͬ��

		D3D11_MAPPED_SUBRESOURCE mapRes;
		UINT subresource = D3D11CalcSubresource(0, 0, 0);

		hr = context->Map(m_AcquiredDesktopImage_copy, subresource, D3D11_MAP_READ, 0, &mapRes);
		if (FAILED(hr)) {
			LOGE("[0x%08X]: context->Map failed.", hr);
			return false;
		}
		//UINT lBmpRowPitch = desc2.Width * 4;
		//UINT lRowPitch = std::min<UINT>(lBmpRowPitch, mapRes.RowPitch);
		//long bufferSize = lRowPitch * desc2.Height;
		//*buffer = new UCHAR[bufferSize];

		BYTE* dptr = *buffer;

		memcpy_s(dptr, bufferSize, mapRes.pData, bufferSize);

		context->Unmap(m_AcquiredDesktopImage_copy, subresource);


		return true;
	}

	bool DXGICapture::doneWithFrame()
	{
		HRESULT hr = m_DeskDupl->ReleaseFrame();
		if (FAILED(hr))
		{
			return false;
		}

		if (m_AcquiredDesktopImage)
		{
			m_AcquiredDesktopImage->Release();
			m_AcquiredDesktopImage = nullptr;
		}

		return true;
	}




}
