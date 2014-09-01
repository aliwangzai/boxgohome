#include "ContactLogic.h"
#include "GameWorld.h"
#include "BoxSprite.h"
#include "GameUI.h"

ContactLogic::ContactLogic()
:m_bIsWin(false)
{
}


ContactLogic::~ContactLogic()
{
}

ContactLogic* ContactLogic::create(GameWorld *gameWorld)
{
	auto contactLogic = new ContactLogic();
	if (contactLogic && contactLogic->initWithGameWorld(gameWorld))
	{
		contactLogic->autorelease();
		return contactLogic;
	}
	return nullptr;
}

bool ContactLogic::initWithGameWorld(GameWorld *gameWorld)
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
	if (body1->getTag() == 4 || body2->getTag() == 4)
		return false;
	return true;
} 

bool ContactLogic::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
	PhysicsShape *shape1= contact.getShapeA();
	PhysicsShape *shape2 = contact.getShapeB();
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
	if (body1->getTag() == 4 || body2->getTag() == 4)
	{
		this->m_bIsWin = true;
	}
}

void ContactLogic::update(float dt)
{
	if (this->m_bIsWin)
	{
		this->unscheduleUpdate();
		this->m_pGameWorld->win();
	}
	
	Vec2 velocity = this->m_pGameWorld->getBoxSprite()->getPhysicsBody()->getVelocity();
	if (velocity.getLengthSq() < 5 * 5 && this->m_pGameWorld->getGameUI()->getJumpCount() <= 0)
	{
		this->unscheduleUpdate();
		this->m_pGameWorld->lose();
	}
	Vec2 position = this->m_pGameWorld->getBoxSprite()->getPosition();
	if (position.y < m_pGameWorld->getBoxSprite()->getContentSize().height / 2)
	{
		this->unscheduleUpdate();
		this->m_pGameWorld->lose();
	}
}

void ContactLogic::loadDefaultData()
{
	this->m_bIsWin = false;
	this->scheduleUpdate();
}
