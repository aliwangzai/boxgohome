#include "Utils.h"

SpriteFrame* Utils::getSpriteFrame(std::string szSpriteFrameName)
{
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szSpriteFrameName);
	if (frame == nullptr)
	{
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(szSpriteFrameName);
		auto size = texture->getContentSize();
		frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));
	}
	return frame;
}

Sprite* Utils::createSprite(std::string szSprite)
{
	auto frame = Utils::getSpriteFrame(szSprite);
	if (frame == nullptr)
	{
		return Sprite::create(szSprite);
	}
	return Sprite::createWithSpriteFrame(frame);
}

Size Utils::getWinSize()
{
	return Director::getInstance()->getVisibleSize();
}

std::string Utils::getWallByType(int type)
{
	std::string fileName;
	switch (type)
	{
	case 1://���ŵ���ɫש
		fileName = "maps/2.png";
		break;
	case 2://���ŵ���ɫש
		fileName = "maps/2_1.png";
		break;
	case 3://���ŵĺ�ɫש
		fileName = "maps/42.png";
		break;
	case 4://����
		fileName = "maps/41.png";
	}
	return fileName;
}