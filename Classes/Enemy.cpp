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
	if (enemy && enemy->init(valueMap, gidProperties))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_RELEASE(enemy);
	return nullptr;
}

bool Enemy::init(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	if (!Wall::initWithMap(valueMap)) return false;
	std::string img = gidProperties.find("source")->second.asString();
	if (!Wall::initWithFile(img)) return false;
	std::string type = gidProperties.find("type")->second.asString();
	this->setPosition(m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.4f, 1.0f)));
	this->m_wallType = wallType_Enemy;
	this->getPhysicsBody()->setTag(this->m_wallType);
	if (type == "enemy_gray")
		this->getPhysicsBody()->setContactTestBitmask(0x0001);

	
	float delayTime = CCRANDOM_0_1() * 1.5;
	this->schedule(schedule_selector(Enemy::updateVelocity), delayTime);

	return true;
}

void Enemy::updateVelocity(float dt)
{
	float distance = CCRANDOM_0_1() * 200 + 150;
	float delayTime = distance / 100;
	this->unschedule(schedule_selector(Enemy::updateVelocity));
	this->schedule(schedule_selector(Enemy::updateVelocity), delayTime);
	this->getPhysicsBody()->setVelocity(Vec2(0, distance));
}

void Enemy::onExit()
{
	Wall::onExit();
	this->unschedule(schedule_selector(Enemy::updateVelocity));
}
