#include "WoodenCrate.h"
#include "Utils.h"

WoodenCrate::WoodenCrate()
{
}


WoodenCrate::~WoodenCrate()
{
}

WoodenCrate* WoodenCrate::create(const ValueMap &valueMap, const ValueMap & gidProperties)
{
	auto woodenCrate = new (std::nothrow) WoodenCrate;
	if (woodenCrate && woodenCrate->init(valueMap , gidProperties))
	{
		woodenCrate->autorelease();
		return woodenCrate;
	}
	CC_SAFE_RELEASE(woodenCrate);
	return nullptr;
}

bool WoodenCrate::init(const ValueMap &valueMap, const ValueMap & gidProperties)
{
	if (!Wall::initWithMap(valueMap )) return false;
	//std::string img = Utils::getWallByType(this->m_nType);
	std::string img = gidProperties.find("source")->second.asString();
	if (!Wall::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.001f, 0.5f, 0.5f)));
	
	return true;
}
