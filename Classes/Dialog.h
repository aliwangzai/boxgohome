#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
USING_NS_CC;

class Dialog: public Node
{
public:
	Dialog();
	~Dialog();

	CREATE_FUNC(Dialog);

	bool init();

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);

	void setContentPanel(Node *node);
	void setTouchPriority(int priority);
	void setOrderZ(int orderZ);
	void setEnableClickClose(bool enable);

private:
	Node*			m_pContentPanel;
	bool			m_bEnableClickClose;
	int				m_nOrderZ;
	int				m_nTouchPriority;
};

#endif