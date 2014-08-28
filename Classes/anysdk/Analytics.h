#ifndef __MY_ANALYTICS_H__
#define __MY_ANALYTICS_H__

#include "AgentManager.h"
#include "string.h"
using namespace anysdk::framework;
using namespace std;
class Analytics
{
public:
    static Analytics* getInstance();
    static void purge();


    //统计系统
        void startSession();

        void stopSession();

        void setSessionContinueMillis(long millis);
    	void setCaptureUncaughtException(bool isEnabled);
    	void logError(string errorId, string message);
    	void logEvent(string eventId);
    	void logEvent(string eventId, map<string, string> paramMap);
    	void logTimedEventBegin(string eventId);
    	void logTimedEventEnd(string eventId);



private:
    	Analytics();
    virtual ~Analytics();

    static Analytics* _pInstance;

};

#endif
