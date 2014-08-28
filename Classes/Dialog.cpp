#include "Dialog.h"


Dialog::Dialog()
:m_bEnableClickClose(false),
m_nTouchPriority(-1000),
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
	listener->onTouchBegan = CC_CALLBACK_2(Dialog::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Dialog::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Dialog::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, this->m_nTouchPriority);
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

}

void Dialog::setTouchPriority(int priority)
{
	this->m_nTouchPriority = priority;
}

void Dialog::setContentPanel(Node *node)
{
	this->m_pContentPanel = node;
}

void Dialog::setEnableClickClose(bool enable)
{
	this->m_bEnableClickClose = enable;
}

void Dialog::setOrderZ(int order)
{
	this->setOrderZ(order);
}
