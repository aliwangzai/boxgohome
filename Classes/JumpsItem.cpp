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
	if (!BaseEntity::initWithMap(valueMap)) return false;
	std::string img = gidProperties.find("source")->second.asString();
	if (!BaseEntity::initWithFile(img)) return false;
	this->setPosition(this->m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize()));
	this->getPhysicsBody()->setTag(Type_Item_Jump_3);
	this->setContactTestBitmask(0x0001);
	return true;
}

bool JumpsItem::contactLogicBegin(PhysicsContact &contact, ContactLogic *logic)
{
	this->removeFromParent();
	return false;
}
void JumpsItem::contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic)
{

}