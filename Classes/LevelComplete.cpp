#include "LevelComplete.h"
#include "GameUI.h"

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

	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(.5, .5));

	auto sprite = Sprite::create("dialog/dialog_2.png");
	this->addChild(sprite);
	this->setContentSize(sprite->getContentSize());
	sprite->setPosition(this->getContentSize() / 2);

	this->initMenu();

	this->initDataLabel();

	return true;
}

bool LevelComplete::initMenu()
{
	MenuItemFont::setFontSize(22);
	auto moreGameItem = MenuItemFont::create("More Game", [=](Ref *pSender){
		if (this->m_fCallback)
		{
			m_fCallback((void*)1);
		}
	});
	moreGameItem->setColor(Color3B(0, 0, 0));
	auto nextLevelItem = MenuItemFont::create("Next Level", [=](Ref *pSender){
		if (this->m_fCallback)
		{
			this->m_pDialog->hideDialog();
			m_fCallback((void*)2);
		}
	});
	nextLevelItem->setColor(Color3B(0, 0, 0));
	auto menu = Menu::create(moreGameItem, nextLevelItem, nullptr);
	menu->alignItemsHorizontallyWithPadding(70);
	menu->setPosition(170, 38);
	this->addChild(menu);
	return true;
}

bool LevelComplete::initDataLabel()
{
	auto oldScore = Label::createWithSystemFont("7434", "", 21);
	oldScore->setPosition(300, 210);
	oldScore->setColor(Color3B(0, 0, 0));
	oldScore->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(oldScore, 0, 0x01);
	auto bonusLabel = Label::createWithSystemFont("7373", "", 21);
	bonusLabel->setPosition(300, 174);
	bonusLabel->setColor(Color3B(0, 0, 0));
	bonusLabel->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(bonusLabel, 0, 0x02);
	auto jumpLabel = Label::createWithSystemFont("3X1000=3000", "", 21);
	jumpLabel->setPosition(300, 142);
	jumpLabel->setColor(Color3B(0, 0, 0));
	jumpLabel->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(jumpLabel, 0, 0x03);
	auto newScore = Label::createWithSystemFont("00000", "", 21);
	newScore->setPosition(300, 96);
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
		auto label = static_cast<Label*>(this->getChildByTag(0x01));
		label->setString(std::to_string(gameUI->getOldScore()));
		label = static_cast<Label*>(this->getChildByTag(0x02));
		label->setString(std::to_string(gameUI->getBonus()));

		char buffer[128];
		sprintf(buffer, "%dX%d=%d", gameUI->getJumpCount(), JUMPSTEPSCORE, gameUI->getJumpScore());
		label = static_cast<Label*>(this->getChildByTag(0x03));
		label->setString(buffer);

		int currentLevelNewScore = gameUI->getBonus() + gameUI->getJumpScore();
		int newScore = currentLevelNewScore + gameUI->getOldScore();
		label = static_cast<Label*>(this->getChildByTag(0x04));
		label->setString(std::to_string(newScore));
		gameUI->setNewScore(currentLevelNewScore);
	}
}

void LevelComplete::setResultCallback(DialogCallback callback)
{
	this->m_fCallback = callback;
}
