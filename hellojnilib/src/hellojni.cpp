// hellojni.cpp : ���� DLL Ӧ�ó���ĵ���������
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