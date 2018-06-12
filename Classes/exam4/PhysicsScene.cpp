#include "PhysicsScene.h"

PhysicsScene::PhysicsScene()
{

}

PhysicsScene::~PhysicsScene()
{

}

bool PhysicsScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// physics scene
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 定义世界的物理边界
	auto body = PhysicsBody::createEdgeBox(visibleSize,
		PHYSICSBODY_MATERIAL_DEFAULT,5.0f);                     
	auto edgeNode = Node::create();                                         
	edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));               
	edgeNode->setPhysicsBody(body);                                     
	this->addChild(edgeNode);                                           

	// 屏幕触摸(点击事件)
	auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(PhysicsScene::onTouchBegan, this); 
	/*listener->onTouchBegan = [this](Touch *touch, Event *unused_event)    //点击生成球
	{
		addNewSpriteAtPosition(touch->getLocation());//getlocation返回vec2
		return false;
	};*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void PhysicsScene::initWorld()
{
	world = new b2World(b2Vec2(0, -10));
}

Scene* PhysicsScene::createScene()
{
	// 创建物理世界
	auto scene = Scene::createWithPhysics();

	// 绘制调试遮罩
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = PhysicsScene::create();
	scene->addChild(layer);
	return scene;
}

void PhysicsScene::onEnter()
{
	Layer::onEnter();
	addBall(visibleSize.width / 2, visibleSize.height / 2);
}

bool PhysicsScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	Vec2 location = touch->getLocation();
	addNewSpriteAtPosition(location);
	return false;
}

void PhysicsScene::addBall(float positionX, float positionY)
{
	auto b = Sprite::create("exam4/Ball/1.png");
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(visibleSize.width /2/RATIO, 9);
	b2Body *birdBody = world->CreateBody(&bodyDef);
	//b->setptm
	b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
	b->setPosition(positionX, positionY);
	this->addChild(b);
}

void PhysicsScene::addNewSpriteAtPosition(Vec2 p)
{
	int picpath = rand() % 11;
	auto sp = Sprite::create(StringUtils::format("exam4/Ball/%d.png",picpath)); 
	sp->setTag(1);

	auto body = PhysicsBody::createCircle(sp->getContentSize().width / 2);
	// auto body = PhysicsBody::createBox(sp->getContentSize());                      
	sp->setPhysicsBody(body);
	//sp->setPosition(p.x,p.y);
	sp->setPosition(p);
	this->addChild(sp);
}

