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
	return true;
}

void ContactLogic::startGame()
{
	this->m_bIsLose = false;
	this->m_bIsWin = false;
	this->initListener();
}

bool ContactLogic::initListener()
{
	m_pEventListener = EventListenerPhysicsContact::create();
	m_pEventListener->onContactBegin = CC_CALLBACK_1(ContactLogic::onContactBegin, this);
	m_pEventListener->onContactPostSolve = CC_CALLBACK_2(ContactLogic::onContactPostSolve, this);
	m_pEventListener->onContactPreSolve = CC_CALLBACK_2(ContactLogic::onContactPreSolve, this);
	m_pEventListener->onContactSeperate = CC_CALLBACK_1(ContactLogic::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pEventListener, this);

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
	auto baseEntity1 = static_cast<BaseEntity*>(contact.getShapeA()->getBody()->getNode());
	auto baseEntity2 = static_cast<BaseEntity*>(contact.getShapeB()->getBody()->getNode());
	if ((baseEntity1 != nullptr && baseEntity1->contactLogicPreSolve(contact, solve, this)) &&
		(baseEntity2 != nullptr && baseEntity2->contactLogicPreSolve(contact, solve, this)))
	{
		return true;
	}
	return false;
}

void ContactLogic::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
	auto baseEntity1 = static_cast<BaseEntity*>(contact.getShapeA()->getBody()->getNode());
	auto baseEntity2 = static_cast<BaseEntity*>(contact.getShapeB()->getBody()->getNode());
	if (baseEntity1 != nullptr)
		baseEntity1->contactLogicPostSolve(contact, solve, this);
	if (baseEntity2 != nullptr)
		baseEntity2->contactLogicPostSolve(contact, solve, this);
}

void ContactLogic::onContactSeperate(PhysicsContact& contact)
{
	auto baseEntity1 = static_cast<BaseEntity*>(contact.getShapeA()->getBody()->getNode());
	auto baseEntity2 = static_cast<BaseEntity*>(contact.getShapeB()->getBody()->getNode());
	if ( baseEntity1 != nullptr)
		baseEntity1->contactLogicSeperate(contact,this);
	if ( baseEntity2 != nullptr)
		baseEntity2->contactLogicSeperate(contact,this);
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
	this->_eventDispatcher->removeEventListener(this->m_pEventListener);
}
