#ifndef __BOXSPRITE_H__
#define __BOXSPRITE_H__

#include "cocos2d.h"
#include "chipmunk.h"
USING_NS_CC;

class GameWorld;
class BoxSprite : public Sprite
{
public:
	CREATE_FUNC(BoxSprite);

	static BoxSprite* create(const ValueMap &valueMap);

	bool init();
	bool initWithMap(const ValueMap &valueMap);
	bool initBoxAnimate();
	void applyForce(const Vec2 &force);
	void setContactTestBitmask(int mask);
	void setCategoryBitmask(int mask);
	void setCollisionBitmask(int mask);

	void loadDefaultData(const ValueMap &valueMap);

private:
	GameWorld	*m_pGameWorld;
	float		m_fMaxForce;
};

#endif