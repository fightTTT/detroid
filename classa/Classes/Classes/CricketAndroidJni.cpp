#include "CricketAndroidJni.h"
#include "ck/ck.h"
#include "ck/config.h"

extern "C" JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(JNIEnv* env,jclass,jobject activity)
{
	CkConfig config(env, activity);
	CkInit(&config);
}