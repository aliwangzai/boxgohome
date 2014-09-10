#include "Utils.h"
#include "CheckBox.h"
#include "AdManager.h"

bool Utils::m_bMusicSwitch = true;
bool Utils::m_bSoundSwitch = true;


SpriteFrame* Utils::getSpriteFrame(std::string szSpriteFrameName)
{
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szSpriteFrameName);
	if (frame == nullptr)
	{
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(szSpriteFrameName);
		auto size = texture->getContentSize();
		frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));
	}
	return frame;
}

Sprite* Utils::createSprite(std::string szSprite)
{
	auto frame = Utils::getSpriteFrame(szSprite);
	if (frame == nullptr)
	{
		return Sprite::create(szSprite);
	}
	return Sprite::createWithSpriteFrame(frame);
}

Size Utils::getWinSize()
{
	return Director::getInstance()->getVisibleSize();
}

std::string Utils::getWallByType(int type)
{
	std::string fileName;
	switch (type)
	{
	case 1://横着的蓝色砖
		fileName = "maps/2.png";
		break;
	case 2://竖着的蓝色砖
		fileName = "maps/2_1.png";
		break;
	case 3://横着的红色砖
		fileName = "maps/42.png";
		break;
	case 4://旗子
		fileName = "maps/41.png";
		break;
	case 5://木箱
		fileName = "maps/woodenCrate_01.png";
		break;
	}
	return fileName;
}

Node* Utils::createSound()
{
	auto soundCheckBox = CheckBox::create("music_open.png", "music_close.png");
	soundCheckBox->setCallback([=](bool state){
		Utils::reverseSound();
		if (!state){
			CCLOG("%s", "play sound");
			AdManager::getInstance()->showBannerAD();
		}
		else
		{
			CCLOG("%s", "close sound");
			AdManager::getInstance()->hideBannerAD();
		}
	});
	soundCheckBox->setCurrentState(Utils::getSoundSwitch());
	return soundCheckBox;
}

Node* Utils::createMusic()
{
	auto musicCheckBox = CheckBox::create("sound_open.png", "sound_close.png");
	musicCheckBox->setCallback([=](bool state){
		Utils::reverseMusic();
		if (!state)
		{
			CCLOG("%s", "play music");
			AdManager::getInstance()->showBannerAD();
		}
		else
		{
			CCLOG("%s", "close music");
			AdManager::getInstance()->hideBannerAD();
		}
	});
	musicCheckBox->setCurrentState(Utils::getMusicSwitch());
	return musicCheckBox;
}