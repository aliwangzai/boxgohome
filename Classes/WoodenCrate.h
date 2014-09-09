#ifndef __WOODENCRATE_H__
#define __WOODENCRATE_H__

#include "BaseEntity.h"

class WoodenCrate : public BaseEntity
{
public:
	WoodenCrate();
	~WoodenCrate();

	bool init(const ValueMap &valueMap , const ValueMap &valueMap2);

	static WoodenCrate* create(const ValueMap &valueMap , const ValueMap &valueMap2);
};

#endif