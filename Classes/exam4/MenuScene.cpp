#include "MenuScene.h"
MenuScene::MenuScene()
{
	
}

MenuScene::~MenuScene()
{

}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 背景
	auto background = Sprite::create("exam4/aim/menubg.jpg");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(0.5);
	background->setTag(110);
	this->addChild(background);

	// 开始按钮
	auto startItem = MenuItemImage::create(
		"exam4/aim/start.png",
		"exam4/aim/start.png",
		CC_CALLBACK_1(MenuScene::startCallback, this));

	startItem->setPosition(Vec2(visibleSize.width /2, 280));
	startItem->setScale(0.8);
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5);

	// 规则按钮
	auto ruleItem = MenuItemImage::create(
		"exam4/aim/rule.png",
		"exam4/aim/rule.png",
		CC_CALLBACK_1(MenuScene::ruleCallback, this));

	ruleItem->setPosition(Vec2(visibleSize.width /2, 220));
	ruleItem->setScale(0.8);
	auto menu1 = Menu::create(ruleItem, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 5);

	// 退出按钮
	auto quitItem = MenuItemImage::create(
		"exam4/aim/quit.png",
		"exam4/aim/quit.png",
		CC_CALLBACK_1(MenuScene::quitCallback, this));

	quitItem->setPosition(Vec2(visibleSize.width /2, 160));
	quitItem->setScale(0.8);
	auto menu2 = Menu::create(quitItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 5);

	//音效加载
	SimpleAudioEngine::sharedEngine()->preloadEffect("exam4/aim/hit.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("exam4/aim/fall.wav");
	// update
	this->scheduleUpdate();

	return true;
}

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

void MenuScene::update(float delta)
{

}


void MenuScene::startCallback(Ref* pSender)
{
	auto scene = PhysicsBox2dScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MenuScene::ruleCallback(Ref* pSender)
{
	auto scene = RuleScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MenuScene::quitCallback(Ref* pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}