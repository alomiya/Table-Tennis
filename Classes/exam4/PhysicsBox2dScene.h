#ifndef __PHYSICS_BOX2D_SCENE__
#define __PHYSICS_BOX2D_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BilliardSprite.h"
#include "GameContactListener.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d;

class PhysicsBox2dScene : public Layer
{
public:
	PhysicsBox2dScene();
	~PhysicsBox2dScene();

	virtual bool init();
	CREATE_FUNC(PhysicsBox2dScene);
	static Scene* createScene();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void update(float delta);

	void menuContinueCallback(Ref* pSender);
	
	// 初始化物理引擎
	void initPhysics();

	// 虚线
	void updateLine(Vec2 start_p, Vec2 end_p);

	// 更新力量进度条
	void updatePowerSlider(int power);

	// 切换坐标系 像素->米
	b2Vec2 changePos( Vec2 pos ); 

	// 切换坐标系 米->像素
	Vec2 changePos( b2Vec2 pos );

	//Score[0] is main ball score,Score[1-15] are 15 balls score
	int score[16] = {
		40,125,92,63,95,117,89,72,56,92,64,138,70,120,104,38
	};
	/*int score[16] = {
		0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2   //测试用
	};*/
	bool isballfall[17] = {
		false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false
	};

	//场上16个球以及两个记分板的label
	Label* scoreLabel[18];

	Sprite* round;      //用于提示当前回合方的精灵对象

	void drawGameResult(); 
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
private:
	b2World* _world;
	GameContactListener* _ContactListener;

	BilliardSprite* _mainBilliards; // 白球
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	float _sliderSpeed;

	float _angle;
	bool  _aim;
	bool  _canAim;
	Vec2  _aimPos;
	Vec2  _sheetPos;
	Rect  _aimRect;

	float _curPower;
	Rect  _powerRect;     
	bool  _powerEnd;
	bool  _mainBallFall;  //白球是否掉落
	int _hitNum_p1;  //player1击球数
	int _hitNum_p2;  //player2击球数
	int _fallNum_p1; //player1得球数
	int _fallNum_p2; //player2得球数
	bool _isResult; //是否播放结算界面
	int _ballNum ;  //桌上球数

	Vec2 _firstPoint;
	Vec2 _secondPoint;
	Vec2 _thirdPoint;
	float _q;
	float _force;
	bool _move;
};

#endif