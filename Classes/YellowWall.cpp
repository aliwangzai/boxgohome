#include "YellowWall.h"
#include "Utils.h"

YellowWall::YellowWall()
{
}


YellowWall::~YellowWall()
{
}

YellowWall* YellowWall::create(const ValueMap &valueMap, const ValueMap & gidProperties)
{
	auto blueWall = new YellowWall();
	if (blueWall && blueWall->init(valueMap , gidProperties))
	{
		blueWall->autorelease();
		return blueWall;
	}
	return nullptr;
}

bool YellowWall::init( const ValueMap &valueMap, const ValueMap & gidProperties )
{
	if (!Wall::initWithMap(valueMap )) return false;
	//std::string img = Utils::getWallByType(this->m_nType);
	std::string img = gidProperties.find("source")->second.asString();
	if (!Wall::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	std::string type = gidProperties.find("type")->second.asString();
	if (type == "target")
	{
		this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 1.0f), 0));
		this->setContactTestBitmask(0x0001);
		this->m_wallType = wallType_Yellow;
		this->getPhysicsBody()->setTag(this->m_wallType);
	}
	else if (type == "flag")
	{
		this->playFlagAnimate();
		this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize()));
		this->setContactTestBitmask(0x0002);
		this->m_wallType = wallType_Flag;
		this->getPhysicsBody()->setTag(this->m_wallType);
	}
	
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
