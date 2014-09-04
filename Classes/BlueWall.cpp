#include "BlueWall.h"
#include "Utils.h"

BlueWall::BlueWall()
{
}


BlueWall::~BlueWall()
{
}

BlueWall* BlueWall::create(const ValueMap &valueMap , const ValueMap &gidProperties)
{
	auto blueWall = new BlueWall();
	if (blueWall && blueWall->init(valueMap , gidProperties))
	{
		blueWall->autorelease();
		return blueWall;
	}
	return nullptr;
}

bool BlueWall::init(const ValueMap &valueMap , const ValueMap &gidProperties)
{
	if (!Wall::initWithMap(valueMap )) return false;
	//std::string img = Utils::getWallByType(this->m_nType);
	std::string img = gidProperties.find("source")->second.asString();
	if (!Wall::initWithFile(img)) return false;
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
	this->m_wallType = wallType_Normal;
	this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.4f, 1.0f), 0));//ÃÜ¶È µ¯Á¦ Ä¦²ÁÁ¦
	this->getPhysicsBody()->setTag(this->m_wallType);
	return true;
}
