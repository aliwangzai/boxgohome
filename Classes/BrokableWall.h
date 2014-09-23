#ifndef BrokableWall_h
#define BrokableWall_h
#include "BaseEntity.h"



class BrokableWall : public  BaseEntity
{
private :
	int m_durability;
	bool m_bIsCanContact;

public:
	BrokableWall();
	~BrokableWall();

	static BrokableWall* create(const ValueMap &valueMap , const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap , const ValueMap &gidProperties);

	virtual bool contactLogicBegin( PhysicsContact &contact, ContactLogic *logic );

	virtual void contactLogicSeperate( PhysicsContact &contact, ContactLogic *logic );

	void updateContactState(float dt);

};



#endif // BrokableWall_h
