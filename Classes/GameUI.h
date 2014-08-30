#ifndef __GAMEUI_H__
#define __GAMEUI_H__

#include "cocos2d.h"
USING_NS_CC;

class GameWorld;
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
	bool initWithGameWorld(GameWorld* gameWorld);

	void setDefaultValue();

	CREATE_FUNC(GameUI);
	static GameUI* create(GameWorld* gameWorld);

	void setLevel(int level);
	void setScore(int score);
	void setBonus(int bonus);
	void setJumps(int jumps);

	bool jumpsSelfSub();

	int getJumpCount() const { return this->m_nJump; }
	int getLevel() const { return this->m_nLevel; }
	int getScore() const { return this->m_nScore; }
	int getBonus() const { return this->m_nBonus; }

	virtual void update(float dt);

	void restart();

private:
	GameWorld*	m_pGameWorld;
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