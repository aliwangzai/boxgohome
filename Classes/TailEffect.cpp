#include "TailEffect.h"

TailEffect::TailEffect()
{
	_tailCount = 1;
	objectPool = new SimpleObjectPool<Sprite *>(this , false);
}

TailEffect::~TailEffect()
{
	delete objectPool;
}


Sprite * TailEffect::newObject( int type /*= 0 */ )
{
	Sprite * s = Sprite::create(_tailImage);
	//s->retain();
	addChild(s);
	return s;
}

void TailEffect::deleteObject( Sprite * b )
{
	//b->release();
	//delete b ;
}


bool TailEffect::init( const char * image,  int count )
{
	_tailImage = image;
	initWithFile(image , count);
	setCount(count);
	this->schedule(schedule_selector(TailEffect::makeTail) , 0.1f);
	return true;
}

void TailEffect::makeTail(float dt)
{
	Sprite * tail = objectPool->get();
	tail->setOpacity(255);
	tail->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f) ,CallFuncN::create([=](Node * pSender){
		objectPool->recycle((Sprite*)pSender);
	})));
	tail->setPosition(_sprite->getPosition());
	tail->setRotation(_sprite->getRotation());
}

TailEffect * TailEffect::create( const char * image , int count  )
{
	TailEffect * s = new TailEffect;
	s->init(image , count);
	s->autorelease();
	return s;
}

void TailEffect::bindSprite( Sprite * s )
{
	_sprite = s;
}

void TailEffect::setCount( int count )
{
	_tailCount = count;
}
