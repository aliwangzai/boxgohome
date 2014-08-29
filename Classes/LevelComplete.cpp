#include "LevelComplete.h"

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

	auto sprite = Sprite::create("HelloWorld.png");
	this->addChild(sprite);
	this->setContentSize(sprite->getContentSize());
	sprite->setPosition(this->getContentSize() / 2);

	return true;
}

void LevelComplete::databind(void *data)
{

}

void LevelComplete::setResultCallback(DialogCallback callback)
{
	this->m_fCallback = callback;
}
