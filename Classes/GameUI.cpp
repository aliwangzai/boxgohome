#include "GameUI.h"
#include "VisibleRect.h"
#include "MenuLayer.h"
#include "CheckBox.h"
#include "GameWorld.h"
#include "LevelState.h"
#include "Utils.h"

#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h"
using namespace ui;


#define SCORERECOARD_LEVEL(level) "user_score_" + std::to_string(level)

GameUI::GameUI()
{
}

GameUI::~GameUI()
{
}

GameUI* GameUI::create(GameWorld* gameWorld)
{
	auto gameUI = new (std::nothrow) GameUI;
	if (gameUI && gameUI->initWithGameWorld(gameWorld))
	{
		gameUI->autorelease();
		return gameUI;
	}
	CC_SAFE_RELEASE(gameUI);
	return nullptr;
}

bool GameUI::initWithGameWorld(GameWorld* gameWorld)
{
	this->m_pGameWorld = gameWorld;
	return this->init();
}

bool GameUI::init()
{
	this->initScoreUI();
	MenuItemFont::setFontSize(30);
	this->initMenu();
	this->initMoreGame();
	this->initSound();

	return true;
}

bool GameUI::initSound()
{
	/*auto soundCheckBox = Utils::createSound();
	auto size = soundCheckBox->getContentSize();
	soundCheckBox->setPosition(VisibleRect::leftBottom() + Point(size / 2) + Point(20, 10));
	this->addChild(soundCheckBox);
	
	auto musicCheckBox = Utils::createMusic();
	musicCheckBox->setPosition(soundCheckBox->getPosition() + Point(80, 0));
	this->addChild(musicCheckBox);*/
	return true;
}

void GameUI::playerStartAnimate()
{
	for (int i = 3; i >= 0; i--)
	{
		Node* node = this->getChildByTag(100 + i);
		if(node!= nullptr)node->removeFromParent();
	}
	for (int i = 3; i >= 0; i--)
	{
		char buffer[128];
		sprintf(buffer, "ui/321go_%d.png", i);
		auto sprite = Sprite::create(buffer);
		this->addChild(sprite, 1, 100 + i);
		sprite->setPosition(VisibleRect::center());
		sprite->setVisible(false);
		sprite->setScale(4.0f);
		sprite->runAction(Sequence::create(
			DelayTime::create((3 - i) * 0.5f + 0.1f),
			Show::create(),
			CCEaseBackOut::create(ScaleTo::create(0.5f, 1.0f)),
			CallFuncN::create([=](Node *node){
				if (node->getTag() == 100)
					this->startGame();
				node->removeFromParent();
			}),
			nullptr));
	}
}

void GameUI::startGame()
{
	m_pBonusLabel->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.5f),
		CallFunc::create([=](){
			this->scheduleUpdate();
			this->m_pGameWorld->startGame();
		}),
		nullptr));
}

bool GameUI::initMoreGame()
{
// 	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 32);
// 	auto moreGameLabel = Label::createWithTTF(ttfConfig, "More Game");
// 	auto moreGameItem = MenuItemLabel::create(moreGameLabel, [=](Ref *pSender){
// 		
// 	});
// 	moreGameItem->setColor(Color3B(0, 0, 0));
// 	auto menu = Menu::create(moreGameItem, nullptr);
// 	this->addChild(menu);
// 	menu->setPosition(VisibleRect::rightBottom() + Point(-80, 20));
	return true;
}

