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
	bool contactLogicPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve, ContactLogic *logic);

private:
	void updateState(float dt);

private:
	bool	m_bIsContactFlag;
	bool	m_bIsWin;
};

#endif

