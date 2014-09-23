#include "MenuLayer.h"
#include "Background.h"
#include "VisibleRect.h"
#include "CheckBox.h"
#include "GameWorld.h"
#include "PlayGameMenu.h"
#include "LevelSelector.h"
#include "Welcome.h"
#include "AdManager.h"
#include "Utils.h"
#include "TutorialMenu.h"

#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "DialogManager.h"
using namespace  cocos2d::ui;


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

	auto title = Sprite::create("ui/title2.png");
	title->setPosition(VisibleRect::leftTop() + Vec2(20 , -20));
	title->setAnchorPoint(Point(0, 1));
	addChild(title ,2);

// 	m_pJumpBoxTitle = Label::createWithBMFont("fonts/base_font.fnt", "Jumping Box");
// 	auto reincarTitle = Label::createWithBMFont("fonts/base_font.fnt", "Reincarnation 2");
// 	this->addChild(m_pJumpBoxTitle);
// 	m_pJumpBoxTitle->setPosition(VisibleRect::top() + Point(-250, -m_pJumpBoxTitle->getContentSize().height / 2 - 10));
// 	this->addChild(reincarTitle);
// 	reincarTitle->setPosition(VisibleRect::top() + Point(0, -100));
// 	this->playFontAnimate();
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

void MenuLayer::onEnter()
{
	Node::onEnter();

	AdManager::getInstance()->hideBannerAD();
}

void MenuLayer::onExit()
{
	Node::onExit();
}

bool MenuLayer::initSound()
{
	auto soundCheckBox = Utils::createSound();
	auto size = soundCheckBox->getContentSize();
	soundCheckBox->setPosition(VisibleRect::leftBottom() + Point(size / 2) + Point(20, 10));
	this->addChild(soundCheckBox);
	
	auto musicCheckBox = Utils::createMusic();
	musicCheckBox->setPosition(soundCheckBox->getPosition() + Point(80, 0));
	this->addChild(musicCheckBox);
	return true;
}

bool MenuLayer::initWithMenu()
{
	Widget* widget = static_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Menu.json"));
	widget->setAnchorPoint(Vec2(0, 0.5f));
	widget->setPosition(VisibleRect::left() + Vec2(30, 0));
	this->addChild(widget, 10);

	Button * btn_play = static_cast<Button *>(widget->getChildByName("btn_play"));
	Button * btn_tur = static_cast<Button *>(widget->getChildByName("btn_tur"));
	Button * btn_more = static_cast<Button *>(widget->getChildByName("btn_more"));
	Button * btn_credit = static_cast<Button *>(widget->getChildByName("btn_credit"));


	Button * btn_play = static_cast<Button *>(layout->getChildByName("btn_play"));
	Button * btn_tur = static_cast<Button *>(layout->getChildByName("btn_tur"));
	Button * btn_more = static_cast<Button *>(layout->getChildByName("btn_more"));
	Button * btn_settings = static_cast<Button *>(layout->getChildByName("btn_settings"));


	btn_play->addTouchEventListener([=](Ref * sender , Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(LevelSelectScene::createScene());
		}
	});

	if (!btn_settings)
	{
		return true;
	}

	btn_settings->addTouchEventListener([=](Ref * sender , Widget::TouchEventType type) {
		if ((int)type == ui::TouchEventType::TOUCH_EVENT_ENDED)
		{
			//pop setting dialog
			DialogManager::getInstance()->showSettingDialog();
		}

	});

	return true;
}
