#include "YellowWall.h"
#include "Utils.h"
#include "ContactLogic.h"

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
	if (!BaseEntity::initWithMap(valueMap)) return false;
	//std::string img = Utils::getWallByType(this->m_nType);
	std::string img = gidProperties.find("source")->second.asString();
	if (!BaseEntity::initWithFile(img)) return false;
	setPositionAndRotation();
	std::string type = gidProperties.find("type")->second.asString();
	if (type == "target")
	{
		this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 1.0f), 0));
		this->setContactTestBitmask(0x0001);
		setEntityType(Type_Yellow);
	}
	else if (type == "flag")
	{
		this->playFlagAnimate();
		this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize()));
		this->setContactTestBitmask(0x0002);
		setEntityType(Type_Flag);
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

bool YellowWall::contactLogicBegin(PhysicsContact &contact, ContactLogic *logic)
{
	if (this->m_entityType == Type_Flag)
	{
		logic->setWinState(true);
		return false;
	}
	return true;
}
void YellowWall::contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic)
{

}
