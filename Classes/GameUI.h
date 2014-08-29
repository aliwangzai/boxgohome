#ifndef __GAMEUI_H__
#define __GAMEUI_H__

#include "cocos2d.h"
USING_NS_CC;

class GameUI: public Node
{
public:
	GameUI();
	~GameUI();

	bool init();
	bool initScoreUI();
	bool initMenu();
	bool initMoreGame();
	bool initSound();

	void setDefaultValue();

	CREATE_FUNC(GameUI);

	void setLevel(int level);
	void setScore(int score);
	void setBonus(int bonus);
	void setJumps(int jumps);

	void jumpsSelfSub();

	virtual void update(float dt);

private:
	Label		*m_pLevelLabel;
	Label		*m_pScoreLabel;
	Label		*m_pBonusLabel;
	Label		*m_pJumpsLabel;
	int			m_nLevel;
	int			m_nScore;
	int			m_nBonus;
	int			m_nJump;
};

#endif