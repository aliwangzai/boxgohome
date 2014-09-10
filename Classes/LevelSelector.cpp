#include "LevelSelector.h"
#include "VisibleRect.h"
#include "GameWorld.h"
#include "Background.h"
#include "LevelState.h"
#include "CheckBox.h"

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

MenuItem * LevelSelector::createMenuItem(Menu * m , int level , int x, int y  )
{
	auto item = MenuItemImage::create("ui/lv_normal.png" ,"ui/lv_selected.png" ,"ui/lv_locked.png" , [=](Ref * sender){this->onClickMenuItem(sender);});
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 18);
	auto label = Label::createWithTTF(ttfConfig , CCString::createWithFormat("%d" , level)->getCString());
	label->setPosition(item->getContentSize()/2);
	label->setTextColor(Color4B::BLACK);
	item->addChild(label);
	item->setTag(level);
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
	auto soundCheckBox = CheckBox::create("49.png", "50.png");
	auto size = soundCheckBox->getContentSize();
	soundCheckBox->setPosition(VisibleRect::leftBottom() + Point(size / 2) + Point(20, 10));
	this->addChild(soundCheckBox);
	soundCheckBox->setCallback([=](bool state){
		if (!state) CCLOG("%s", "play sound");
		else CCLOG("%s", "close sound");
	});

	auto musicCheckBox = CheckBox::create("47.png", "48.png");
	size = musicCheckBox->getContentSize();
	musicCheckBox->setPosition(VisibleRect::leftBottom() + Point(size / 2) + Point(70, 10));
	this->addChild(musicCheckBox);
	musicCheckBox->setCallback([=](bool state){
		if (!state) CCLOG("%s", "play music");
		else CCLOG("%s", "close music");
	});
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
