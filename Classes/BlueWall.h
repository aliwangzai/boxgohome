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

	virtual bool contactLogicBegin(PhysicsContact &contact, ContactLogic *logic);

	virtual void contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic);

	void contactEffect(PhysicsContact &contact);
};

#endif

