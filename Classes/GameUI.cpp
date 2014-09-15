#include "GameUI.h"
#include "VisibleRect.h"
#include "MenuLayer.h"
#include "CheckBox.h"
#include "GameWorld.h"
#include "LevelState.h"
#include "Utils.h"

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
	this->setDefaultValue();

	return true;
}

bool GameUI::initSound()
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

bool GameUI::initMoreGame()
{
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 32);
	auto moreGameLabel = Label::createWithTTF(ttfConfig, "More Game");
	auto moreGameItem = MenuItemLabel::create(moreGameLabel, [=](Ref *pSender){
		
	});
	moreGameItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(moreGameItem, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::rightBottom() + Point(-80, 20));
	return true;
}

bool GameUI::initMenu()
{
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 32);
	auto restartLabel = Label::createWithTTF(ttfConfig, "Restart");
	auto restartItem = MenuItemLabel::create(restartLabel, [=](Ref *pSender){
		this->m_pGameWorld->restart();
	});
	restartItem->setColor(Color3B(0, 0, 0));
	auto menuLabel = Label::createWithTTF(ttfConfig, "Menu");
	auto menuItem = MenuItemLabel::create(menuLabel, [=](Ref *pSender){
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	menuItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(restartItem, menuItem, nullptr);
	this->addChild(menu);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(VisibleRect::rightTop() + Point(-100, -20));
	return true;
}

bool GameUI::initScoreUI()
{
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 25);
	//--------------------------------------level-----------------------------------
	auto levelNameLabel = Label::createWithTTF(ttfConfig, "Level:");
	this->addChild(levelNameLabel);
	levelNameLabel->setPosition(VisibleRect::leftTop() + Point(50, -30));
	levelNameLabel->setColor(Color3B(0, 0, 0));

	m_pLevelLabel = Label::createWithTTF(ttfConfig, "");
	this->addChild(m_pLevelLabel);
	m_pLevelLabel->setPosition(VisibleRect::leftTop() + Point(85, -30));
	m_pLevelLabel->setColor(Color3B(0, 0, 0));

	//--------------------------------------score-----------------------------------
	auto scoreNameLabel = Label::createWithTTF(ttfConfig, "Score:");
	this->addChild(scoreNameLabel);
	scoreNameLabel->setPosition(VisibleRect::leftTop() + Point(150, -30));
	scoreNameLabel->setColor(Color3B(0, 0, 0));

	m_pScoreLabel = Label::createWithTTF(ttfConfig, "1");
	this->addChild(m_pScoreLabel);
	m_pScoreLabel->setPosition(VisibleRect::leftTop() + Point(215, -30));
	m_pScoreLabel->setColor(Color3B(0, 0, 0));


	//--------------------------------------bonus-----------------------------------
	auto bonusNameLabel = Label::createWithTTF(ttfConfig, "Bonus:");
	this->addChild(bonusNameLabel);
	bonusNameLabel->setPosition(VisibleRect::leftTop() + Point(305, -30));
	bonusNameLabel->setColor(Color3B(0, 0, 0));

	m_pBonusLabel = Label::createWithTTF(ttfConfig, "1");
	this->addChild(m_pBonusLabel);
	m_pBonusLabel->setPosition(VisibleRect::leftTop() + Point(365, -30));
	m_pBonusLabel->setColor(Color3B(0, 0, 0));

	//--------------------------------------jumps-----------------------------------
	auto jumpsNameLabel = Label::createWithTTF(ttfConfig, "Jumps:");
	this->addChild(jumpsNameLabel);
	jumpsNameLabel->setPosition(VisibleRect::leftTop() + Point(500, -30));
	jumpsNameLabel->setColor(Color3B(0, 0, 0));

	m_pJumpsLabel = Label::createWithTTF(ttfConfig, "5");
	this->addChild(m_pJumpsLabel);
	m_pJumpsLabel->setPosition(VisibleRect::leftTop() + Point(545, -30));
	m_pJumpsLabel->setColor(Color3B(0, 0, 0));
	return true;
}

void GameUI::setDefaultValue()
{
	this->unscheduleUpdate();
	this->setLevel(LevelState::getInstance()->getSelectedLevel());
	this->setScore(getOldScore());
	this->setBonus(6000);
	this->setJumps(5);
	this->scheduleUpdate();
}

void GameUI::setLevel(int level)
{
	this->m_nLevel = level;
	m_pLevelLabel->setString(std::to_string(level));
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
		this->m_pGameWorld->lose();
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
	int oldScore = 0;
	char buffer[128];
	sprintf(buffer, "user_score_%d", m_nLevel);
	oldScore += UserDefault::getInstance()->getIntegerForKey(buffer);
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
	this->m_nJump += this->m_nJump + count;
	this->setJumps(this->m_nJump, true);
}

