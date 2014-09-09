#ifndef BrokableWall_h
#define BrokableWall_h
#include "BaseEntity.h"



class BrokableWall : public  BaseEntity
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
