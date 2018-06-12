// 第6章例子2 -- 综合动画例子

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "GameConfig.h"
#include "PhysicsBox2dScene.h"
#include "RuleScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"              //包含cocos-ext.h头文件
using namespace cocos2d::extension; //引用cocos2d::extension命名空间
USING_NS_CC;
using namespace CocosDenshion;

class MenuScene : public Layer
{
public:
	MenuScene();
	~MenuScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);
	static Scene* createScene();

	void update(float delta);

	void startCallback(Ref* pSender);
	void ruleCallback(Ref* pSender);
	void quitCallback(Ref* pSender);
private:

};

#endif