bool GameUI::initMenu()
{
	//TTFConfig ttfConfig("fonts/Marker Felt.ttf", 32);
	///auto restartLabel = Label::createWithTTF(ttfConfig, "Restart");
	auto restartItem = MenuItemImage::create("ui/btn_reset.png" , "ui/btn_reset.png" ,"ui/btn_reset.png", [=](Ref *pSender){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/press.mp3");
		this->m_pGameWorld->restart();
	});
	restartItem->setOpacity(100);
	//restartItem->setColor(Color3B(0, 0, 0));
	//auto menuLabel = Label::createWithTTF(ttfConfig, "Menu");
	auto menuItem = MenuItemImage::create("ui/btn_menu.png", "ui/btn_menu.png","ui/btn_menu.png", [=](Ref *pSender){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/press.mp3");
		Utils::replaceScene(MenuLayer::createScene());
	});
	menuItem->setOpacity(100);
	//menuItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(restartItem, menuItem, nullptr);
	this->addChild(menu);
	//menu->alignItemsHorizontallyWithPadding(20);
    menu->alignItemsVerticallyWithPadding(10);
	menu->setPosition(VisibleRect::rightTop() + Point(-50, -75));
	return true;
}

bool GameUI::initScoreUI()
{
	//GameUI_UP.json
	Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/GameUI_UP.json"));
	addChild(layout);
	layout->setAnchorPoint(Vec2(0,1));
	layout->setPosition(VisibleRect::leftTop());


	ui::Text* label =  static_cast<ui::Text*>(layout->getChildByName("label_0_score"));
	label->enableOutline(Color4B::BLACK , 1);

	label =   static_cast<ui::Text*>(layout->getChildByName("label_0_bonus"));
	label->enableOutline(Color4B::BLACK , 1);

	label =  static_cast<ui::Text*>(layout->getChildByName("label_0_jump"));
	label->enableOutline(Color4B::BLACK , 1);

	//


	m_pScoreLabel =  static_cast<ui::Text*>(layout->getChildByName("label_score"));
	m_pScoreLabel->enableOutline(Color4B::BLACK , 1);

	m_pBonusLabel =  static_cast<ui::Text*>(layout->getChildByName("label_bonus"));
	m_pBonusLabel->enableOutline(Color4B::BLACK , 1);

	m_pJumpsLabel =  static_cast<ui::Text*>(layout->getChildByName("label_jump"));
	m_pJumpsLabel->enableOutline(Color4B::BLACK , 1);

// 	TTFConfig ttfConfig("ui/grobold.ttf", 25);
// 	//--------------------------------------level-----------------------------------
// 	auto levelNameLabel = Label::createWithTTF(ttfConfig, "Level:");
// 	this->addChild(levelNameLabel);
// 	levelNameLabel->setPosition(VisibleRect::leftTop() + Point(50, -30));
// 	levelNameLabel->setColor(Color3B(255,255, 255));
// 	levelNameLabel->enableOutline(Color4B::BLACK , 1);
// 
// 	m_pLevelLabel = Label::createWithTTF(ttfConfig, "");
// 	this->addChild(m_pLevelLabel);
// 	m_pLevelLabel->setPosition(VisibleRect::leftTop() + Point(95, -30));
// 	m_pLevelLabel->setColor(Color3B(255,255, 255));
// 	m_pLevelLabel->enableOutline(Color4B::BLACK , 1);
// 
// 	//--------------------------------------score-----------------------------------
// 	auto scoreNameLabel = Label::createWithTTF(ttfConfig, "Score:");
// 	this->addChild(scoreNameLabel);
// 	scoreNameLabel->setPosition(VisibleRect::leftTop() + Point(160, -30));
// 	scoreNameLabel->setColor(Color3B(255,255, 255));
// 	scoreNameLabel->enableOutline(Color4B::BLACK , 1);
// 
// 	m_pScoreLabel = Label::createWithTTF(ttfConfig, "1");
// 	this->addChild(m_pScoreLabel);
// 	m_pScoreLabel->setPosition(VisibleRect::leftTop() + Point(230, -30));
// 	m_pScoreLabel->setColor(Color3B(255,255, 255));
// 	m_pScoreLabel->enableOutline(Color4B::BLACK , 1);
// 
// 
// 	//--------------------------------------bonus-----------------------------------
// 	auto bonusNameLabel = Label::createWithTTF(ttfConfig, "Bonus:");
// 	this->addChild(bonusNameLabel);
// 	bonusNameLabel->setPosition(VisibleRect::leftTop() + Point(305, -30));
// 	bonusNameLabel->setColor(Color3B(255,255, 255));
// 	bonusNameLabel->enableOutline(Color4B::BLACK , 1);
// 
// 	m_pBonusLabel = Label::createWithTTF(ttfConfig, "1");
// 	this->addChild(m_pBonusLabel);
// 	m_pBonusLabel->setPosition(VisibleRect::leftTop() + Point(365, -30));
// 	m_pBonusLabel->setColor(Color3B(255,255, 255));
// 	m_pBonusLabel->enableOutline(Color4B::BLACK , 1);
// 
// 	//--------------------------------------jumps-----------------------------------
// 	auto jumpsNameLabel = Label::createWithTTF(ttfConfig, "Jumps:");
// 	this->addChild(jumpsNameLabel);
// 	jumpsNameLabel->setPosition(VisibleRect::leftTop() + Point(500, -30));
// 	jumpsNameLabel->setColor(Color3B(255,255, 255));
// 	jumpsNameLabel->enableOutline(Color4B::BLACK , 1);
// 
// 	m_pJumpsLabel = Label::createWithTTF(ttfConfig, "5");
// 	this->addChild(m_pJumpsLabel);
// 	m_pJumpsLabel->setPosition(VisibleRect::leftTop() + Point(545, -30));
// 	m_pJumpsLabel->setColor(Color3B(255,255, 255));
// 	m_pJumpsLabel->enableOutline(Color4B::BLACK , 1);
	return true;
}

