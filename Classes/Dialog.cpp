#include "Dialog.h"
#include "VisibleRect.h"

Dialog::Dialog()
:m_bEnableClickClose(false),
m_nOrderZ(1000),
m_pContentPanel(nullptr)
{
}


Dialog::~Dialog()
{
}

bool Dialog::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Dialog::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Dialog::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Dialog::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->setLocalZOrder(this->m_nOrderZ);
	auto scene = Director::getInstance()->getRunningScene();
	scene->addChild(this);

	return true;
}

bool Dialog::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void Dialog::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void Dialog::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (this->m_pContentPanel)
	{
		Rect rect = this->m_pContentPanel->getBoundingBox();
		Point touchPoint = pTouch->getLocation();
		bool isContains = rect.containsPoint(touchPoint);
		if (!isContains && this->m_bEnableClickClose)
		{
			this->hideDialog();
		}
	}
}

void Dialog::setContentPanel(Node *node)
{
	this->m_pContentPanel = node;
	this->addChild(this->m_pContentPanel);
	this->m_pContentPanel->setScale(0.01f);
	this->m_pContentPanel->setPosition(VisibleRect::center());
}

void Dialog::setEnableClickClose(bool enable)
{
	this->m_bEnableClickClose = enable;
}

void Dialog::showDialog()
{
	if (this->m_pContentPanel)
	{
		auto seqAction = Sequence::create(
			ScaleTo::create(0.2f, 1.0f),
			CallFunc::create([=](){
				int tag = DialogEvent::Event_show;
                if(m_fCallback) m_fCallback((void*)&tag);
			}),
			nullptr);
		this->m_pContentPanel->runAction(seqAction);
	}
}

void Dialog::hideDialog()
{
	if (this->m_pContentPanel)
	{
		auto seqAction = Sequence::create(
			ScaleTo::create(0.2f, 0.001f),
			CallFunc::create([=](){
				int tag = DialogEvent::Event_hide;
				if (m_fCallback)m_fCallback((void*)&tag);
				_eventDispatcher->removeEventListenersForTarget(this);
				this->removeFromParent();
			}),
			nullptr);
		m_pContentPanel->runAction(seqAction);
	}
}

void Dialog::setTouchEnabled(bool enable)
{
	_eventDispatcher->setEnabled(enable);
}

void Dialog::setDisplayCallback(DialogCallback callback)
{
    this->m_fCallback = callback;
}
