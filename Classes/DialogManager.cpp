#include "DialogManager.h"
#include "LevelComplete.h"

static DialogManager* dialogManager = nullptr;

DialogManager* DialogManager::getInstance()
{
	if (dialogManager == nullptr)
	{
		dialogManager = new (std::nothrow) DialogManager;
	}
	return dialogManager;
}

LevelComplete* DialogManager::showLvelComplete(void *data, DialogCallback callback)
{
	auto dialog = Dialog::create();
	auto layer = LevelComplete::create(dialog);
	layer->databind(data);
	dialog->setContentPanel(layer);
	dialog->setEnableClickClose(true);
	dialog->showDialog();
	return layer;
}