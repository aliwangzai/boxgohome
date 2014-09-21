#include "LevelComplete.h"
#include "GameUI.h"
#include "UIButton.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "AdManager.h"
#include "LevelState.h"



LevelComplete::LevelComplete()
{
}

LevelComplete::~LevelComplete()
{
}

LevelComplete* LevelComplete::create(Dialog* dialog)
{
	auto levelComplete = new (std::nothrow) LevelComplete;
	if (levelComplete && levelComplete->initWithDialog(dialog))
	{
		levelComplete->autorelease();
		return levelComplete;
	}
	CC_SAFE_RELEASE(levelComplete);
	return nullptr;
}

bool LevelComplete::initWithDialog(Dialog* dialog)
{
	this->m_pDialog = dialog;
	m_pLayout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Win.json"));
	addChild(m_pLayout);

	m_pLayout->setAnchorPoint(Vec2(0.5, 0.5));


	/*auto light = Sprite::create("ui/bg_light.png");
	auto sprite = Sprite::create("ui/bg_result.png");
	this->addChild(sprite);
	//this->addChild(light);
	this->setContentSize(sprite->getContentSize());
	light->setScale(3.0f);

	light->setPosition(this->getContentSize() / 2);
	sprite->setPosition(this->getContentSize() / 2);;*/


	Text * txt = static_cast<Text*>(m_pLayout->getChildByName("label_score"));
	txt->setString("123456789");

	Button * btn_menu = static_cast<Button*>(m_pLayout->getChildByName("btn_menu"));
	Button * btn_reset = static_cast<Button*>(m_pLayout->getChildByName("btn_reset"));
	Button * btn_next = static_cast<Button*>(m_pLayout->getChildByName("btn_next"));

	btn_menu->addTouchEventListener(this, toucheventselector(LevelComplete::btn_menuCallback));
	btn_reset->addTouchEventListener(this, toucheventselector(LevelComplete::btn_resetCallback));
	btn_next->addTouchEventListener(this, toucheventselector(LevelComplete::btn_nextCallback));

	//this->initMenu();
	//this->initDataLabel();
    
    dialog->setDisplayCallback([=](void *data){
        int tag = (int)data;
        if(tag == DialogEvent::Event_show){
            AdManager::getInstance()->displayInterstitial();
        }
    });
	return true;
}

void LevelComplete::btn_menuCallback(Ref*sender,TouchEventType type)
{
	if (type == ui::TouchEventType::TOUCH_EVENT_ENDED)
	{
		this->m_pDialog->hideDialog();
		m_fCallback((void*)1);
	}
}

void LevelComplete::btn_resetCallback(Ref*sender,TouchEventType type)
{
	if (type == ui::TouchEventType::TOUCH_EVENT_ENDED)
	{
		this->m_pDialog->hideDialog();
		m_fCallback((void*)2);
	}
}


void LevelComplete::btn_nextCallback(Ref*sender,TouchEventType type)
{
	if (type == ui::TouchEventType::TOUCH_EVENT_ENDED)
	{
		this->m_pDialog->hideDialog();
		m_fCallback((void*)3);
	}
}


bool LevelComplete::initDataLabel()
{
	auto bonusLabel = Label::createWithSystemFont("7373", "", 21);
	bonusLabel->setPosition(320, 188);
	bonusLabel->setColor(Color3B(0, 0, 0));
	bonusLabel->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(bonusLabel, 0, 0x02);
	auto jumpLabel = Label::createWithSystemFont("3X1000=3000", "", 21);
	jumpLabel->setPosition(320, 162);
	jumpLabel->setColor(Color3B(0, 0, 0));
	jumpLabel->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(jumpLabel, 0, 0x03);
	auto newScore = Label::createWithSystemFont("00000", "", 21);
	newScore->setPosition(320, 123);
	newScore->setColor(Color3B(0, 0, 0));
	newScore->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(newScore, 0, 0x04);
	return true;
}

void LevelComplete::databind(void *data)
{
	if (data != nullptr)
	{
		auto gameUI = (GameUI*)data;
		Text *label = static_cast<Text*>(m_pLayout->getChildByName("label_score"));
		int currentLevelNewScore = gameUI->getBonus() + gameUI->getJumpScore();
		label->setString(std::to_string(currentLevelNewScore));
		gameUI->setNewScore(currentLevelNewScore);

		int starNum = 2;  // TODO: calculation for star count
		ui::LoadingBar * bar =  static_cast<ui::LoadingBar*>(m_pLayout->getChildByName("progress_stars"));
		bar->setPercent(33* starNum);
		// save current level 'score in userdefault.xml  /
		int currentSelectLevel = LevelState::getInstance()->getSelectedLevel();
		UserDefault::getInstance()->setIntegerForKey(CCString::createWithFormat("stars_1_%d" ,currentSelectLevel)->getCString() , starNum);

	}
}

void LevelComplete::setResultCallback(DialogCallback callback)
{
	this->m_fCallback = callback;
}
