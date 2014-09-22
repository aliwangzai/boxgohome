
#ifndef LevelConfig_h__
#define LevelConfig_h__

#include "cocos2d.h"
USING_NS_CC;

class LevelState 
{
public:
	int _selectedLevel;
	static LevelState * getInstance()
	{
		static LevelState state;
		return &state ;
	}
	LevelState()
	{
		//read level cfg 
		_selectedLevel = getCurrentLevel();
	}

	void unlockNewLevel()
	{
		int level = getCurrentLevel();
		CCUserDefault::getInstance()->setIntegerForKey("User.Level" , level + 1);
	}

	int  getCurrentLevel()
	{
		int level = CCUserDefault::getInstance()->getIntegerForKey("User.Level" , 1);
		return level;
		//return 15;
	}

	void setSelectedLevel(int level)
	{
		_selectedLevel = level;
	}

	int getSelectedLevel()
	{
		return _selectedLevel;
	}

	std::string getMapName()
	{
		int level = getSelectedLevel();
		return CCString::createWithFormat("maps/nmap_%d.tmx" , level)->getCString();
	}

	~LevelState(){}


};



#endif // LevelConfig_h__