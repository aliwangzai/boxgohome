#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Wall.h"

class Enemy: public Wall
{
public:
	Enemy();
	~Enemy();

	static Enemy* create(const ValueMap &valueMap, const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap, const ValueMap &gidProperties);

	void updateVelocity(float dt);

private:
};

#endif