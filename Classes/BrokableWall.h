#ifndef BrokableWall_h
#define BrokableWall_h
#include "BaseEntity.h"



class BrokableWall : public  BaseEntity
{
private :
	int m_durability;

public:
	BrokableWall();
	~BrokableWall();

	static BrokableWall* create(const ValueMap &valueMap , const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap , const ValueMap &gidProperties);

	virtual bool contactLogicBegin( PhysicsContact &contact, ContactLogic *logic );

	virtual void contactLogicSeperate( PhysicsContact &contact, ContactLogic *logic );

};



#endif // BrokableWall_h
