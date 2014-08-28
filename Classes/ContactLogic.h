#ifndef __CONTACTLOGIC_H__
#define __CONTACTLOGIC_H__

#include "cocos2d.h"
USING_NS_CC;

class GameWorld;
class ContactLogic: public Node
{
public:
	ContactLogic();
	~ContactLogic();

	bool initWithGameWorld(const GameWorld *gameWorld);

	static ContactLogic* create(const GameWorld *gameWorld);

	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	void onContactSeperate(PhysicsContact& contact);

	void update(float dt);

private:
	const GameWorld		*m_pGameWorld;
	bool				m_bIsWin;
};

#endif