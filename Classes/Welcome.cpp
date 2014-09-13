#include "Welcome.h"
#include "VisibleRect.h"
#include "Background.h"
#include "GameWorld.h"
#include "GameMap.h"
#include "BoxSprite.h"
#include "MenuLayer.h"
#include "DialogManager.h"
#include "ShareManager.h"
#include "AdManager.h"

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
	std::string filename = "maps/nwelcome.tmx";
	m_pGameMap = GameMap::createWithFile(filename);
	m_pGameMap->setPosition(VisibleRect::center());
	this->addChild(m_pGameMap);
	return true;
}

bool Welcome::initMenu()
{
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 32);
	auto moreGameLabel = Label::createWithTTF(ttfConfig, "More Game");
	auto moreGameItem = MenuItemLabel::create(moreGameLabel, [=](Ref *pSender){
		ShareManager::getInstance()->setShareAttribute("content", "this is test content");
		ShareManager::getInstance()->setShareAttribute("image", "http://img0.bdstatic.com/img/image/308342ac65c10385343da168d569113b07ecb8088ef.jpg");
		ShareManager::getInstance()->setShareAttribute("title", "title");
		ShareManager::getInstance()->setShareAttribute("description", "description");
		ShareManager::getInstance()->setShareAttribute("url", "http://sharesdk.cn");
		ShareManager::getInstance()->setShareAttribute("type", std::to_string(C2DXContentTypeNews));
		ShareManager::getInstance()->sendShare();
	});
	moreGameItem->setColor(Color3B(0, 0, 0));
	auto startLabel = Label::createWithTTF(ttfConfig, "Play");
	auto startItem = MenuItemLabel::create(startLabel, [](Ref *pSender){
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	startItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(moreGameItem, startItem, nullptr);
	this->addChild(menu);
	menu->alignItemsVerticallyWithPadding(10);
	menu->setPosition(VisibleRect::center() + Point(0, 0));

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
		JumpBy::create(0.4f, Point(-130, 71), 60, 1),
		DelayTime::create(0.2f),
		JumpBy::create(0.3f, Point(-20, 25), 40, 1),
		MoveBy::create(0.2f, Point(12, 0)),
		JumpBy::create(0.2f, Point(10, -25), 0, 1),
		DelayTime::create(0.2f),
		JumpBy::create(0.3f, Point(-65, 25), 30, 1),
		JumpBy::create(0.5f, Point(15, 0), 5, 2),
		JumpBy::create(0.5f, Point(100, 77), 50, 1),
		MoveBy::create(0.2f, Point(12, 0)),
		JumpBy::create(0.4f, Point(70, 23), 50, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.4f, Point(40, 25), 50, 1),
		MoveBy::create(0.2f, Point(35, 0)),
		JumpBy::create(0.9f, Point(220, -222), 100, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.5f, Point(10, 0), 5, 2),
		MoveBy::create(0.2f, Point(60, 0)),
		
		JumpBy::create(0.6f, Point(125, 74), 60, 1),
		JumpBy::create(0.5f, Point(5, 0), 5, 2),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.3f, Point(80, 25), 20, 1),
		MoveBy::create(0.2f, Point(-5, 0)),
		JumpBy::create(0.5f, Point(-130, 74), 60, 1),
		MoveBy::create(0.2f, Point(-5, 0)),
		JumpBy::create(0.3f, Point(-70, 25), 20, 1),
		JumpBy::create(0.3f, Point(-80, 24), 20, 1),
		JumpBy::create(0.5f, Point(0, 0), 5, 2),
		JumpBy::create(0.5f, Point(140, 100), 50, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		JumpBy::create(0.5f, Point(80, 75), 50, 1),
		MoveBy::create(0.2f, Point(10, 0)),
		MoveBy::create(0.2f, Point(-5, 0)),
		JumpBy::create(0.5f, Point(-150, 77), 50, 1),
		MoveBy::create(0.2f, Point(-15, 0)),
		JumpBy::create(0.5f, Point(-180, -77), 50, 1),/**/
		DelayTime::create(0.2f),
		Hide::create(),
		Place::create(this->m_vHeroInitPos),
		nullptr
		);
	this->m_pBoxSprite->runAction(RepeatForever::create(seqAction));
}