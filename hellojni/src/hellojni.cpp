// hellojni.cpp : ���� DLL Ӧ�ó���ĵ���������
//


#include "top_zhost_jni_HelloWorldJNI.h"


JNIEXPORT void JNICALL Java_top_zhost_jni_HelloWorldJNI_helloJNI
(JNIEnv *, jobject, jstring){
	printf("printf from C");
}