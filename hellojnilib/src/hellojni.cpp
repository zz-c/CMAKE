// hellojni.cpp : 定义 DLL 应用程序的导出函数。
//


#include "top_zhost_jni_HelloWorldJNI.h"
#include "SMath.h"


JNIEXPORT void JNICALL Java_top_zhost_jni_HelloWorldJNI_helloJNI
(JNIEnv *, jobject, jstring){
	printf("C printf ..");
	int a = 3;
	int result = test(a);
	printf("C printf result= %d", result);
}