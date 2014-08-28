#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"
USING_NS_CC;

class Utils: public Ref
{
public:
	static SpriteFrame* getSpriteFrame(std::string szSpriteFrameName);

	static Sprite* createSprite(std::string szSpriteName);

	static std::string getWallByType(int type);

	static Size getWinSize();
};

#endif