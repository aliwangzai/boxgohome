#include "AdManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
#include <jni.h>
#include "jni/JniHelper.h"
#include <android/log.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif

static AdManager* g_pAdManager = nullptr;

AdManager* AdManager::getInstance()
{
	if (g_pAdManager == nullptr)
	{
		g_pAdManager = new AdManager();
	}
	return g_pAdManager;
}

void AdManager::showBannerAD()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "showBannerAD", "()V");
	if(isHave)
	{
		CCLOG("the showBannerAD method is exits");
		minfo.env->CallStaticVoidMethod( minfo.classID, minfo.methodID);
	}
	else
	{
		CCLOG("the showBannerAD method is not exits");
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

void AdManager::hideBannerAD()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "hideBannerAD", "()V");
	if (isHave)
	{
		CCLOG("the hideBannerAD method is exits");
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
	else
	{
		CCLOG("the hideBannerAD method is not exits");
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

