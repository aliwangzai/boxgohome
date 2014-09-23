#include "ContactLogic.h"
#include "GameWorld.h"
#include "BoxSprite.h"
#include "GameUI.h"
#include "BaseEntity.h"

ContactLogic::ContactLogic()
:m_bIsWin(false),
m_bIsLose(false)
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
	auto baseEntity1 = static_cast<BaseEntity*>(contact.getShapeA()->getBody()->getNode());
	auto baseEntity2 = static_cast<BaseEntity*>(contact.getShapeB()->getBody()->getNode());
	if ((baseEntity1 != nullptr && baseEntity1->contactLogicBegin(contact, this)) && 
		(baseEntity2 != nullptr && baseEntity2->contactLogicBegin(contact, this)))
	{
		return true;
	}
	return false;
} 

bool ContactLogic::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
	return true;
}

void ContactLogic::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
}

void ContactLogic::onContactSeperate(PhysicsContact& contact)
{
	auto baseEntity1 = static_cast<BaseEntity*>(contact.getShapeA()->getBody()->getNode());
	auto baseEntity2 = static_cast<BaseEntity*>(contact.getShapeB()->getBody()->getNode());
	if ( baseEntity1 != nullptr)
		baseEntity1->contactLogicSeperate(contact,this);
	if ( baseEntity2 != nullptr)
		baseEntity2->contactLogicSeperate(contact,this);
// 	if(body1->getTag() == wallType_broken)
// 	{
// 		//remove brick
// 		body1->getNode()->removeFromParentAndCleanup(true);
// 		//remove body1
// 		//NotificationCenter::sharedNotificationCenter()->postNotification("ContactLogic." , this);
// 	}
// 	if(body2->getTag() == wallType_broken)
// 		body1->getNode()->removeFromParentAndCleanup(true);
}

void ContactLogic::update(float dt)
{
	Node::update(dt);

	if (this->m_bIsWin)
	{
		this->m_pGameWorld->win();
		this->unscheduleUpdate();
	}
	Vec2 velocity = this->m_pGameWorld->getBoxSprite()->getPhysicsBody()->getVelocity();
	if (velocity.getLengthSq() < 5 * 5 && this->m_pGameWorld->getGameUI()->getJumpCount() <= 0)
	{
		this->unscheduleUpdate();
		this->m_pGameWorld->lose();
	}
	Vec2 position = this->m_pGameWorld->getBoxSprite()->getPosition();
	if (position.y < m_pGameWorld->getBoxSprite()->getContentSize().height / 2 || m_bIsLose)
	{
		this->unscheduleUpdate();
		this->m_pGameWorld->lose();
	}
}

void ContactLogic::loadDefaultData()
{
	this->m_bIsWin = false;
	this->m_bIsLose = false;
	this->scheduleUpdate();
}
