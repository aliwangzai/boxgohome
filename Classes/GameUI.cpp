#include "GameUI.h"
#include "VisibleRect.h"
#include "Welcome.h"
#include "CheckBox.h"
#include "GameWorld.h"

#define SCORERECOARD_LEVEL(level) "user_score_" + level

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

bool GameUI::initMoreGame()
{
	auto moreGameItem = MenuItemFont::create("MoreGame", [=](Ref *pSender){
		
	});
	auto menu = Menu::create(moreGameItem, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::rightBottom() + Point(-80, 20));
	return true;
}

bool GameUI::initMenu()
{
	auto restartItem = MenuItemFont::create("Restart", [=](Ref *pSender){
		this->m_pGameWorld->restart();
	});
	restartItem->setColor(Color3B(0, 0, 0));
	auto menuItem = MenuItemFont::create("Menu", [=](Ref *pSender){
		Director::getInstance()->replaceScene(Welcome::createScene());
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
	this->m_pLevelLabel = Label::createWithBMFont("fonts/fonts.fnt", "Level:1");
	m_pLevelLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pLevelLabel);
	m_pLevelLabel->setPosition(VisibleRect::leftTop() + Point(20, -10));

	this->m_pScoreLabel = Label::createWithBMFont("fonts/fonts.fnt", "Score:1");
	m_pScoreLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pScoreLabel);
	m_pScoreLabel->setPosition(VisibleRect::leftTop() + Point(120, -10));

	this->m_pBonusLabel = Label::createWithBMFont("fonts/fonts.fnt", "Bonus:5");
	m_pBonusLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pBonusLabel);
	m_pBonusLabel->setPosition(VisibleRect::leftTop() + Point(300, -10));

	this->m_pJumpsLabel = Label::createWithBMFont("fonts/fonts.fnt", "Jumps:5");
	m_pJumpsLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pJumpsLabel);
	m_pJumpsLabel->setPosition(VisibleRect::leftTop() + Point(470, -10));
	return true;
}

void GameUI::setDefaultValue()
{
	this->unscheduleUpdate();
	this->setLevel(1);
	this->setScore(getOldScore());
	this->setBonus(9000);
	this->setJumps(5);
	this->scheduleUpdate();
}

void GameUI::setLevel(int level)
{
	this->m_nLevel = level;
	m_pLevelLabel->setString("Level: " + std::to_string(level));
}

void GameUI::setScore(int score)
{
	this->m_nScore = score;
	m_pScoreLabel->setString("Score: " + std::to_string(score));
}
void GameUI::setBonus(int bonus)
{
	this->m_nBonus = bonus;
	m_pBonusLabel->setString("Bonus: " + std::to_string(bonus));
}

void GameUI::setJumps(int jumps)
{
	this->m_nJump = jumps;
	m_pJumpsLabel->setString("Jumps: " + std::to_string(jumps));
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
	for (int i = 1; i <= m_nLevel; i++)
	{
		oldScore = UserDefault::getInstance()->getIntegerForKey(SCORERECOARD_LEVEL(i));
	}
	return oldScore;
}

void GameUI::setNewScore(int newScore)
{
	UserDefault::getInstance()->setIntegerForKey(SCORERECOARD_LEVEL(m_nLevel + 1), newScore);
}

