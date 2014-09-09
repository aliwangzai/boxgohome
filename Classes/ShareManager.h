#ifndef __SHAREMANAGER_H__
#define __SHAREMANAGER_H__

#include "cocos2d.h"
#include "C2DXShareSDK.h"
USING_NS_CC;
using namespace cn::sharesdk;

class ShareManager: public Ref
{
public:
	ShareManager();
	~ShareManager();

	static ShareManager* getInstance();

	void setShareAttribute(std::string key, std::string value);
	void sendShare();

private:
	Dictionary			*m_pContent;
};

#endif