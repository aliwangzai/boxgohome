#include "DialogManager.h"
#include "Dialog.h"

static DialogManager* dialogManager = nullptr;

DialogManager* DialogManager::getInstance()
{
	if (dialogManager == nullptr)
	{
		dialogManager = new (std::nothrow) DialogManager;
	}
	return dialogManager;
}

void DialogManager::showLvelComplete(void *data, DialogCallback callback)
{
	auto dialog = Dialog::create();
}