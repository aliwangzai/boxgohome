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

	auto node = Node::create();
	this->addChild(node);

	auto sprite = Sprite::create("HelloWorld.png");
	node->addChild(sprite);
	sprite->setPosition(winSize / 2);

	auto sprite2 = Sprite::create("HelloWorld.png");
	sprite->addChild(sprite2);
	sprite2->setScale(0.5f);

	node->setOpacity(125);
	return true;
}
