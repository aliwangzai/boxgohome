#ifndef __BLUEWALL_H__
#define __BLUEWALL_H__

#include "Wall.h"

class BlueWall: public Wall
{
public:
	BlueWall();
	~BlueWall();

	bool init(const ValueMap &valueMap);

	static BlueWall* create(const ValueMap &valueMap);
};

#endif

