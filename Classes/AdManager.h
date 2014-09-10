#ifndef __ADMANAGER_H__
#define __ADMANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class AdManager: public Ref
{
public:
	static AdManager* getInstance();

	void showBannerAD();
	void hideBannerAD();
};

#endif