#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class DialogManager: public Ref
{
public:
	static DialogManager* getInstance();
};

#endif