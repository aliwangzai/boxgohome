#ifndef SettingsDiaog_H
#define SettingsDiaog_H

#include "cocos2d.h"
#include "Dialog.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d::ui;


class SettingsDiaog: public Node
{
public:
	SettingsDiaog();
	~SettingsDiaog();

	static SettingsDiaog* create(Dialog* dailog);

	bool initWithDialog(Dialog* dialog);

	void databind(void *data);

	void setResultCallback(DialogCallback callback);

private:

	Dialog*			m_pDialog;
	DialogCallback  m_fCallback;
};

#endif