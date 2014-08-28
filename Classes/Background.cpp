#include "Background.h"
#include "VisibleRect.h"

#define CLOUD_NUM 5

Background::Background()
{
}

Background::~Background()
{
}

bool Background::init()
{
	auto bgSprite = Sprite::create("39.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(VisibleRect::center());

	this->initCloud();

	this->scheduleUpdate();

	return true;
}

bool Background::initCloud()
{
	Point cloudPoss[CLOUD_NUM] = {
		VisibleRect::center() + Point(200, 100),
		VisibleRect::left(),
		VisibleRect::right() - Point(200, 250),
		VisibleRect::center() + Point(-100, -100),
		VisibleRect::top() + Point(-200, -100)
	};
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		auto cloudSprite = Sprite::create("1.png");
		this->addChild(cloudSprite, 0, 100 + i);
		cloudSprite->setPosition(cloudPoss[i]);
	}
	return true;
}

void Background::update(float dt)
{
	static float offset = 5.0f;
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		auto sprite = this->getChildByTag(100 + i);
		Point newPoint = sprite->getPosition() + Point((i + offset) / 6.0f, 0);
		if ((newPoint.x - sprite->getContentSize().width / 2) > VisibleRect::right().x)
		{
			offset = CCRANDOM_0_1() * 3 + 3;
			newPoint.x = -sprite->getContentSize().width / 2;
		}
		sprite->setPosition(newPoint);
	}
}
