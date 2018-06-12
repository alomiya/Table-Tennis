#include "RuleScene.h"
RuleScene::RuleScene()
{
	
}

RuleScene::~RuleScene()
{

}

bool RuleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//将rulewordbg作为背景图
	auto background = Sprite::create("exam4/aim/rulewordbg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);
	/*
	// 背景
	auto background = Sprite::create("exam4/aim/rulebg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(0.9);
	background->setTag(110);
	this->addChild(background);


	//通过xml获得规则
	Dictionary* strings = Dictionary::createWithContentsOfFile("fonts/my.xml");
	const char *rule1_text = ((String*)strings->objectForKey("rule1"))->getCString();
	const char *rule2_text = ((String*)strings->objectForKey("rule2"))->getCString();
	const char *rule3_text = ((String*)strings->objectForKey("rule3"))->getCString();
	const char *rule4_text = ((String*)strings->objectForKey("rule4"))->getCString();
	const char *rule5_text = ((String*)strings->objectForKey("rule5"))->getCString();
	const char *rule6_text = ((String*)strings->objectForKey("rule6"))->getCString();


	auto tips_rule_1 = Label::createWithBMFont("fonts/usual-for-rule.fnt", rule1_text);
	tips_rule_1->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 230));
	tips_rule_1->setScale(0.8);
	this->addChild(tips_rule_1, 14);

	auto tips_rule_2 = Label::createWithBMFont("fonts/usual-for-rule.fnt", rule2_text);
	tips_rule_2->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 280));
	tips_rule_2->setScale(0.8);
	this->addChild(tips_rule_2, 14);

	auto tips_rule_3 = Label::createWithBMFont("fonts/usual-for-rule.fnt", rule3_text);
	tips_rule_3->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 330));
	tips_rule_3->setScale(0.8);
	this->addChild(tips_rule_3, 14);


	auto  tips_rule_4 = Label::createWithBMFont("fonts/usual-for-rule.fnt", rule4_text);
	tips_rule_4->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 380));
	tips_rule_4->setScale(0.8);
	this->addChild(tips_rule_4, 14);

	auto  tips_rule_5 = Label::createWithBMFont("fonts/usual-for-rule.fnt", rule5_text);
	tips_rule_5->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 430));
	tips_rule_5->setScale(0.8);
	this->addChild(tips_rule_5, 14);

	auto  tips_rule_6 = Label::createWithBMFont("fonts/usual-for-rule.fnt", rule6_text);
	tips_rule_6->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 480));
	tips_rule_6->setScale(0.8);
	this->addChild(tips_rule_6, 14);
	*/
	
	// 继续按钮
	auto conItem = MenuItemImage::create(
		"exam4/aim/continue.png",
		"exam4/aim/continue.png",
		CC_CALLBACK_1(RuleScene::continueCallback, this));

	conItem->setPosition(Vec2(visibleSize.width /2, 90));
	conItem->setScale(0.7);
	auto menu2 = Menu::create(conItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 5);
	
	// update
	this->scheduleUpdate();

	return true;
}

Scene* RuleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RuleScene::create();
	scene->addChild(layer);
	return scene;
}

void RuleScene::update(float delta)
{
}

void RuleScene::continueCallback(Ref* pSender)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->pushScene(scene);
}
