#include "GameMap.h"
#include "VisibleRect.h"
#include "BlueWall.h"
#include "YellowWall.h"
#include "WoodenCrate.h"

#include "2d\CCFastTMXTiledMap.h"
#include "2d\CCFastTMXLayer.h"

GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

GameMap* GameMap::createWithFile(std::string &szTmxFile)
{
	auto gameMap = new GameMap();
	if (gameMap && gameMap->initWithTmxFile(szTmxFile))
	{
		gameMap->autorelease();
		return gameMap;
	}
	return nullptr;
}

bool GameMap::initWithTmxFile(std::string &szTmxFile)
{
	if (szTmxFile.size() == 0)
	{
		szTmxFile = "maps/map_2.tmx";
	}
	this->_szTmxFile = szTmxFile;
	return this->init();
}

bool GameMap::init()
{
	this->_map = experimental::TMXTiledMap::create(this->_szTmxFile);
	this->addChild(this->_map, 10);
	this->initBlueBrick();
	this->initYellowBrick();
	this->initWoodenCrate();
	return true;
}

ValueMap GameMap::getHeroValueMap()
{
	ValueMap boxValues = this->_map->getObjectGroup("hero")->getObject("hero");
	return boxValues;
}

bool GameMap::initYellowBrick()
{
	ValueVector yellowValues = this->_map->getObjectGroup("yellow")->getObjects();
	for (unsigned int i = 0; i < yellowValues.size(); i++)
	{
		auto yellowWall = YellowWall::create(yellowValues.at(i).asValueMap());
		this->addChild(yellowWall);
	}
	return true;
}

bool GameMap::initBlueBrick()
{
	ValueVector blueValues = this->_map->getObjectGroup("blue")->getObjects();
	for (unsigned int v = 0; v < blueValues.size(); v++)
	{
		BlueWall *wall = BlueWall::create(blueValues.at(v).asValueMap());
		this->addChild(wall);
	}
	return true;
}

bool GameMap::initWoodenCrate()
{
	TMXObjectGroup *objectGroup = this->_map->getObjectGroup("wooden");
	if (objectGroup != nullptr)
	{
		ValueVector woodenValues = objectGroup->getObjects();
		for (unsigned int v = 0; v < woodenValues.size(); v++)
		{
			WoodenCrate *wooden = WoodenCrate::create(woodenValues.at(v).asValueMap());
			this->addChild(wooden);
		}
	}
	return true;
}

void GameMap::loadDefaultData()
{
	this->removeAllChildren();
	this->initWithTmxFile(this->_szTmxFile);
}

void GameMap::loadMapFile(std::string &filename)
{
	this->removeAllChildren();
	this->initWithTmxFile(filename);
}