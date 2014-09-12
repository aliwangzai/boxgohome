#include "AppDelegate.h"
#include "GameWorld.h"
#include "Welcome.h"
#include "TestLayer.h"
#include "C2DXShareSDK.h"
using namespace cn::sharesdk;
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{	
	cocostudio::GUIReader::destroyInstance();
	cocostudio::DictionaryHelper::destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching() {
	this->initShareSDK();
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::createWithRect("My Game", Rect(0.0f, 0.0f, 1136, 640));
        director->setOpenGLView(glview);
    }

	srand((unsigned)time(NULL));

	auto frameSize = Director::getInstance()->getWinSize();
	auto lsSize = Size(960, 640);
	float scaleX = frameSize.width / lsSize.width;
	float scaleY = frameSize.height / lsSize.height;

	float scale_width = 0, scale_height = 0;
	if (scaleX > scaleY)
		scale_width = scaleX / (frameSize.height / lsSize.height);
	else
		scale_width = scaleX / (frameSize.width / lsSize.width);

	if (scaleX > scaleY)
		scale_height = scaleY / (frameSize.height / lsSize.height);
	else
		scale_height = scaleY / (frameSize.width / lsSize.width);

	float scale = std::max(scale_width, scale_height);

	glview->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = Welcome::createScene();

	//auto scene = TestLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initShareSDK()
{
	C2DXShareSDK::open(CCString::create("2f5d7a211988"), true);
}
