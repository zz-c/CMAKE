#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C 
#endif

#ifdef SMATH_EXPORT
#define SMATH_API EXTERN_C __declspec(dllexport)
#else
#define SMATH_API EXTERN_C
#endif


SMATH_API int test(int v);
