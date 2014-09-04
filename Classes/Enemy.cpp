#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	auto enemy = new (std::nothrow) Enemy;
	if (enemy && enemy->initWithMap(valueMap, gidProperties))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_RELEASE(enemy);
	return nullptr;
}

bool Enemy::initWithMap(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	std::string img = gidProperties.find("source")->second.asString();
	if (!Sprite::initWithFile(img)) return false;

	float x = valueMap.find("x")->second.asFloat();
	float y = valueMap.find("y")->second.asFloat();
	this->m_nGid = valueMap.find("gid")->second.asInt();
	this->m_nType = valueMap.find("type")->second.asInt();
	this->m_sName = valueMap.find("name")->second.asString();
	this->m_rotation = valueMap.find("rotation")->second.asFloat();

	this->m_initPos = Point(x, y);
	this->setPosition(m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.4f, 1.0f)));

	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	if (this->getPosition().y > this->m_initPos.y + 200){
		Vec2 direction = Vec2(0, 1);
		Vec2 force = direction * 100;
		this->getPhysicsBody()->applyForce(force);
	}
}