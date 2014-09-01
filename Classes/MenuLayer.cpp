#include "MenuLayer.h"
#include "Background.h"
#include "VisibleRect.h"
#include "CheckBox.h"
#include "GameWorld.h"
#include "PlayGameMenu.h"
#include "LevelSelector.h"

MenuLayer::MenuLayer()
:m_pCurrentNode(nullptr)
{
}


MenuLayer::~MenuLayer()
{
}

Scene* MenuLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	if (scene)
	{
		auto layer = MenuLayer::create();
		scene->addChild(layer);
		return scene;
	}
	return nullptr;
}

bool MenuLayer::init()
{
	this->initBackground();
	this->initWithMenu();
	this->initSound();
	this->initTitle();
	return true;
}

bool MenuLayer::initTitle()
{
	m_pJumpBoxTitle = Label::createWithBMFont("fonts/base_font.fnt", "Jumping Box");
	auto reincarTitle = Label::createWithBMFont("fonts/base_font.fnt", "Reincarnation 2");
	this->addChild(m_pJumpBoxTitle);
	m_pJumpBoxTitle->setPosition(VisibleRect::top() + Point(-250, -m_pJumpBoxTitle->getContentSize().height / 2 - 10));
	this->addChild(reincarTitle);
	reincarTitle->setPosition(VisibleRect::top() + Point(0, -100));
	this->playFontAnimate();
	return true;
}

void MenuLayer::playFontAnimate()
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

bool MenuLayer::initBackground()
{
	auto background = Background::create();
	this->addChild(background);
	return true;
}

bool MenuLayer::initSound()
{
	auto soundCheckBox = CheckBox::create("49.png", "50.png");
	auto size = soundCheckBox->getContentSize();
	soundCheckBox->setPosition(Point(size / 2) + Point(20, 10));
	this->addChild(soundCheckBox);
	soundCheckBox->setCallback([=](bool state){
		if (!state) CCLOG("%s", "play sound");
		else CCLOG("%s", "close sound");
	});

	auto musicCheckBox = CheckBox::create("47.png", "48.png");
	size = musicCheckBox->getContentSize();
	musicCheckBox->setPosition(Point(size / 2) + Point(70, 10));
	this->addChild(musicCheckBox);
	musicCheckBox->setCallback([=](bool state){
		if (!state) CCLOG("%s", "play music");
		else CCLOG("%s", "close music");
	});
	return true;
}

bool MenuLayer::initWithMenu()
{
	this->m_pCurrentNode = PlayGameMenu::create();
	this->addChild(this->m_pCurrentNode);
	m_pCurrentNode->setPosition(VisibleRect::leftBottom());

	MenuItemFont::setFontSize(32);
	auto playItem = MenuItemFont::create("Play Game", [=](Ref *pSender){
		Director::getInstance()->replaceScene(LevelSelectScene::createScene());
		//Director::getInstance()->replaceScene(GameWorld::createScene());
	});
	playItem->setColor(Color3B(0, 0, 0));
	auto highScoreItem = MenuItemFont::create("Highscores", [=](Ref *pSender){
		this->m_pCurrentNode->removeFromParent();
		this->m_pCurrentNode = PlayGameMenu::create();
		this->addChild(this->m_pCurrentNode);
		m_pCurrentNode->setPosition(VisibleRect::leftBottom());
	});
	highScoreItem->setColor(Color3B(0, 0, 0));
	auto instructionItem = MenuItemFont::create("Instructions", [=](Ref *pSender){
		this->m_pCurrentNode->removeFromParent();
		this->m_pCurrentNode = Sprite::create("38.png");
		m_pCurrentNode->setPosition(VisibleRect::center() + Vec2(100, -50));
		this->addChild(m_pCurrentNode);
	});
	instructionItem->setColor(Color3B(0, 0, 0));
	auto tutorialItem = MenuItemFont::create("Tutorial", [=](Ref *pSender){
		this->m_pCurrentNode->removeFromParent();
		this->m_pCurrentNode = Sprite::create("37.png");
		m_pCurrentNode->setPosition(VisibleRect::center() + Vec2(100, -50));
		this->addChild(m_pCurrentNode);
	});
	tutorialItem->setColor(Color3B(0, 0, 0));
	auto walkthroughItem = MenuItemFont::create("Walkthrough", [=](Ref *pSender){
	
	});
	walkthroughItem->setColor(Color3B(0, 0, 0));
	auto moreGameItem = MenuItemFont::create("More Games", [=](Ref *pSender){
		Director::getInstance()->replaceScene(LevelSelectScene::createScene());
	});
	moreGameItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(playItem, highScoreItem, instructionItem, tutorialItem, walkthroughItem, moreGameItem, nullptr);
	this->addChild(menu);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(VisibleRect::left() + Point(150, 0));
	return true;
}
