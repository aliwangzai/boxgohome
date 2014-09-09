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

	bool initWithGameWorld(GameWorld *gameWorld);
	void loadDefaultData();

	static ContactLogic* create(GameWorld *gameWorld);

	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	void onContactSeperate(PhysicsContact& contact);

	void update(float dt);

	void setWinState(bool isWin){ this->m_bIsWin = isWin; }
	void setLoseState(bool isLose){ this->m_bIsLose = isLose; }

private:
	GameWorld		*m_pGameWorld;
	bool				m_bIsWin;
	bool				m_bIsLose;
};

#endif