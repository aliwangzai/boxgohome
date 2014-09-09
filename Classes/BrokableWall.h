#ifndef BrokableWall_h
#define BrokableWall_h
#include "Wall.h"



class BrokableWall : public  Wall
{
private :
	int brokenLevel;

public:
	BrokableWall();
	~BrokableWall();

	static BrokableWall* create(const ValueMap &valueMap , const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap , const ValueMap &gidProperties);

};



#endif // BrokableWall_h
