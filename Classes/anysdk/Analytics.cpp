#include "Analytics.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>

using namespace anysdk::framework;

#define  LOG_TAG    "Analytics"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
#if (cc_target_pla)
extern "C"{
void Java_com_anysdk_sample_wrapper_nativeStartSession(JNIEnv*  env, jobject thiz)
{
	Analytics::getInstance()->startSession();
}

void Java_com_anysdk_sample_wrapper_nativeStopSession(JNIEnv*  env, jobject thiz)
{
	Analytics::getInstance()->stopSession();
}
}


Analytics* Analytics::_pInstance = NULL;

Analytics::Analytics()
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
		{
			AgentManager::getInstance()->getAnalyticsPlugin()->setDebugMode(true);
		}
}

Analytics::~Analytics()
{

}

Analytics* Analytics::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Analytics();
    }
    return _pInstance;
}

void Analytics::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}
void Analytics::startSession()
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->startSession();
	}

}

void Analytics::stopSession()
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->stopSession();
	}

}

void Analytics::setSessionContinueMillis(long millis)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->setSessionContinueMillis(millis);
	}

}
void Analytics::setCaptureUncaughtException(bool isEnabled)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->setCaptureUncaughtException(true);
	}

}
void Analytics::logError(string errorId, string message)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logError(errorId.c_str(),message.c_str());
	}

}
void Analytics::logEvent(string eventId)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logEvent(eventId.c_str());
	}

}
void Analytics::logEvent(string eventId, map<string, string> paramMap)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logEvent(eventId.c_str(), &paramMap);
	}

}
void Analytics::logTimedEventBegin(string eventId)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logTimedEventBegin("logTimedEventBegin");
	}

}
void Analytics::logTimedEventEnd(string eventId)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logTimedEventEnd(eventId.c_str());
	}

}

