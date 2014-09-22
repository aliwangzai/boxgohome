#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
USING_NS_CC;

enum DialogEvent
{
    Event_show,
    Event_hide
};

typedef std::function<void(void *data)> DialogCallback;

class Dialog: public Layer
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
	void setEnableClickClose(bool enable);
	void setTouchEnabled(bool enable);

	void showDialog();
	void hideDialog();
    
    void setDisplayCallback(DialogCallback callback);

private:
	Node*			m_pContentPanel;
	bool			m_bEnableClickClose;
	int				m_nOrderZ;
	int				m_nTouchPriority;
    DialogCallback m_fCallback;
};

#endif