#include "SettingsDiaog.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "Utils.h"
using namespace cocos2d::ui;

SettingsDiaog::SettingsDiaog()
{

}

SettingsDiaog::~SettingsDiaog()
{

}

SettingsDiaog* SettingsDiaog::create( Dialog* dialog )
{
	auto d = new (std::nothrow) SettingsDiaog;
	if (d && d->initWithDialog(dialog))
	{
		d->autorelease();
		return d;
	}
	CC_SAFE_RELEASE(d);
	return nullptr;
}

bool SettingsDiaog::initWithDialog( Dialog* dialog )
{
	this->m_pDialog = dialog;

	Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Settings.json"));
	addChild(layout);
	layout->setAnchorPoint(Vec2(0.5, 0.5));

	ImageView *imageView = static_cast<ImageView*>(layout->getChildByName("Image_1"));
	this->setContentSize(imageView->getSize());
	
	auto trail_pos = static_cast<Layout*>(layout->getChildByName("trail_pos"))->getPosition();
	auto music_pos = static_cast<Layout*>(layout->getChildByName("music_pos"))->getPosition();
	auto sound_pos = static_cast<Layout*>(layout->getChildByName("sound_pos"))->getPosition();

	auto soundCheckBox = Utils::createSound();
	soundCheckBox->setPosition(sound_pos);
	layout->addChild(soundCheckBox);

	auto musicCheckBox = Utils::createMusic();
	musicCheckBox->setPosition(music_pos);
	layout->addChild(musicCheckBox);
	
	auto trailBox = Utils::createTrail();
	trailBox->setPosition(trail_pos);
	layout->addChild(trailBox);


	return true;
}

void SettingsDiaog::databind( void *data )
{

}

void SettingsDiaog::setResultCallback( DialogCallback callback )
{
	this->m_fCallback = callback;
}

