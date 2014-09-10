#ifndef UIButton_h__
#define UIButton_h__
#include "cocos-ext.h"
USING_NS_CC_EXT;


typedef std::function<void(Ref* )> cccontrol_callback;

class UIButton : public Node
{
	ControlButton * _button;
	cccontrol_callback _callback;
public:
	UIButton();
	~UIButton();

	void onClicked(Ref * sender , Control::EventType);

	static UIButton * create(const char * imagename, cccontrol_callback handler );
	bool init(const char * imagename ,  cccontrol_callback handler);
};

bool UIButton::init(const char * imagename ,  cccontrol_callback handler)
{
	auto s9 = Scale9Sprite::create(imagename);
	_button = ControlButton::create(s9);
	_button->setAdjustBackgroundImage(false);
	_callback = handler;
	_button->addTargetWithActionForControlEvents(this, cccontrol_selector(UIButton::onClicked) , Control::EventType::TOUCH_UP_INSIDE);
	addChild(_button);
	return true;
}

void UIButton::onClicked(Ref * sender , Control::EventType typ)
{
	_callback(sender);
}

UIButton * UIButton::create( const char * imagename , cccontrol_callback handler )
{
	UIButton * btn = new UIButton;
	btn->init(imagename , handler);
	btn->autorelease();
	return btn;
}

UIButton::UIButton()
{

}

UIButton::~UIButton()
{

}




#endif // UIButton_h__
