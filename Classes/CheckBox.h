#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "cocos2d.h"
USING_NS_CC;

typedef std::function<void(bool)> CheckBoxCallback;

class CheckBox: public Sprite
{
public:
	CheckBox();
	~CheckBox();

	bool init();
	bool initWithImage(std::string normalSprite, std::string selectSprite);
	bool initListener();

	static CheckBox* create(std::string normalSprite, std::string selectSprite);
	CREATE_FUNC(CheckBox);

	void playClickAnimate();
	void playEndedAnimate();

	virtual bool onTouchBegin(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	bool getCurrentState() const{ return m_bCurrentState; }
	void changeNormalState();
	void changeSelectState();

	void setCallback(const CheckBoxCallback &callback);

protected:
	void select();
	void unSelect();

private:
	std::string m_sNormalSprite;
	std::string	m_sSelectSprite;
	bool		m_bCurrentState;
	bool		m_bIsPlayAnimate;
	CheckBoxCallback m_cCallback;
};

#endif