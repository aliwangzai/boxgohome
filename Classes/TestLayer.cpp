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
	/*Size winSize = Director::getInstance()->getWinSize();

	auto scrollView = ScrollView::create(winSize / 2);
	scrollView->setBounceable(true);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	scrollView->setDelegate(this);
	this->addChild(scrollView);
	scrollView->setPosition(winSize / 4);
	scrollView->setContentSize(Size(winSize.width / 2, winSize.height / 2 + 100));
	scrollView->setContentOffset(Point(0, scrollView->getViewSize().height - scrollView->getContentSize().height));

	auto label = Label::createWithSystemFont("klasfalskdfjalsdflasdklfj\nasldjflaksdjflasjdflkasdfasdf\nklasfalskdfjalsdflasdklfj\nasldjflaksdjflasjdflkasdfasdf\nklasfalskdfjalsdflasdklfj\nasldjflaksdjflasjdflkasdfasdf\nklasfalskdfjalsdflasdklfj\nasldjflaksdjflasjdflkasdfasdf\nklasfalskdfjalsdflasdklfj\nasldjflaksdjflasjdflkasdfasdf\nklasfalskdfjalsdflasdklfj\nasldjflaksdjflasjdflkasdfasdf\n", "", 32);
	label->setAnchorPoint(Point(0, 1));
	label->setPositionY(scrollView->getContentSize().height);
	//label->setDimensions(winSize.width / 2, winSize.height / 2);
	scrollView->addChild(label);*/

	return true;
}
