#include "WoodenCrate.h"
#include "Utils.h"

WoodenCrate::WoodenCrate()
{
}


WoodenCrate::~WoodenCrate()
{
}

WoodenCrate* WoodenCrate::create(const ValueMap &valueMap)
{
	auto woodenCrate = new (std::nothrow) WoodenCrate;
	if (woodenCrate && woodenCrate->init(valueMap))
	{
		woodenCrate->autorelease();
		return woodenCrate;
	}
	CC_SAFE_RELEASE(woodenCrate);
	return nullptr;
}

bool WoodenCrate::init(const ValueMap &valueMap)
{
	if (!Wall::initWithMap(valueMap)) return false;

	std::string img = Utils::getWallByType(this->m_nType);
	if (!Wall::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.01f, 0.5f, 0.5f)));

	return true;
}
