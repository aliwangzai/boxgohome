#ifndef __WELCOME_H__
#define __WELCOME_H__

#include "cocos2d.h"
USING_NS_CC; 

class GameMap;
class BoxSprite;
class Welcome : public Node
{
public:

	bool init();
	bool initBackground();
	bool initTitle();
	bool initMenu();
	bool initEdgeMap();
	bool initLoadResource();
	bool initHero();

	virtual void onEnter();
	virtual void onExit();

	void playFontAnimate();
	void playHeroAnimate();

	static Scene* createScene();

	CREATE_FUNC(Welcome);

	virtual void onEnterTransitionDidFinish();

private:
	Label		*m_pJumpBoxTitle;
	GameMap		*m_pGameMap;
	BoxSprite	*m_pBoxSprite;
	PhysicsWorld *m_pPhysicsWorld;
	Point		m_vHeroInitPos;
};

#endif