#include "ContactLogic.h"
#include "GameWorld.h"

ContactLogic::ContactLogic()
:m_bIsWin(false)
{
}


ContactLogic::~ContactLogic()
{
}

ContactLogic* ContactLogic::create(const GameWorld *gameWorld)
{
	auto contactLogic = new ContactLogic();
	if (contactLogic && contactLogic->initWithGameWorld(gameWorld))
	{
		contactLogic->autorelease();
		return contactLogic;
	}
	return nullptr;
}

bool ContactLogic::initWithGameWorld(const GameWorld *gameWorld)
{
	this->m_pGameWorld = gameWorld;

	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(ContactLogic::onContactBegin, this);
	physicsListener->onContactPostSolve = CC_CALLBACK_2(ContactLogic::onContactPostSolve, this);
	physicsListener->onContactPreSolve = CC_CALLBACK_2(ContactLogic::onContactPreSolve, this);
	physicsListener->onContactSeperate = CC_CALLBACK_1(ContactLogic::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

	this->scheduleUpdate();

	return true;
}

bool ContactLogic::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody *body1 = contact.getShapeA()->getBody();
	PhysicsBody *body2 = contact.getShapeB()->getBody();
	//CCLOG("-------------------------------- onContactBegin -------------------------------- %d %d", body1->getTag(), body2->getTag());
	if (body1->getTag() != 4 && body2->getTag() != 4)
	{
		return true;
	}
	else
	{
		this->m_bIsWin = true;
	}
	return false;
} 

bool ContactLogic::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
	PhysicsBody *body1 = contact.getShapeA()->getBody();
	PhysicsBody *body2 = contact.getShapeB()->getBody();
	//CCLOG("-------------------------------- onContactPreSolve ----------------------------- %d %d", body1->getTag(), body2->getTag());
	return true;
}

void ContactLogic::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
	PhysicsBody *body1 = contact.getShapeA()->getBody();
	PhysicsBody *body2 = contact.getShapeB()->getBody();
	//CCLOG("-------------------------------- onContactPostSolve --------------------------- %d %d", body1->getTag(), body2->getTag());
}

void ContactLogic::onContactSeperate(PhysicsContact& contact)
{
	PhysicsBody *body1 = contact.getShapeA()->getBody();
	PhysicsBody *body2 = contact.getShapeB()->getBody();
	//CCLOG("-------------------------------- onContactSeperate ---------------------------- %d %d", body1->getTag(), body2->getTag());
}

void ContactLogic::update(float dt)
{
	if (this->m_bIsWin)
	{
		this->unscheduleUpdate();
		CCLOG("oh win !, enter next level");
	}
}
