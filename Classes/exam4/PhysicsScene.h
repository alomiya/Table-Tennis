#ifndef __PHYSICS_SCENE_H__
#define __PHYSICS_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#define RATIO  48.0f

USING_NS_CC;
using namespace cocos2d;

class PhysicsScene : public Layer
{
public:
	PhysicsScene();
	~PhysicsScene();
	virtual bool init();
	CREATE_FUNC(PhysicsScene);
	static Scene* createScene();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onEnter();
	void addBall(float positionX, float positionY);

	void addNewSpriteAtPosition(Vec2 p); 
	b2World *world;
private:
	void initWorld();
	Size visibleSize;
};

#endif