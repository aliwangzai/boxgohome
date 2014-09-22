#include "LevelSelector.h"
#include "VisibleRect.h"
#include "GameWorld.h"
#include "Background.h"
#include "LevelState.h"
#include "CheckBox.h"
#include "Utils.h"
#include "AdManager.h"

LevelSelector::LevelSelector()
{
	// user 
	cur = 1;

	//configs & develop 
	max = 30;
	numColumns =  6;
	padding = Vec2(10 , 10);

	//calc
	numRows = max / numColumns ;
	if (max % numColumns != 0)
		numRows ++;
}


LevelSelector::~LevelSelector()
{
}


void LevelSelector::setStarForLevel(int level , ProgressTimer * star , Sprite * bg)
{
	// getScore for level
	int cur = LevelState::getInstance()->getCurrentLevel();
	if (level > cur) 
	{
		star->setPercentage(0);
		bg->setVisible(false);
	}
	else if (level <= cur)
	{
		int starNum = Utils::getStar(Utils::getScore(level));
		//UserDefault::getInstance()->getIntegerForKey(CCString::createWithFormat("stars_1_%d" ,level)->getCString() , 1);
		star->setPercentage(33 * starNum);
	}
	//
	
}

MenuItem * LevelSelector::createMenuItem(Menu * m , int level , int x, int y  )
{
	auto item = MenuItemImage::create("ui/lv_normal.png" ,"ui/lv_selected.png" ,"ui/lv_locked.png" , [=](Ref * sender){this->onClickMenuItem(sender);});
	TTFConfig ttfConfig("ui/grobold.ttf", 18);
	auto label = Label::createWithTTF(ttfConfig , CCString::createWithFormat("%d" , level)->getCString());
	label->setPosition(item->getContentSize()/2);
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 1);
	item->addChild(label);
	item->setTag(level);
	//item add progressbar _star
	auto progress_bg = Sprite::create("ui/start_blank.png");
	auto progress = ProgressTimer::create(Sprite::create("ui/start_full.png"));
	progress->setMidpoint(Vec2(0, 1));
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setType(ProgressTimer::Type::BAR);
	progress_bg->setPosition(Point(38 , 20));
	progress->setPosition(Point(38 ,20));
	item->addChild(progress_bg);
	item->addChild(progress);

	setStarForLevel(level , progress , progress_bg);

	m->addChild(item);
	Size size = item->getContentSize();
	//if (x == 0)
	item->setAnchorPoint(Vec2(0, 1));
	float	paddingX = padding.x * x;
	float	paddingY = padding.y * y;
	item->setPosition(Vec2(x * size.width + paddingX , - y * size.height - paddingY));
	m->setPosition( Vec2(- numColumns * size.width/2 - paddingX/2 , numRows* size.height/2 + paddingY/2) + VisibleRect::center());
	return item;
}

void LevelSelector::onClickMenuItem( Ref * sender )
{
	MenuItemImage * item = (MenuItemImage*)sender;
	int level = item->getTag();
	CCLOG("goto level:%d" ,  level);
	LevelState::getInstance()->setSelectedLevel(level);
	Director::getInstance()->replaceScene(GameWorld::createScene());
}

/** 
 ** <"User.Level"> stored as a Key of Current Level in UserDefault.xml; 
 * */
bool LevelSelector::init()
{
	
	Menu * menu = Menu::create();
	addChild(menu);
	//cloud.

	auto bgcloud = Background::create();
	addChild(bgcloud , -1);

	//back main buttons
	//menu->setPosition(Vec2::ZERO);

	cur = LevelState::getInstance()->getCurrentLevel();
	
	for (int i = 0 ; i < numRows ; i ++)
	{
		for (int j = 0 ; j < numColumns ; j++)
		{
			int pos = i * numColumns + j + 1;
			if (pos > max)
			{
				return true;
			}
			auto item = createMenuItem(menu , pos , j , i );
			if (pos > cur)
				item->setEnabled(false);
		}
	}
	
	this->initSound();

	return true;
}

bool LevelSelector::initSound()
{
	auto soundCheckBox = Utils::createSound();
	auto size = soundCheckBox->getContentSize();
	soundCheckBox->setPosition(VisibleRect::leftBottom() + Point(size / 2) + Point(20, 10));
	this->addChild(soundCheckBox);

	auto musicCheckBox = Utils::createMusic();
	musicCheckBox->setPosition(soundCheckBox->getPosition() + Point(80, 0));
	this->addChild(musicCheckBox);
	return true;
}

LevelSelector * LevelSelector::create()
{
	LevelSelector * o =  new LevelSelector;
	o->init();
	o->autorelease();
	return o;
}


///---
Scene * LevelSelectScene::createScene()
{
	Scene * s = Scene::create();
	s->addChild(LevelSelectScene::create());
	return s;
}

bool LevelSelectScene::init()
{
	auto selector = LevelSelector::create();
	addChild(selector);
	return true;
}

void LevelSelectScene::onExit()
{
	Layer::onExit();

	AdManager::getInstance()->hideBannerAD();
}

void LevelSelectScene::onEnter()
{
    Layer::onEnter();
    
	AdManager::getInstance()->showBannerAD();
}
