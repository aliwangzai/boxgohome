#ifndef __WOODENCRATE_H__
#define __WOODENCRATE_H__

#include "Wall.h"

class WoodenCrate: public Wall
{
public:
	WoodenCrate();
	~WoodenCrate();

	bool init(const ValueMap &valueMap , const ValueMap &valueMap2);

	static WoodenCrate* create(const ValueMap &valueMap , const ValueMap &valueMap2);
};

#endif