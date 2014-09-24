#ifndef __TUTORIALMENU_H__
#define __TUTORIALMENU_H__

#include "cocos2d.h"
USING_NS_CC;

struct MoveData
{
	Point m_ArrowPointOne;
	Point m_ArrowPointTwo;
	Point m_JumpPoint;

	MoveData(){}
	MoveData(Point one, Point two, Point three) :
		m_ArrowPointOne(one),
		m_ArrowPointTwo(two),
		m_JumpPoint(three)
	{}
};

class GameMap;
class BoxSprite;
class ArrowSprite;
class TutorialMenu: public Node
{
public:
	TutorialMenu();
	~TutorialMenu();

	bool init();
	bool initGameMap();
	bool initBoxSprite();
	bool initArrowSprite();
	bool initHand();
	bool initMoveData();
	void animateFinish();

	void playAnimate();
	
	void update(float dt);

	CREATE_FUNC(TutorialMenu);

private:
	GameMap *m_pGameMap;
	BoxSprite *m_pBoxSprite;
	Sprite*	m_pHand;
	ArrowSprite *m_pArrowSprite;
	MoveData	m_moveDatas[4];
	int			m_nCurrentIdx;
};

#endif