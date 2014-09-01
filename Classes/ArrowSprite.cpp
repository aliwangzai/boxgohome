#include "ArrowSprite.h"


ArrowSprite::ArrowSprite()
{
}


ArrowSprite::~ArrowSprite()
{
}

bool ArrowSprite::init()
{
	if (!Sprite::init()) return false;

	this->setAnchorPoint(Point(0, 0.5));
	return true;
}

void ArrowSprite::showCurrentFrame(int distance)
{
	if (distance >= 7 && distance <= 221)
	{
		char buffer[128];
		sprintf(buffer, "arrow/%d.png", distance);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		this->setSpriteFrame(frame);
		BlendFunc blendFun = { 1, 1 };
		this->setBlendFunc(blendFun);
	}
}

void ArrowSprite::show()
{
	this->setVisible(true);
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("arrow/7.png");
	this->setSpriteFrame(frame);
	BlendFunc blendFun = { 1, 1 };
	this->setBlendFunc(blendFun);
}

void ArrowSprite::changeDir(const Vec2 &normalDir)
{
	float radians = atan2(normalDir.y, normalDir.x);
	float degree = CC_RADIANS_TO_DEGREES(radians);
	this->setRotation(-degree);
}


