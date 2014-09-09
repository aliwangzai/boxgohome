#ifndef __YELLOWWALL_H__
#define __YELLOWWALL_H__

#include "BaseEntity.h"

class YellowWall : public BaseEntity
{
public:
	YellowWall();
	~YellowWall();

	bool init(const ValueMap &valueMap, const ValueMap & gidProperties);

	void playFlagAnimate();

	static YellowWall* create(const ValueMap &valueMap, const ValueMap & gidProperties);

	bool contactLogicBegin(PhysicsContact &contact, ContactLogic *logic);
	void contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic);
};

#endif

