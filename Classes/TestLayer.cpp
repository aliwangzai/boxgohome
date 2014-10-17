#include "TestLayer.h"


TestLayer::TestLayer()
{
}


TestLayer::~TestLayer()
{
}

Scene* TestLayer::createScene()
{
	auto scene = Scene::create();
	if (scene)
	{
		auto layer = TestLayer::create();
		scene->addChild(layer);
		return scene;
	}
	return nullptr;
}

bool TestLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto label = Label::createWithSystemFont("helloWorldlkasd\njfla;dfjalksdjfa;sdjlasdjflkasdgjal;sdgja;sdfjalsdkf", "", 32);
	label->setDimensions(100, 200);
	int height = label->getHeight();
	CCLOG("height : %d", height);
	label->setPosition(winSize / 2);
	this->addChild(label);

	return true;
}
