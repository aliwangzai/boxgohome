#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "cocos2d.h"
USING_NS_CC;

class Obstacle: public Sprite
{
private:
	enum{default_type = -1};
public:
	Obstacle();
	~Obstacle();
};

#endif