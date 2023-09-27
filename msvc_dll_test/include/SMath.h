#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C 
#endif // __cplusplus

#ifdef SMATH_EXPORT
#define SMATH_API EXTERN_C __declspec(dllexport)
#else
#define SMATH_API EXTERN_C __declspec(dllexport)
#endif // SMATH_EXPORT


SMATH_API int test(int v);
