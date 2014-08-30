#include "LevelCompleteLoss.h"
#include "Utils.h"

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

	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(.5, .5));

	auto sprite = Utils::createSprite("dialog/dialog_1.png");
	this->setContentSize(sprite->getContentSize());
	this->addChild(sprite);
	sprite->setPosition(this->getContentSize() / 2);

	this->initWithMenu();
	this->initWithTitle();
	
	return true;
}

bool LevelCompleteLoss::initWithMenu()
{
	MenuItemFont::setFontSize(22);
	auto moreGameItem = MenuItemFont::create("More Game", [=](Ref *pSender){
		if (m_fCallback)
		{
			m_fCallback((void*)1);
		}
	});
	moreGameItem->setColor(Color3B(0, 0, 0));
	auto restartItem = MenuItemFont::create("Restart", [=](Ref *pSender){
		if (m_fCallback)
		{
			this->m_pDialog->hideDialog();
			m_fCallback((void*)2);
		}
	});
	restartItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(moreGameItem, restartItem, nullptr);
	menu->alignItemsHorizontallyWithPadding(60);
	menu->setPosition(150, 38);
	this->addChild(menu);
	return true;
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
