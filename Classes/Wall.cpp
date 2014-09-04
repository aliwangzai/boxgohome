#include "Wall.h"


Wall::Wall()
{
}

Wall::~Wall()
{
}

bool Wall::initWithMap(const ValueMap &valueMap)
{
	float x = valueMap.find("x")->second.asFloat();
	float y = valueMap.find("y")->second.asFloat();
	this->m_nGid = valueMap.find("gid")->second.asInt();
	this->m_nType = valueMap.find("type")->second.asInt();
	this->m_sName = valueMap.find("name")->second.asString();
	this->m_rotation = valueMap.find("rotation")->second.asFloat();
	this->m_initPos = Point(x, y);
	return true;
}

void Wall::setCollisionBitmask(int mask)
{
	this->getPhysicsBody()->setCollisionBitmask(mask);
}

void Wall::setContactTestBitmask(int mask)
{
	this->getPhysicsBody()->setContactTestBitmask(mask);
}

void Wall::setCategoryBitmask(int mask)
{
	this->getPhysicsBody()->setCategoryBitmask(mask);
}
