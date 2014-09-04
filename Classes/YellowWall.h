#ifndef __YELLOWWALL_H__
#define __YELLOWWALL_H__

#include "Wall.h"

class YellowWall : public Wall
{
public:
	YellowWall();
	~YellowWall();

	bool init(const ValueMap &valueMap, const ValueMap & gidProperties);;

	void playFlagAnimate();

	static YellowWall* create(const ValueMap &valueMap, const ValueMap & gidProperties);
};

#endif

