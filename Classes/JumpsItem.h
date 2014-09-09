#ifndef __JUMPSITEM_H__
#define __JUMPSITEM_H__

#include "Wall.h"

class JumpsItem: public Wall
{
public:
	JumpsItem();
	~JumpsItem();

	static JumpsItem* create(const ValueMap &valueMap, const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap, const ValueMap &gidProperties);
};

#endif