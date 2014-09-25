#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"
USING_NS_CC;

class Utils: public Ref
{
private:
	static bool		m_bSoundSwitch;
	static bool		m_bMusicSwitch;
	static bool		m_bTrailSwitch;
public:
	static SpriteFrame* getSpriteFrame(std::string szSpriteFrameName);

	static Sprite* createSprite(std::string szSpriteName);

	static std::string getWallByType(int type);

	static Size getWinSize();

	static bool getSoundSwitch() { return Utils::m_bSoundSwitch; }
	static bool getMusicSwitch() { return Utils::m_bMusicSwitch; }
	static bool getTrailSwitch() { return Utils::m_bTrailSwitch; }

	static void reverseSound(){ Utils::m_bSoundSwitch = !Utils::m_bSoundSwitch; }
	static void reverseMusic(){ Utils::m_bMusicSwitch = !Utils::m_bMusicSwitch; }
	static void reverseTrail(){ Utils::m_bTrailSwitch = !Utils::m_bTrailSwitch; }

	static Node* createSound();
	static Node* createMusic();
	static Node* createTrail();


	static long long getCurrentTime();

	static int getStar(int score);

	static int getScore(int level);
	
};

#endif