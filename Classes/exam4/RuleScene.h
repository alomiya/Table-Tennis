// 第6章例子2 -- 综合动画例子

#ifndef __RULE_SCENE_H__
#define __RULE_SCENE_H__

#include "GameConfig.h"
#include "MenuScene.h"
#include "cocos-ext.h"              //包含cocos-ext.h头文件
using namespace cocos2d::extension; //引用cocos2d::extension命名空间
USING_NS_CC;

class RuleScene : public Layer
{
public:
	RuleScene();
	~RuleScene();
	virtual bool init();
	CREATE_FUNC(RuleScene);
	static Scene* createScene();

	void update(float delta);

	void continueCallback(Ref* pSender);
private:

};

#endif