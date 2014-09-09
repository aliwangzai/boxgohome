#ifndef BrokenWall_h__
#define BrokenWall_h__
#include "BaseEntity.h"



class BrokenWall : public  BaseEntity
{
public:
	BrokenWall();
	~BrokenWall();

	static BrokenWall* create(const ValueMap &valueMap , const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap , const ValueMap &gidProperties);

};



#endif // WoodWall_h__
