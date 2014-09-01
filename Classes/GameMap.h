#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "cocos2d.h"
USING_NS_CC;

class GameMap : public Node
{
public:
	GameMap();
	~GameMap();

	bool init();
	bool initWithTmxFile(std::string &szTmxFile);
	bool initBlueBrick();
	bool initYellowBrick();
	bool initWoodenCrate();
	ValueMap getHeroValueMap();

	void loadDefaultData();

	static GameMap* createWithFile(std::string &szTmxFile);

	CREATE_FUNC(GameMap);

private:
	std::string		_szTmxFile;
	experimental::TMXTiledMap	*_map;
};

#endif