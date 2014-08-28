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
		auto layer = Layer::create();
		scene->addChild(layer);
		return scene;
	}
	return nullptr;
}

bool TestLayer::init()
{

	return true;
}
