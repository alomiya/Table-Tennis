// ��6������2 -- �ۺ϶�������

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "GameConfig.h"
#include "PhysicsBox2dScene.h"
#include "RuleScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"              //����cocos-ext.hͷ�ļ�
using namespace cocos2d::extension; //����cocos2d::extension�����ռ�
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