#ifndef BrokenWall_h__
#define BrokenWall_h__
#include "Wall.h"



class BrokenWall : public  Wall
{
public:
	BrokenWall();
	~BrokenWall();

	static BrokenWall* create(const ValueMap &valueMap , const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap , const ValueMap &gidProperties);

};



#endif // WoodWall_h__
