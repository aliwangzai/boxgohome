#ifndef __WALLSPRITE_H__
#define __WALLSPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

class Wall: public Sprite
{
public:
	Wall();
	~Wall();

	bool initWithMap(const ValueMap &valueMap );

	void setContactTestBitmask(int mask);
	void setCategoryBitmask(int mask);
	void setCollisionBitmask(int mask);

protected:
	int			 m_nGid;
	int			 m_nType;
	std::string	 m_sName;
	Point		 m_initPos;
	float		 m_rotation;
};

#endif