#include "TutorialMenu.h"
#include "GameMap.h"
#include "VisibleRect.h"
#include "BoxSprite.h"
#include "Utils.h"
#include "ArrowSprite.h"

TutorialMenu::TutorialMenu()
{
}


TutorialMenu::~TutorialMenu()
{
}

bool TutorialMenu::init()
{
	this->initGameMap();
	this->initBoxSprite();
	this->initArrowSprite();
	this->initHand();
	this->playAnimate();
	return true;
}

bool TutorialMenu::initGameMap()
{
	std::string filename = "maps/nmap_tutorial.tmx";
	this->m_pGameMap = GameMap::createWithFile(filename);
	this->m_pGameMap->setPosition(VisibleRect::center());
	this->addChild(this->m_pGameMap);
	return true;
}

bool TutorialMenu::initBoxSprite()
{
	ValueMap valueMap = this->m_pGameMap->getHeroValueMap();
	this->m_pBoxSprite = BoxSprite::create(valueMap);
	this->addChild(this->m_pBoxSprite);
	Point point = m_pBoxSprite->getPosition() + 
		m_pGameMap->getPosition() - m_pGameMap->getContentSize() / 2;
	m_pBoxSprite->setPosition(point);
	this->m_pBoxSprite->getPhysicsBody()->setGravityEnable(false);
	return true;
}

bool TutorialMenu::initHand()
{
	this->m_pHand = Sprite::create("ui/pointer.png");
	m_pHand->setAnchorPoint(Vec2(0.4f, 1.0f));
	this->addChild(m_pHand);
	m_pHand->setPosition(VisibleRect::right() + Point(50, 0));
	return true;
}

bool TutorialMenu::initArrowSprite()
{
	m_pArrowSprite = ArrowSprite::create();
	this->addChild(m_pArrowSprite);
	m_pArrowSprite->setPosition(m_pBoxSprite->getPosition());
	return true;
}

void TutorialMenu::update(float dt)
{
	Point localPoint = this->m_pHand->getPosition();
	Point targetPoint = this->m_pBoxSprite->getPosition();
	Vec2 m_vNormalDir = (localPoint - targetPoint).getNormalized();
	int distance = (int)(localPoint - targetPoint).getLength();
	this->m_pArrowSprite->showCurrentFrame(distance);
	this->m_pArrowSprite->changeDir(m_vNormalDir);
}

void TutorialMenu::playAnimate()
{
	m_pHand->runAction(Sequence::create(
		MoveTo::create(1.0f, this->m_pBoxSprite->getPosition()),
		DelayTime::create(0.4f),
		CallFunc::create([=](){
			this->m_pArrowSprite->setPosition(this->m_pBoxSprite->getPosition());
			this->m_pArrowSprite->show();
			this->scheduleUpdate();
		}),
		MoveBy::create(0.5f, Point(-5, -35)),
		MoveBy::create(0.5f, Point(-15, -35)),
		DelayTime::create(0.5f),
		CallFunc::create([=]{
		this->unscheduleUpdate();
		this->m_pArrowSprite->hide();
		this->m_pBoxSprite->runAction(Sequence::create(
			JumpBy::create(1.0f, Point(150, 70), 80, 1),
			DelayTime::create(0.2f),
			CallFunc::create([=](){
				//this->m_pHand->runAction(MoveTo::create(1.0f, this->m_pBoxSprite->getPosition()));
				this->playAnimate();
			}),
			nullptr));
	}),
		nullptr));
}
