#include "BlueWall.h"
#include "Utils.h"

BlueWall::BlueWall()
{
}


BlueWall::~BlueWall()
{
}

BlueWall* BlueWall::create(const ValueMap &valueMap)
{
	auto blueWall = new BlueWall();
	if (blueWall && blueWall->init(valueMap))
	{
		blueWall->autorelease();
		return blueWall;
	}
	return nullptr;
}

bool BlueWall::init(const ValueMap &valueMap)
{
	if (!Wall::initWithMap(valueMap)) return false;
	std::string img = Utils::getWallByType(this->m_nType);
	if (!Wall::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.4f, 1.0f), 0));//ÃÜ¶È µ¯Á¦ Ä¦²ÁÁ¦
	this->getPhysicsBody()->setTag(this->m_nType);
	this->setContactTestBitmask(0x0002);
	return true;
}
