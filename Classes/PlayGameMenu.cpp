#include "PlayGameMenu.h"
#include "GameMap.h"
#include "VisibleRect.h"
#include "BoxSprite.h"
#include "Utils.h"
#include "BaseEntity.h"

PlayGameMenu::PlayGameMenu()
:m_pBoxSprite(nullptr),
m_pGameMap(nullptr)
{
}


PlayGameMenu::~PlayGameMenu()
{
}

bool PlayGameMenu::init()
{
	this->initGameMap();
	this->initBoxSprite();
	this->initListener();
	this->scheduleUpdate();

	return true;
}

bool PlayGameMenu::initBoxSprite()
{
	this->m_pBoxSprite = BoxSprite::create();
	float x = CCRANDOM_0_1() * Utils::getWinSize().width / 2 + Utils::getWinSize().width / 2;
	this->m_pBoxSprite->setPosition(x - m_pBoxSprite->getContentSize().width / 2 , Utils::getWinSize().height);
	this->addChild(this->m_pBoxSprite);
	return true;
}

bool PlayGameMenu::initGameMap()
{
	std::string filename = "maps/nplaygame_menu.tmx";
	this->m_pGameMap = GameMap::createWithFile(filename);
	this->m_pGameMap->setPosition(VisibleRect::center());
	this->addChild(this->m_pGameMap);
	return true;
}

bool PlayGameMenu::initListener()
{
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(PlayGameMenu::onContactBegin, this);
	listener->onContactPreSolve = CC_CALLBACK_2(PlayGameMenu::onContactPreSolve, this);
	listener->onContactPostSolve = CC_CALLBACK_2(PlayGameMenu::onContactPostSolve, this);
	listener->onContactSeperate = CC_CALLBACK_1(PlayGameMenu::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool PlayGameMenu::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody *bodyA = contact.getShapeA()->getBody();
	PhysicsBody *bodyB = contact.getShapeB()->getBody();
	if (bodyA->getTag() != Type_Flag && bodyB->getTag() != Type_Flag)
	{
		return true;
	}
	return false;
}

bool PlayGameMenu::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{

	return true;
}

void PlayGameMenu::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{

}

void PlayGameMenu::onContactSeperate(PhysicsContact& contact)
{
	
}

void PlayGameMenu::update(float dt)
{
	float length = this->m_pBoxSprite->getPhysicsBody()->getVelocity().getLengthSq();
	if (length <= 15 * 15)
	{
		float x = (CCRANDOM_0_1() - 0.5) * 2;
		float y = (CCRANDOM_0_1() - 0.5) * 2;
		this->m_pBoxSprite->getPhysicsBody()->applyImpulse(Vec2(x, y) * 50);
	}
	if (this->m_pBoxSprite->getPositionY() < -this->m_pBoxSprite->getContentSize().height / 2)
	{
		float x = CCRANDOM_0_1() * Utils::getWinSize().width / 2 + Utils::getWinSize().width / 2;
		this->m_pBoxSprite->setPosition(x - m_pBoxSprite->getContentSize().width / 2, Utils::getWinSize().height + 
			m_pBoxSprite->getContentSize().height);
		this->m_pBoxSprite->getPhysicsBody()->setVelocity(Vec2());
	}
}

void PlayGameMenu::onExit()
{
	Node::onExit();
	_eventDispatcher->removeEventListenersForTarget(this);
	this->unscheduleUpdate();
	
}
