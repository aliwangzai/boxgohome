#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;

class Enemy: public Sprite
{
public:
	Enemy();
	~Enemy();

	static Enemy* create(const ValueMap &valueMap, const ValueMap &gidProperties);

	bool initWithMap(const ValueMap &valueMap, const ValueMap &gidProperties);

	virtual void update(float dt);

private:
	int			 m_nGid;
	int			 m_nType;
	std::string	 m_sName;
	Point		 m_initPos;
	float		 m_rotation;
};

#endif