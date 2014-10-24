#include "ShareManager.h"

static ShareManager* g_pShareManager = nullptr;

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, Dictionary *shareInfo, Dictionary *error)
{
	switch (state) {
	case C2DXResponseStateBegin:
		//CCLOG("��ʼ���� -------------------- platType: %d", platType);
		break;
	case C2DXResponseStateSuccess:
		//CCLOG("����ɹ�");
		break;
	case C2DXResponseStateFail:
		//CCLOG("����ʧ��");
		break;
	case C2DXResponseStateCancel:
		//CCLOG("ȡ������");
	default:
		break;
	}
}

ShareManager* ShareManager::getInstance()
{
	if (g_pShareManager == nullptr)
	{
		g_pShareManager = new ShareManager;
	}
	return g_pShareManager;
}

ShareManager::ShareManager()
{
	m_pContent = Dictionary::create();
	m_pContent->retain();
}

ShareManager::~ShareManager()
{
	CC_SAFE_RELEASE(m_pContent);
}

void ShareManager::setShareAttribute(std::string key, std::string value)
{
	m_pContent->setObject(CCString::create(value), key);
}

void ShareManager::sendShare()
{
	C2DXShareSDK::showShareMenu(nullptr, m_pContent, Point(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
	m_pContent->removeAllObjects();
}