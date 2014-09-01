#include "CheckBox.h"
#include "Utils.h"

CheckBox::CheckBox()
:m_sNormalSprite(""),
m_sSelectSprite(""),
m_bCurrentState(false),
m_bIsPlayAnimate(true)
{
}


CheckBox::~CheckBox()
{
}

CheckBox* CheckBox::create(std::string normalSprite, std::string selectSprite)
{
	auto checkBox = new CheckBox();
	if (checkBox && checkBox->initWithImage(normalSprite, selectSprite))
	{
		checkBox->autorelease();
		return checkBox;
	}
	return nullptr;
}

bool CheckBox::initWithImage(std::string normalSprite, std::string selectSprite)
{
	this->m_sNormalSprite = normalSprite;
	this->m_sSelectSprite = selectSprite;
	return this->init();
}

bool CheckBox::init()
{
	if (!Sprite::init()) return false;

	if (this->m_sNormalSprite.size() != 0)
	{
		this->setSpriteFrame(Utils::getSpriteFrame(this->m_sNormalSprite));
	}
	this->initListener();
	return true;
}

bool CheckBox::initListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CheckBox::onTouchBegin, this);
	listener->onTouchMoved = CC_CALLBACK_2(CheckBox::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CheckBox::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void CheckBox::playClickAnimate()
{
	if (this->m_bIsPlayAnimate)
	{
		this->stopAllActions();
		auto scaleBy = ScaleTo::create(0.1, 1.3f);
		this->runAction(scaleBy);
		this->m_bIsPlayAnimate = false;
	}
}

void CheckBox::playEndedAnimate()
{
	if (!this->m_bIsPlayAnimate)
	{
		this->stopAllActions();
		auto scaleTo = ScaleTo::create(0.1, 1.0f);
		this->runAction(scaleTo);
		this->m_bIsPlayAnimate = true;
	}
}

bool CheckBox::onTouchBegin(Touch *pTouch, Event *pEvent)
{
	if (this->getBoundingBox().containsPoint(pTouch->getLocation()))
	{
		this->playClickAnimate();
		return true;
	}
	return false;
}

void CheckBox::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	if (!this->getBoundingBox().containsPoint(pTouch->getLocation())){
		this->playEndedAnimate();
	}
}

void CheckBox::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (this->getBoundingBox().containsPoint(pTouch->getLocation()))
	{
		this->m_bCurrentState = !this->m_bCurrentState;
		if (this->m_bCurrentState)
		{
			this->select();
		}
		else
		{
			this->unSelect();
		}
	}
	this->playEndedAnimate();
}

void CheckBox::select()
{
	if (this->m_sSelectSprite.size() != 0)
	{
		this->setSpriteFrame(Utils::getSpriteFrame(this->m_sSelectSprite));
	}
	if (this->m_cCallback)
	{
		m_cCallback(this->m_bCurrentState);
	}
}

void CheckBox::unSelect()
{
	if (this->m_sNormalSprite.size() != 0)
	{
		this->setSpriteFrame(Utils::getSpriteFrame(this->m_sNormalSprite));
	}
	if (this->m_cCallback)
	{
		this->m_cCallback(this->m_bCurrentState);
	}
}

void CheckBox::changeNormalState()
{
	this->unSelect();
	this->m_bCurrentState = !this->m_bCurrentState;
}

void CheckBox::changeSelectState()
{
	this->select();
	this->m_bCurrentState = !this->m_bCurrentState;
}

void CheckBox::setCallback(const CheckBoxCallback &callback)
{
	this->m_cCallback = callback;
}

