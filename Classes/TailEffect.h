#ifndef TailEffect_h__
#define TailEffect_h__

#include "cocos2d.h"
#include "ObjectPool.h"
USING_NS_CC;

class TailEffect : public SpriteBatchNode , ObjectPoolDelegate <Sprite *>
{
	Sprite * _sprite;
	SimpleObjectPool <Sprite *> * objectPool;
	int _tailCount;
	const char * _tailImage;
public:

	TailEffect();
	~TailEffect();

	bool init( const char * image, int count );

	static TailEffect * create(const char * image , int count = 5);

	void bindSprite(Sprite * s);

	void setCount(int count );
	Sprite * newObject( int type /*= 0 */ );
	void deleteObject( Sprite * b );

	void makeTail(float dt);
	
};


#endif // TailEffect_h__
