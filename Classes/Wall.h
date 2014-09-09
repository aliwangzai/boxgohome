#ifndef __WALLSPRITE_H__
#define __WALLSPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

enum WallType
{
	wallType_Normal,
	wallType_broken , 
	wallType_brokable,
	wallType_Yellow,
	wallType_Flag,
	wallType_Wood,
	wallType_Enemy
};

class Wall: public Sprite
{
public:
	Wall();
	~Wall();

	bool initWithMap(const ValueMap &valueMap );

	void setContactTestBitmask(int mask);
	void setCategoryBitmask(int mask);
	void setCollisionBitmask(int mask);

	WallType getWallType() const { return m_wallType; }
	void setPositionAndRotation();
	void setWallType(WallType wallType);
protected:
	int			 m_nGid;
	int			 m_nType;
	std::string	 m_sName;
	Point		 m_initPos;
	float		 m_rotation;
	WallType     m_wallType;
};

#endif