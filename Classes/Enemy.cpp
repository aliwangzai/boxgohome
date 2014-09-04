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

	this->setPosition(m_initPos + this->getContentSize() / 2);
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.4f, 1.0f)));
	this->m_wallType = wallType_Enemy;
	this->getPhysicsBody()->setTag(this->m_wallType);
	this->getPhysicsBody()->setContactTestBitmask(0x0001);

	//this->scheduleUpdate();
	static float distance = 350.0f;
	auto seqAction = Sequence::create(
		CallFunc::create([=](){
			this->getPhysicsBody()->setVelocity(Vec2(0, distance));
			distance = CCRANDOM_0_1() * 50 + 300;
		}),
		DelayTime::create(4.0f),
		nullptr
		);
	this->runAction(RepeatForever::create(seqAction));

	return true;
}
