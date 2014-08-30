#include "BoxSprite.h"
#include "GameWorld.h"
#include "ArrowSprite.h"

BoxSprite* BoxSprite::create(const ValueMap &valueMap)
{
	auto boxSprite = new BoxSprite();
	if (boxSprite && boxSprite->initWithMap(valueMap))
	{
		boxSprite->autorelease();
		return boxSprite;
	}
	return nullptr;
}

bool BoxSprite::initWithMap(const ValueMap &valueMap)
{
	if (!this->init())return false;

	this->loadDefaultData(valueMap);

	return true;
}

void BoxSprite::loadDefaultData(const ValueMap &valueMap)
{
	float x = valueMap.find("x")->second.asFloat();
	float y = valueMap.find("y")->second.asFloat();
	this->setPosition(Point(x, y) + this->getContentSize() / 2);
	this->getPhysicsBody()->setVelocity(Vec2());
	this->getPhysicsBody()->setAngularVelocity(0);
}

bool BoxSprite::init()
{
	if (!Sprite::initWithFile("3.png")) return false;
	this->m_fMaxForce = 6400;
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.5f)));
	this->getPhysicsBody()->setMass(10.0f);

	this->initBoxAnimate();

	return true;
}

bool BoxSprite::initBoxAnimate()
{

	this->setContactTestBitmask(0x0001);
	return true;
}

void BoxSprite::setCollisionBitmask(int mask)
{
	this->getPhysicsBody()->setCollisionBitmask(mask);
}

void BoxSprite::setCategoryBitmask(int mask)
{
	this->getPhysicsBody()->setCategoryBitmask(mask);
}

void BoxSprite::setContactTestBitmask(int mask)
{
	this->getPhysicsBody()->setContactTestBitmask(mask);
}

void BoxSprite::applyForce(const Vec2 &force)
{
	Vec2 newForce = force;
	float forceSize = force.getLength();
	if (forceSize > m_fMaxForce)
	{
		newForce = force * (m_fMaxForce / forceSize);
	}
	this->getPhysicsBody()->applyImpulse(newForce);
}
