#include "LevelCompleteLoss.h"
#include "Utils.h"

#include "cocos/ui/UIText.h"
#include "cocos/ui/UIButton.h"
#include "cocostudio/CCSGUIReader.h"
#include "cocos/ui/UILayout.h"


LevelCompleteLoss::LevelCompleteLoss()
{
}


LevelCompleteLoss::~LevelCompleteLoss()
{
}

LevelCompleteLoss* LevelCompleteLoss::create(Dialog* dialog)
{
	auto levelCompleteLoss = new (std::nothrow) LevelCompleteLoss;
	if (levelCompleteLoss && levelCompleteLoss->initWithDialog(dialog))
	{
		levelCompleteLoss->autorelease();
		return levelCompleteLoss;
	}
	CC_SAFE_RELEASE(levelCompleteLoss);
	return nullptr;
}

bool LevelCompleteLoss::initWithDialog(Dialog* dialog)
{
	//if (!LayerColor::initWithColor(Color4B(255, 0, 0, 255))) return false;
	this->m_pDialog = dialog;

	Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Lose.json"));
	addChild(layout);

	Button * btn_menu = static_cast<Button*>(layout->getChildByName("btn_menu"));
	Button * btn_reset = static_cast<Button*>(layout->getChildByName("btn_reset"));
	Button * btn_next = static_cast<Button*>(layout->getChildByName("btn_next"));

	btn_menu->addTouchEventListener(this, toucheventselector(LevelCompleteLoss::btn_menuCallback));
	btn_reset->addTouchEventListener(this, toucheventselector(LevelCompleteLoss::btn_resetCallback));

	layout->setAnchorPoint(ccp(0.5,0.5));
	
	return true;
}

void LevelCompleteLoss::btn_menuCallback( Ref*sender,TouchEventType a )
{
	this->m_pDialog->hideDialog();
	m_fCallback((void*)1);
}

void LevelCompleteLoss::btn_resetCallback( Ref*sender,TouchEventType a )
{
	this->m_pDialog->hideDialog();
	m_fCallback((void*)2);
}



bool LevelCompleteLoss::initWithTitle()
{
	auto label = Label::createWithSystemFont("Try Again", "", 30);
	label->setPosition(Point(0, 110) + this->getContentSize() / 2);
	label->setColor(Color3B(0, 0, 0));
	this->addChild(label);
	return true;
}

void LevelCompleteLoss::databind(void *data)
{

}

void LevelCompleteLoss::setResultCallback(DialogCallback callback)
{
	this->m_fCallback = callback;
}

