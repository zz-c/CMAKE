// hellojni.cpp : 定义 DLL 应用程序的导出函数。
//


#include "top_zhost_jni_HelloWorldJNI.h"


JNIEXPORT void JNICALL Java_top_zhost_jni_HelloWorldJNI_helloJNI
(JNIEnv *, jobject, jstring){
	printf("printf from C");
}