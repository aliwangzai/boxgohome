#include "Welcome.h"
#include "VisibleRect.h"
#include "Background.h"
#include "GameWorld.h"
#include "GameMap.h"
#include "BoxSprite.h"
#include "MenuLayer.h"

Scene* Welcome::createScene()
{
	auto scene = Scene::create();
	if (scene)
	{
		auto layer = Welcome::create();
		scene->addChild(layer);
		return scene;
	}
	return nullptr;
}

bool Welcome::init()
{
	this->initLoadResource();
	this->initBackground();
	this->initTitle();
	this->initMenu();
	this->initEdgeMap();
	this->initHero();
	return true;
}

bool Welcome::initLoadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("entity/hero/heroTexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("entity/hero/arrowTexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("entity/flag/flagTexture.plist");

	return true;
}

bool Welcome::initEdgeMap()
{
	m_pGameMap = GameMap::createWithFile("maps/welcome.tmx");
	m_pGameMap->setPosition(VisibleRect::leftBottom());
	this->addChild(m_pGameMap);
	return true;
}

bool Welcome::initMenu()
{
	auto moreGameItem = MenuItemFont::create("More Game", [=](Ref *pSender){
		
	});
	auto startItem = MenuItemFont::create("Play", [](Ref *pSender){
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	auto menu = Menu::create(moreGameItem, startItem, nullptr);
	this->addChild(menu);
	menu->alignItemsVerticallyWithPadding(10);
	menu->setPosition(VisibleRect::center() + Point(0, -100));
	return true;
}

bool Welcome::initBackground()
{
	auto background = Background::create();
	this->addChild(background);
	return true;
}

bool Welcome::initTitle()
{
	m_pJumpBoxTitle = Label::createWithBMFont("fonts/base_font.fnt", "Jumping Box");
	auto reincarTitle = Label::createWithBMFont("fonts/base_font.fnt", "Reincarnation 2");
	this->addChild(m_pJumpBoxTitle);
	m_pJumpBoxTitle->setPosition(VisibleRect::center() + Point(-300, 280));
	this->addChild(reincarTitle);
	reincarTitle->setPosition(VisibleRect::center() + Point(-50, 230));
	this->playFontAnimate();
	return true;
}

void Welcome::playFontAnimate()
{
	float sleep = 0.0f;
	std::string jumpBoxStr = this->m_pJumpBoxTitle->getString();
	for (unsigned int i = 0; i < jumpBoxStr.size(); i++)
	{
		char singleChar = jumpBoxStr.at(i);
		if (singleChar == 32) continue;
		auto singleSprite = m_pJumpBoxTitle->getLetter(i);
		auto delayTime = DelayTime::create(sleep);
		auto moveBy1 = MoveBy::create(0.1f, Point(0, 10));
		auto moveBy2 = MoveBy::create(0.1f, Point(0, -10));
		Sequence *seqAction = nullptr;
		if (i == jumpBoxStr.size() - 1)
		{
			auto callback = CallFunc::create([=](){
				auto seqAction2 = Sequence::create(
					DelayTime::create(0.1f),
					MoveBy::create(0.1f, Point(0, 10)),
					MoveBy::create(0.1f, Point(0, -15)),
					MoveBy::create(0.1f, Point(0, 5)),
					DelayTime::create(0.3f),
					CallFunc::create([=](){
						this->playFontAnimate();
					}),
					nullptr
					);
				m_pJumpBoxTitle->runAction(seqAction2);
			});
			seqAction = Sequence::create(delayTime, moveBy1, moveBy2, callback, nullptr);
		}
		else
		{
			seqAction = Sequence::create(delayTime, moveBy1, moveBy2, nullptr);
		}
		singleSprite->runAction(seqAction);
		sleep += 0.15f;
	}
}

bool Welcome::initHero()
{
	ValueMap valueMap = this->m_pGameMap->getHeroValueMap();
	this->m_pBoxSprite = BoxSprite::create(valueMap);
	this->m_pGameMap->addChild(m_pBoxSprite);
	this->m_vHeroInitPos = this->m_pBoxSprite->getPosition();
	return true;
}

void Welcome::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();

	this->playHeroAnimate();
}

void Welcome::playHeroAnimate()
{
	auto seqAction = Sequence::create(
		Show::create(),
		JumpBy::create(0.5f, Point(10, 0), 5, 2),
		MoveBy::create(0.5f, Point(30, 0)),
		MoveBy::create(0.2f, Point(-80, 0)),
		JumpBy::create(0.4f, Point(-120, 68), 60, 1),
		DelayTime::create(0.2f),
		JumpBy::create(0.3f, Point(-20, 18), 30, 1),
		MoveBy::create(0.2f, Point(12, 0)),
		JumpBy::create(0.2f, Point(10, -18), 0, 1),
		DelayTime::create(0.2f),
		JumpBy::create(0.3f, Point(-50, 18), 30, 1),
		JumpBy::create(0.5f, Point(15, 0), 5, 2),
		JumpBy::create(0.5f, Point(120, 65), 50, 1),
		MoveBy::create(0.2f, Point(12, 0)),
		JumpBy::create(0.4f, Point(40, 15), 50, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.4f, Point(40, 15), 50, 1),
		MoveBy::create(0.2f, Point(15, 0)),
		JumpBy::create(0.9f, Point(180, -180), 100, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(1.2f, Point(-60, 0), 15, 2),
		JumpBy::create(0.5f, Point(0, 0), 5, 2),
		MoveBy::create(0.2f, Point(60, 0)),
		JumpBy::create(0.8f, Point(200, 0), 100, 1),
		JumpBy::create(0.5f, Point(0, 0), 5, 2),
		MoveBy::create(0.2f, Point(50, 0)),
		JumpBy::create(0.6f, Point(95, 68), 60, 1),
		JumpBy::create(0.5f, Point(5, 0), 5, 2),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.3f, Point(50, 18), 20, 1),
		MoveBy::create(0.2f, Point(-5, 0)),
		JumpBy::create(0.5f, Point(-130, 68), 60, 1),
		MoveBy::create(0.2f, Point(-5, 0)),
		JumpBy::create(0.3f, Point(-50, 14), 20, 1),
		JumpBy::create(0.3f, Point(-50, 14), 20, 1),
		JumpBy::create(0.5f, Point(0, 0), 5, 2),
		JumpBy::create(0.5f, Point(80, 107), 50, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.5f, Point(80, 65), 50, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		MoveBy::create(0.2f, Point(-5, 0)),
		JumpBy::create(0.5f, Point(-150, 84), 50, 1),
		MoveBy::create(0.2f, Point(-15, 0)),
		JumpBy::create(0.5f, Point(-210, -85), 50, 1),
		DelayTime::create(0.2f),
		Hide::create(),
		Place::create(this->m_vHeroInitPos),
		nullptr
		);
	this->m_pBoxSprite->runAction(RepeatForever::create(seqAction));
}