// ��6������2 -- �ۺ϶�������

#ifndef __RULE_SCENE_H__
#define __RULE_SCENE_H__

#include "GameConfig.h"
#include "MenuScene.h"
#include "cocos-ext.h"              //����cocos-ext.hͷ�ļ�
using namespace cocos2d::extension; //����cocos2d::extension�����ռ�
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