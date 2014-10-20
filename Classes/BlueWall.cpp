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
	getTexture()->setAliasTexParameters();
	setPositionAndRotation();
	this->setPhysicsBody(PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.4f, 1.0f), 0));//ÃÜ¶È µ¯Á¦ Ä¦²ÁÁ¦

	setContactTestBitmask(0x0002);
	setEntityType(Type_Normal);
	return true;
}

bool BlueWall::contactLogicBegin(PhysicsContact &contact, ContactLogic *logic)
{
	PhysicsBody * body = Utils::getBody(contact, Type_BoxSprite);
	if (body == nullptr)
		return false;

	float moment = body->getVelocity().getLengthSq();
	if (moment > 400 * 400)
	{
		this->contactEffect(contact);
	}
	return true;
}

void BlueWall::contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic)
{
}

void BlueWall::contactEffect(PhysicsContact &contact)
{
	ParticleSystem *particleSystem = ParticleSystemQuad::create("effect/Contact.plist");
	const PhysicsContactData *data = contact.getContactData();
	Vec2 position = data->points[0];
	particleSystem->setPosition(position);
	particleSystem->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFuncN::create([=](Node *node){
		node->removeFromParent();
	}),
		nullptr));
	auto scene = Director::getInstance()->getRunningScene();
	scene->addChild(particleSystem, 100);
}
