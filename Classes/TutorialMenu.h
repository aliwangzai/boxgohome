#ifndef __TUTORIALMENU_H__
#define __TUTORIALMENU_H__

#include "cocos2d.h"
USING_NS_CC;

class GameMap;
class BoxSprite;
class TutorialMenu: public Node
{
public:
	TutorialMenu();
	~TutorialMenu();

	bool init();
	bool initGameMap();
	bool initBoxSprite();

	CREATE_FUNC(TutorialMenu);

private:
	GameMap *m_pGameMap;
	BoxSprite *m_pBoxSprite;
};

#endif