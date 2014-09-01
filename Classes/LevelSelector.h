#ifndef LevelSelector_h__
#define LevelSelector_h__

#include "cocos2d.h"
USING_NS_CC;

class LevelItem 
{
public:
	LevelItem(){};
	~LevelItem(){};
	MenuItem * item;
	int index;

};


class LevelSelector : public Node
{
	int cur;
	int max;
	Vec2 padding;
	LevelItem * items;

	int numColumns;
	int numRows;
public:
	LevelSelector();
	~LevelSelector();

	static LevelSelector * create();

	bool init();
	MenuItem * createMenuItem(Menu * m , int level , int x, int y );
	void onClickMenuItem(Ref * sender);
};


class LevelSelectScene : public Layer
{

public:
	LevelSelectScene(){};
	~LevelSelectScene(){};

	bool init();

	CREATE_FUNC(LevelSelectScene);

	static Scene * createScene();


};






#endif // LevelSelector_h__