#include "GameWorld.h"
#include "VisibleRect.h"
#include "BoxSprite.h"
#include "Background.h"
#include "GameMap.h"
#include "ArrowSprite.h"
#include "GameUI.h"
#include "ContactLogic.h"

GameWorld::GameWorld()
:m_pArrowSprite(nullptr),
m_pBoxSprite(nullptr),
m_pContactLogic(nullptr),
m_pGameMap(nullptr),
m_pGameUI(nullptr)
{

}

GameWorld::~GameWorld()
{
	
}

Scene* GameWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	if (scene)
	{	
		auto layer = GameWorld::create();
		scene->addChild(layer);
		return scene;
	}
	return nullptr;
}

bool GameWorld::init()
{
	if (!Node::init()) return false;

	this->initBackground();
	this->initGameMap();

	this->initListener();
	this->initBoxSprite();
	this->initArrowSprite();
	this->scheduleUpdate();
	this->initGameUI();
	this->initContactLogic();
	return true;
}

bool GameWorld::initContactLogic()
{
	this->m_pContactLogic = ContactLogic::create(this);
	this->addChild(this->m_pContactLogic);
	return true;
}

bool GameWorld::initGameUI()
{
	m_pGameUI = GameUI::create();
	this->addChild(m_pGameUI);
	return true;
}

bool GameWorld::initArrowSprite()
{
	m_pArrowSprite = ArrowSprite::create();
	this->addChild(m_pArrowSprite);
	m_pArrowSprite->setPosition(m_pBoxSprite->getPosition());
	return true;
}

bool GameWorld::initBoxSprite()
{
	ValueMap valueMap = this->m_pGameMap->getHeroValueMap();
	this->m_pBoxSprite = BoxSprite::create(valueMap);
	this->addChild(this->m_pBoxSprite);
	return true;
}

bool GameWorld::initBackground()
{
	auto background = Background::create();
	this->addChild(background);
	return true;
}

bool GameWorld::initGameMap()
{
	m_pGameMap = GameMap::createWithFile("maps/map_2.tmx");
	m_pGameMap->setPosition(VisibleRect::leftBottom());
	this->addChild(m_pGameMap);
	return true;
}

bool GameWorld::initListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

bool GameWorld::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	if (this->m_pBoxSprite->getBoundingBox().containsPoint(pTouch->getLocation()))
	{
		Point localPoint = pTouch->getLocation();
		Point targetPoint = this->m_pBoxSprite->getPosition();
		m_vNormalDir = (localPoint - targetPoint).getNormalized();
		int distance = (int)(localPoint - targetPoint).getLength();
		this->m_pArrowSprite->showCurrentFrame(distance);
		this->m_pArrowSprite->changeDir(m_vNormalDir);
		m_pArrowSprite->show();
		return true;
	}
	return false;
}
void GameWorld::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	Point localPoint = pTouch->getLocation();
	Point targetPoint = this->m_pBoxSprite->getPosition();
	m_vNormalDir = (localPoint - targetPoint).getNormalized();
	int distance = (int)(localPoint - targetPoint).getLength();
	this->m_pArrowSprite->showCurrentFrame(distance);
	this->m_pArrowSprite->changeDir(m_vNormalDir);
}
void GameWorld::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	m_pArrowSprite->setVisible(false);
	Point localPoint = pTouch->getLocation();
	Point targetPoint = this->m_pBoxSprite->getPosition();
	m_vNormalDir = (localPoint - targetPoint).getNormalized();
	int distance = (int)(localPoint - targetPoint).getLength();
	this->m_pBoxSprite->applyForce(-m_vNormalDir * distance * 20);
}

void GameWorld::onEnter()
{
	Node::onEnter();

	_physicsWorld = this->getScene()->getPhysicsWorld();
	_physicsWorld->setGravity(Vect(0.0f, -300.0f));
	//_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	/*auto node = Node::create();
	node->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size));
	node->setPosition(VisibleRect::center());
	this->addChild(node);*/
}

void GameWorld::update(float dt)
{
	if (m_pArrowSprite->isVisible())
	{
		Point newPoint = -m_vNormalDir * this->m_pBoxSprite->getContentSize().width / 2 +
			this->m_pBoxSprite->getPosition();
		this->m_pArrowSprite->setPosition(newPoint);
	}
}

void GameWorld::win()
{

}

void GameWorld::lose()
{

}
