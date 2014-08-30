#ifndef __LEVELCOMPLETELOSS_H__
#define __LEVELCOMPLETELOSS_H__

#include "cocos2d.h"
#include "Dialog.h"
USING_NS_CC;

class LevelCompleteLoss: public Node
{
public:
	LevelCompleteLoss();
	~LevelCompleteLoss();

	static LevelCompleteLoss* create(Dialog* dailog);

	bool initWithDialog(Dialog* dialog);
	bool initWithMenu();
	bool initWithTitle();

	void databind(void *data);

	void setResultCallback(DialogCallback callback);

private:

	Dialog*			m_pDialog;
	DialogCallback  m_fCallback;
};

#endif