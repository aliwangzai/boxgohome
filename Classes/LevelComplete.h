#ifndef __LEVELCOMPLETE_H__
#define __LEVELCOMPLETE_H__

#include "cocos2d.h"
#include "Dialog.h"
#include "ui/CocosGUI.h"
USING_NS_CC;


using namespace cocos2d::ui;

class LevelComplete: public Node
{
public:
	LevelComplete();
	~LevelComplete();

	bool initWithDialog(Dialog* dialog);
	bool initMenu();
	bool initDataLabel();

	static LevelComplete* create(Dialog *dialog);

	void databind(void *data);
	void playerPassAnimate();

	void setResultCallback(DialogCallback callback);
	void btn_menuCallback(Ref*sender, Widget::TouchEventType a);
	void btn_resetCallback(Ref*sender, Widget::TouchEventType a);
	void btn_nextCallback(Ref*sender, Widget::TouchEventType a);
private:
	Dialog			*m_pDialog;
	DialogCallback	m_fCallback;
	Layout			*m_pLayout;
};

#endif