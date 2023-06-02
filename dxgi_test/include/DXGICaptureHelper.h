#ifndef BXC_DXGICAPTUREHELPER_H
#define BXC_DXGICAPTUREHELPER_H

#include "DXGICaptureTypes.h"

class DXGICaptureHelper
{
public:
	static
		COM_DECLSPEC_NOTHROW
		inline
		HRESULT
		ConvertDxgiOutputToMonitorInfo(
			_In_ const DXGI_OUTPUT_DESC* pDxgiOutput,
			_In_ int monitorIdx,
			_Out_ tagDublicatorMonitorInfo* pOutVal
		)
	{
		CHECK_POINTER(pOutVal);
		// reset output parameter
		RtlZeroMemory(pOutVal, sizeof(tagDublicatorMonitorInfo));
		CHECK_POINTER_EX(pDxgiOutput, E_INVALIDARG);

		switch (pDxgiOutput->Rotation)
		{
		case DXGI_MODE_ROTATION_UNSPECIFIED:
		case DXGI_MODE_ROTATION_IDENTITY:
			pOutVal->RotationDegrees = 0;
			break;

		case DXGI_MODE_ROTATION_ROTATE90:
			pOutVal->RotationDegrees = 90;
			break;

		case DXGI_MODE_ROTATION_ROTATE180:
			pOutVal->RotationDegrees = 180;
			break;

		case DXGI_MODE_ROTATION_ROTATE270:
			pOutVal->RotationDegrees = 270;
			break;
		}

		pOutVal->Idx = monitorIdx;
		pOutVal->Bounds.X = pDxgiOutput->DesktopCoordinates.left;
		pOutVal->Bounds.Y = pDxgiOutput->DesktopCoordinates.top;
		pOutVal->Bounds.Width = pDxgiOutput->DesktopCoordinates.right - pDxgiOutput->DesktopCoordinates.left;
		pOutVal->Bounds.Height = pDxgiOutput->DesktopCoordinates.bottom - pDxgiOutput->DesktopCoordinates.top;

		wsprintfW(pOutVal->DisplayName, L"Display %d: %ldx%ld @ %ld,%ld"
			, monitorIdx + 1
			, pOutVal->Bounds.Width, pOutVal->Bounds.Height
			, pOutVal->Bounds.X, pOutVal->Bounds.Y);

		return S_OK;
	} // ConvertDxgiOutputToMonitorInfo

	static
		COM_DECLSPEC_NOTHROW
		inline
		BOOL
		IsEqualMonitorInfo(
			_In_ const tagDublicatorMonitorInfo* p1,
			_In_ const tagDublicatorMonitorInfo* p2
		)
	{
		if (nullptr == p1) {
			return (nullptr == p2);
		}
		if (nullptr == p2) {
			return FALSE;
		}

		return memcmp((const void*)p1, (const void*)p2, sizeof(tagDublicatorMonitorInfo)) == 0;
	} // IsEqualMonitorInfo



}; // end class DXGICaptureHelper

#endif // BXC_DXGICAPTUREHELPER_H
