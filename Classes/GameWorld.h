#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "cocos2d.h"
#include "chipmunk.h"
USING_NS_CC;

class ArrowSprite;
class BoxSprite;
class GameUI;
class GameMap;
class ContactLogic;
class GameWorld : public Node
{
public:
	GameWorld();
	~GameWorld();
	static Scene* createScene();

	CREATE_FUNC(GameWorld);

	bool init();
	bool initListener();
	bool initBackground();
	bool initGameMap();
	bool initBoxSprite();
	bool initArrowSprite();
	bool initGameUI();
	bool initContactLogic();

	virtual void onEnterTransitionDidFinish();
	virtual void onEnter();
	virtual void onExit();

	virtual void update(float dt);

	PhysicsWorld* getPhysicsWorld()const{ return _physicsWorld; }

	bool onTouchBegan(Touch *pTouch, Event* event);
	void onTouchMoved(Touch *pTouch, Event* event);
	void onTouchEnded(Touch *pTouch, Event* event);

	ArrowSprite* getArrowSprite() const { return m_pArrowSprite; }
	BoxSprite* getBoxSprite() const { return m_pBoxSprite; }
	GameUI*	getGameUI() const { return m_pGameUI; }

	void win();
	void lose();
	void restart();
	void nextLevel();
	
private:
	PhysicsWorld *_physicsWorld;
	ArrowSprite *m_pArrowSprite;
	BoxSprite	*m_pBoxSprite;
	Vec2		m_vNormalDir;
	GameUI		*m_pGameUI;
	GameMap		*m_pGameMap;
	ContactLogic *m_pContactLogic;
};

#endif