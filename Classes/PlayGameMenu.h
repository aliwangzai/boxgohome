#ifndef __PLAYGAMEMENU_H__
#define __PLAYGAMEMENU_H__

#include "cocos2d.h"
USING_NS_CC;

class GameMap;
class BoxSprite;
class PlayGameMenu: public Node
{
public:
	PlayGameMenu();
	~PlayGameMenu();

	bool init();
	bool initGameMap();
	bool initBoxSprite();
	bool initListener();

	CREATE_FUNC(PlayGameMenu);

	virtual void update(float dt);

	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	void onContactSeperate(PhysicsContact& contact);

private:

	GameMap			*m_pGameMap;
	BoxSprite		*m_pBoxSprite;
};

#endif