#ifndef __TESTLAYER_H__
#define __TESTLAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class TestLayer: public Node
{
public:
	TestLayer();
	~TestLayer();

	static Scene* createScene();

	bool init();

	CREATE_FUNC(TestLayer);
};

#endif