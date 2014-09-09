#include "JumpsItem.h"


JumpsItem::JumpsItem()
{
}


JumpsItem::~JumpsItem()
{
}

JumpsItem* JumpsItem::create(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	auto jumpsItem = new (std::nothrow) JumpsItem;
	if (jumpsItem && jumpsItem->init(valueMap, gidProperties))
	{
		jumpsItem->autorelease();
		return jumpsItem;
	}
	CC_SAFE_RELEASE(jumpsItem);
	return nullptr;
}

bool JumpsItem::init(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	if (!Wall::initWithMap(valueMap)) return false;
	std::string img = gidProperties.find("source")->second.asString();
	if (!Wall::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize()));

	return true;
}