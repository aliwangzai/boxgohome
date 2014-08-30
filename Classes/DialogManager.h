#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "cocos2d.h"
#include "Dialog.h"
USING_NS_CC;

class LevelComplete;
class LevelCompleteLoss;
class DialogManager: public Ref
{
public:
	static DialogManager* getInstance();

	Dialog* showLvelComplete(void *data, DialogCallback callback);

	Dialog* showLevelCompleteLoss(void *data, DialogCallback callback);
};

#endif