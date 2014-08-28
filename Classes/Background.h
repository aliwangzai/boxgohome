#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"
USING_NS_CC;

class Background: public Node
{
public:
	Background();
	~Background();

	bool init();
	bool initCloud();

	virtual void update(float dt);

	CREATE_FUNC(Background);
};

#endif