#include "GameUI.h"
#include "VisibleRect.h"
#include "Welcome.h"
#include "CheckBox.h"

GameUI::GameUI()
{
}

GameUI::~GameUI()
{
}

bool GameUI::init()
{
	this->initScoreUI();
	MenuItemFont::setFontSize(30);
	this->initMenu();
	this->initMoreGame();
	this->initSound();
	this->setDefaultValue();

	this->scheduleUpdate();

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
		
	});
	auto menuItem = MenuItemFont::create("Menu", [=](Ref *pSender){
		Director::getInstance()->replaceScene(Welcome::createScene());
	});
	auto menu = Menu::create(restartItem, menuItem, nullptr);
	this->addChild(menu);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(VisibleRect::rightTop() + Point(-100, -20));
	return true;
}

bool GameUI::initScoreUI()
{
	//Label::createWithSystemFont("Level: 1", "", 20);
	this->m_pLevelLabel = Label::createWithBMFont("fonts/fonts.fnt", "Level:1");
	m_pLevelLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pLevelLabel);
	m_pLevelLabel->setPosition(VisibleRect::leftTop() + Point(20, -10));

	this->m_pScoreLabel = Label::createWithBMFont("fonts/fonts.fnt", "Score:1");
	m_pScoreLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pScoreLabel);
	m_pScoreLabel->setPosition(VisibleRect::leftTop() + Point(150, -10));

	this->m_pBonusLabel = Label::createWithBMFont("fonts/fonts.fnt", "Bonus:5");
	m_pBonusLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pBonusLabel);
	m_pBonusLabel->setPosition(VisibleRect::leftTop() + Point(280, -10));

	this->m_pJumpsLabel = Label::createWithBMFont("fonts/fonts.fnt", "Jumps:5");
	m_pJumpsLabel->setAnchorPoint(Point(0, 1));
	this->addChild(m_pJumpsLabel);
	m_pJumpsLabel->setPosition(VisibleRect::leftTop() + Point(430, -10));
	return true;
}

void GameUI::setDefaultValue()
{
	this->setLevel(1);
	this->setScore(0);
	this->setBonus(9000);
	this->setJumps(5);
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
		this->unscheduleUpdate();
	}
}

void GameUI::jumpsSelfSub()
{
	this->setJumps(--this->m_nJump);
}

