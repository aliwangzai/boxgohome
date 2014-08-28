#include "YellowWall.h"
#include "Utils.h"

YellowWall::YellowWall()
{
}


YellowWall::~YellowWall()
{
}

YellowWall* YellowWall::create(const ValueMap &valueMap)
{
	auto blueWall = new YellowWall();
	if (blueWall && blueWall->init(valueMap))
	{
		blueWall->autorelease();
		return blueWall;
	}
	return nullptr;
}

bool YellowWall::init(const ValueMap &valueMap)
{
	if (!Wall::initWithMap(valueMap)) return false;
	std::string img = Utils::getWallByType(this->m_nType);
	if (!Wall::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	if (this->m_nType == 3)
	{
		this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize()));
		this->setContactTestBitmask(0x0001);
	}
	else if (this->m_nType == 4)
	{
		this->playFlagAnimate();
		this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize()));
		this->setContactTestBitmask(0x0002);
	}
	this->getPhysicsBody()->setTag(m_nType);
	return true;
}

void YellowWall::playFlagAnimate()
{
	Vector<SpriteFrame*> frames;
	for (int i = 1; i <= 10; i++)
	{
		char buffer[128];
		sprintf(buffer, "flag/%d.png", i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		frames.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}
