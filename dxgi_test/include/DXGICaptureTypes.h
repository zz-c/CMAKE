#ifndef BXC_DXGICAPTURETYPES_H
#define BXC_DXGICAPTURETYPES_H

#include <dxgi1_2.h>
#include <windef.h>
#include <sal.h>
#include <vector>


//
// struct tagBounds_s
//
typedef struct tagFrameBounds_s
{
	LONG X;
	LONG Y;
	LONG Width;
	LONG Height;
} tagFrameBounds;

//
// struct tagDublicatorMonitorInfo_s
//
typedef struct tagDublicatorMonitorInfo_s
{
	INT            Idx;
	WCHAR          DisplayName[64];
	INT            RotationDegrees;
	tagFrameBounds Bounds;
} tagDublicatorMonitorInfo;

typedef std::vector<tagDublicatorMonitorInfo*> DublicatorMonitorInfoVec;


enum GETFRAMERESULT {
	GETFRAME_SUCCESS = 0,
	GETFRAME_ERROR,
	GETFRAME_DUPLICATION_ERROR
};

// macros
#define RESET_POINTER_EX(p, v)      if (nullptr != (p)) { *(p) = (v); }
#define RESET_POINTER(p)            RESET_POINTER_EX(p, nullptr)
#define CHECK_POINTER_EX(p, hr)     if (nullptr == (p)) { return (hr); }
#define CHECK_POINTER(p)            CHECK_POINTER_EX(p, E_POINTER)
#define CHECK_HR_BREAK(hr)          if (FAILED(hr)) { break; }
#define CHECK_HR_RETURN(hr)         { HRESULT hr_379f4648 = hr; if (FAILED(hr_379f4648)) { return hr_379f4648; } }

#endif // BXC_DXGICAPTURETYPES_H
