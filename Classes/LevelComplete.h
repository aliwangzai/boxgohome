#ifndef __LEVELCOMPLETE_H__
#define __LEVELCOMPLETE_H__

#include "cocos2d.h"
#include "Dialog.h"
USING_NS_CC;

class LevelComplete: public Node
{
public:
	LevelComplete();
	~LevelComplete();

	bool initWithDialog(Dialog* dialog);

	static LevelComplete* create(Dialog *dialog);

	void databind(void *data);

	void setResultCallback(DialogCallback callback);

private:
	Dialog			*m_pDialog;
	DialogCallback	m_fCallback;
};

#endif