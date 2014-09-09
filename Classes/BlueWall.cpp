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
	if (!BaseEntity::initWithMap(valueMap )) return false;
	//std::string img = Utils::getWallByType(this->m_nType);
	std::string img = gidProperties.find("source")->second.asString();
	if (!BaseEntity::initWithFile(img)) return false;
	setPositionAndRotation();
	this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.4f, 1.0f), 0));//ÃÜ¶È µ¯Á¦ Ä¦²ÁÁ¦

	setEntityType(Type_Normal);
	return true;
}
