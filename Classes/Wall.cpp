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


void Wall::setPositionAndRotation()
{
	if (this->m_rotation != 0.0f)
	{
		//this->setAnchorPoint(Vec2(0 , 0));
		//rotate . 
		/*
		 ***
		 *** Vector(center->leftBottom)  (-size.width/2, -size.height/2)
		 *** rotate Vector(center->leftBottom) by given rotation (m_rotation)
		 *** make Vector(leftBottom ->center) 
		 *** Center Point = initPos + Vector(leftBottom ->center )
		 */
		Vec2 lb = this->getContentSize()/2;
		lb.rotate(Vec2::ZERO , -CC_DEGREES_TO_RADIANS(this->m_rotation));
		this->setPosition(this->m_initPos + lb);
		this->setRotation(this->m_rotation);
	}else
	{
		this->setPosition(this->m_initPos + this->getContentSize()/2 );
	}
}

void Wall::setWallType(WallType type)
{
	this->m_wallType = type;
	this->getPhysicsBody()->setTag(this->m_wallType);
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
