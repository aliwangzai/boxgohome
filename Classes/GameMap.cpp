#include "GameMap.h"
#include "VisibleRect.h"
#include "BlueWall.h"
#include "YellowWall.h"
#include "WoodenCrate.h"
#include "Enemy.h"
#include "JumpsItem.h"

#include "2d\CCFastTMXTiledMap.h"
#include "2d\CCFastTMXLayer.h"
#include "BrokableWall.h"

#define MAP_TAG 10


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
	this->setContentSize(Size(960, 640));

	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(0.5, 0.5));

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
	this->addChild(this->_map, MAP_TAG);
	this->initObjects();
	return true;
}

ValueMap GameMap::getHeroValueMap()
{
	return m_heroValueMap;
}

void GameMap::initObjects()
{
	TMXObjectGroup *objectGroup = this->_map->getObjectGroup("game");
	if (objectGroup == nullptr) return;
	ValueVector objects = objectGroup->getObjects();
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		ValueMap objProperties = objects.at(i).asValueMap();
		ValueMap gidProperties = this->_map->getPropertiesForGID(objProperties["gid"].asInt()).asValueMap();
		std::string type = gidProperties["type"].asString();
		if (type == "brick")
		{
			BlueWall *wall = BlueWall::create(objProperties , gidProperties);
			this->addChild(wall);
		}else if (type == "target")
		{
			auto yellowWall = YellowWall::create(objProperties , gidProperties);
			this->addChild(yellowWall);
		}else if (type == "flag")
		{
			auto yellowWall = YellowWall::create(objProperties , gidProperties);
			this->addChild(yellowWall);
		}else if (type == "wood")
		{
			WoodenCrate *wooden = WoodenCrate::create(objProperties , gidProperties);
			this->addChild(wooden);
		}else if (type == "hero")
		{
			this->m_heroValueMap = objProperties;
		}
		else if (type == "enemy_gray" || type == "enemy_purple")
		{
			auto enemy_gray = Enemy::create(objProperties, gidProperties);
			this->addChild(enemy_gray);
		}else if (type == "brokable")
		{
			auto brokable_wall = BrokableWall::create(objProperties,gidProperties);
			addChild(brokable_wall);
		}
		else if (type == "jumps_item")
		{
			auto jumpsItem = JumpsItem::create(objProperties, gidProperties);
			this->addChild(jumpsItem);
		}
		//auto yellowWall = YellowWall::create(yellowValues.at(i).asValueMap());
		//this->addChild(yellowWall);
	}
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