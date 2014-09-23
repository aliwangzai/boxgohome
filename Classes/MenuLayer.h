#ifndef __MENULAYER_H__
#define __MENULAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace  cocos2d::ui;

class MenuLayer: public Node
{
public:
	MenuLayer();
	~MenuLayer();

	static Scene* createScene();

	virtual void onEnter();
	virtual void onExit();

	bool init();
	bool initBackground();
	bool initWithMenu();
	bool initSound();
	bool initTitle();

	void playFontAnimate();

	CREATE_FUNC(MenuLayer);

private:
	Label		*m_pJumpBoxTitle;
	Node		*m_pCurrentNode;
};

#endif