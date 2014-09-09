#ifndef __BLUEWALL_H__
#define __BLUEWALL_H__

#include "BaseEntity.h"

class BlueWall : public BaseEntity
{
public:
	BlueWall();
	~BlueWall();

	bool init(const ValueMap &valueMap,const ValueMap &valueMap2);

	static BlueWall* create(const ValueMap &valueMap , const ValueMap &valueMap2);

};

#endif

