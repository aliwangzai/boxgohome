#include "AppDelegate.h"
#include "GameWorld.h"
#include "Welcome.h"
#include "C2DXShareSDK\C2DXShareSDK.h"
using namespace cn::sharesdk;

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	this->initShareSDK();
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::createWithRect("My Game", Rect(0.0f, 0.0f, 854, 480));
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
	C2DXShareSDK::open(CCString::create("api20"), false);

	CCDictionary *sinaConfigDict = CCDictionary::create();
	sinaConfigDict->setObject(CCString::create("568898243"), "app_key");
	sinaConfigDict->setObject(CCString::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
	sinaConfigDict->setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
	C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
}
