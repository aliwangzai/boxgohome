#include "Utils.h"
#include "CheckBox.h"
#include "AdManager.h"
#include <time.h>

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



Node* Utils::createTrail()
{
	auto trailBox = CheckBox::create("ui/btn_motionblur.png", "ui/btn_motionblur2.png");
	//trailBox->setCurrentState(Utils::getSoundSwitch());
	return trailBox;
}

Node* Utils::createSound()
{
	auto soundCheckBox = CheckBox::create("ui/btn_music.png", "ui/btn_music2.png");
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
	auto musicCheckBox = CheckBox::create("ui/btn_sound.png", "ui/btn_sound2.png");
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

long long Utils::getCurrentTime()
{
	clock_t time = clock();
	return time;
}

int Utils::getStar(int score)
{
	int sumScore = 5 * 1000 + 6000;
	if (score >= sumScore / 4 * 3){
		return 3;
	}else if (score >= sumScore / 4 * 2){
		return 2;
	}else if (score >= sumScore / 4){
		return 1;
	}else if(score >= 0) {
		return 0;
	}
	return 0;
}

int Utils::getScore(int level)
{
	char buffer[128];
	sprintf(buffer, "user_score_%d", level);
	int oldScore = UserDefault::getInstance()->getIntegerForKey(buffer);
	return oldScore;
}