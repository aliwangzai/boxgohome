#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "BaseEntity.h"

class Enemy : public BaseEntity
{
public:
	Enemy();
	~Enemy();

	static Enemy* create(const ValueMap &valueMap, const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap, const ValueMap &gidProperties);

	void updateVelocity(float dt);

	void onExit();

	bool contactLogicBegin(PhysicsContact &contact, ContactLogic *logic);
	void contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic);

private:
};

#endif