void GameUI::setDefaultValue()
{
	this->unscheduleUpdate();
	this->setLevel(LevelState::getInstance()->getSelectedLevel());
	this->setScore(getOldScore());
	this->setBonus(1000);
	this->setJumps(3);
	this->playerStartAnimate();
}

void GameUI::setLevel(int level)
{
	this->m_nLevel = level;
}

void GameUI::setScore(int score)
{
	this->m_nScore = score;
	m_pScoreLabel->setString(std::to_string(score));
}
void GameUI::setBonus(int bonus)
{
	this->m_nBonus = bonus;
	m_pBonusLabel->setString(std::to_string(bonus));
}

void GameUI::setJumps(int jumps, bool isShowAni)
{
	this->m_nJump = jumps;
	m_pJumpsLabel->setString(std::to_string(jumps));
	if (isShowAni)
	{
		auto seqAction = Sequence::create(
			ScaleTo::create(0.2f, 1.4f),
			ScaleTo::create(0.2f, 1.0f),
			nullptr
			);
		m_pJumpsLabel->runAction(seqAction);
	}
}

void GameUI::update(float dt)
{
	if (this->m_nBonus > 0)
	{
		this->setBonus(--this->m_nBonus);
	}
	else
	{
		this->m_pGameWorld->lose(3);
		this->unscheduleUpdate();
	}
}

bool GameUI::jumpsSelfSub()
{
	if (this->m_nJump >= 1)
	{
		this->setJumps(--this->m_nJump);
		return true;
	}
	return false;
}

void GameUI::stop()
{
	this->unscheduleUpdate();
}

int GameUI::getOldScore() const
{
	char buffer[128];
	sprintf(buffer, "user_score_%d", m_nLevel);
	int oldScore = UserDefault::getInstance()->getIntegerForKey(buffer);
	return oldScore;
}

void GameUI::setNewScore(int newScore)
{
	char buffer[128];
	sprintf(buffer, "user_score_%d", m_nLevel);
	UserDefault::getInstance()->setIntegerForKey(buffer, newScore);
}

void GameUI::addJumps(int count)
{
	this->m_nJump += count;
	this->setJumps(this->m_nJump, true);
}

