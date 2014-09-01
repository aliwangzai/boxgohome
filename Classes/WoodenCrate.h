#ifndef __WOODENCRATE_H__
#define __WOODENCRATE_H__

#include "Wall.h"

class WoodenCrate: public Wall
{
public:
	WoodenCrate();
	~WoodenCrate();

	bool init(const ValueMap &valueMap);

	static WoodenCrate* create(const ValueMap &valueMap);
};

#endif