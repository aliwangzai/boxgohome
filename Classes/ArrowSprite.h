#ifndef __ARROWSPRITE_H__
#define __ARROWSPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

class ArrowSprite: public Sprite
{
public:
	ArrowSprite();
	~ArrowSprite();

	bool init();

	void show();
	void hide();
	void showCurrentFrame(int distance);
	void changeDir(const Vec2 &normalDir);

	CREATE_FUNC(ArrowSprite);

private:

};

#endif