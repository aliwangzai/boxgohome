#include "DialogManager.h"

static DialogManager* dialogManager = nullptr;

DialogManager* DialogManager::getInstance()
{
	if (dialogManager == nullptr)
	{
		dialogManager = new (std::nothrow) DialogManager;
	}
	return dialogManager;
}