#ifndef __LEVELCOMPLETE_H__
#define __LEVELCOMPLETE_H__

#include "cocos2d.h"
USING_NS_CC;

class Dialog;
class LevelComplete: public Node
{
public:
	LevelComplete();
	~LevelComplete();

	bool initWithDialog(Dialog* dialog);

	static LevelComplete* create(Dialog *dialog);

private:
	Dialog		*m_pDialog;
};

#endif