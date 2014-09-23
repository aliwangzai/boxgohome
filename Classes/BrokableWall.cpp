#include "BrokableWall.h"
#include "Utils.h"

BrokableWall::BrokableWall()
:m_lLastTime(0)
{

}

BrokableWall::~BrokableWall()
{

}

BrokableWall* BrokableWall::create( const ValueMap &valueMap , const ValueMap &gidProperties )
{
	auto blueWall = new BrokableWall();
	if (blueWall && blueWall->init(valueMap , gidProperties))
	{
		blueWall->autorelease();
		return blueWall;
	}
	return nullptr;
}

bool BrokableWall::init( const ValueMap &valueMap , const ValueMap &gidProperties )
{
	if (!BaseEntity::initWithMap(valueMap )) return false;
	//std::string img = Utils::getWallByType(this->m_nType);
	std::string img = gidProperties.find("source")->second.asString();
	m_durability = gidProperties.find("durability")->second.asInt();
	if (!BaseEntity::initWithFile(img)) return false;
	setPositionAndRotation();
	this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.4f, 1.0f), 0));//ÃÜ¶È µ¯Á¦ Ä¦²ÁÁ¦

	setContactTestBitmask(0x0002);
	setEntityType(Type_Brokable);
	return true;
}

bool BrokableWall::contactLogicBegin( PhysicsContact &contact, ContactLogic *logic )
{
	return true;
}

void BrokableWall::contactLogicSeperate( PhysicsContact &contact, ContactLogic *logic )
{
	PhysicsBody* body1 = contact.getShapeA()->getBody();
	PhysicsBody* body2 = contact.getShapeB()->getBody();
	if (body1 != nullptr && body2 != nullptr)
	{
		if (body1->getTag() == Type_BoxSprite || body2->getTag() == Type_BoxSprite)
		{
			long long currentTime = Utils::getCurrentTime();
			CCLOG("%d ---------------------------------------------------------", currentTime - m_lLastTime);
			if (currentTime - m_lLastTime > 500)
			{
				m_lLastTime = currentTime;
				m_durability--;
				if (m_durability <= 0)
				{
					m_lLastTime = 0;
					this->removeFromParent();
				}
			}
		}
	}
}

