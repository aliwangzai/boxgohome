#ifndef UIButton_h__
#define UIButton_h__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
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




#endif // UIButton_h__
