#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

typedef std::function<bool(void *data)> DialogCallback;

class DialogManager: public Ref
{
public:
	static DialogManager* getInstance();

	void showLvelComplete(void *data, DialogCallback callback);
};

#endif