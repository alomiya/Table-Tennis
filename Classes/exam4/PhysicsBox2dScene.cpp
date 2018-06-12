#include "PhysicsBox2dScene.h"

PhysicsBox2dScene::PhysicsBox2dScene()
{
	_world = NULL;
	_aim = false;
	_angle = 0.0f;
	_curPower = 0.0f;
	_powerEnd = false;
	_sliderSpeed = 0.0f;
	_aimPos = Vec2(-1,-1);
	_canAim = true;
	_mainBallFall = false;
	_hitNum_p1 = 0;
	_hitNum_p2 = 0;
	_fallNum_p1 = 0;
	_fallNum_p2 = 0;
	_isResult = false;
	_ballNum = 15;
	_force = 0;
	_move = false;
}

PhysicsBox2dScene::~PhysicsBox2dScene()
{
	// delete World, ContactListener
	CC_SAFE_DELETE(_world);
	CC_SAFE_DELETE(_ContactListener);
}

bool PhysicsBox2dScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

Vec2 origin = Director::getInstance()->getVisibleOrigin();

//bg
auto bg = Sprite::create("exam4/aim/bg.png");
bg->setPosition(Vec2(visibleSize.width / 2 - 30, visibleSize.height / 2));
bg->setScale(0.9);
this->addChild(bg, 1);

// slider bg
auto slider_bg = Sprite::create("exam4/slider/bg-f.png");
slider_bg->setPosition(Vec2(visibleSize.width - 30, visibleSize.height / 2));
this->addChild(slider_bg, 2, SLIDER_BG_TAG);

// init power slider rect
_powerRect = Rect(visibleSize.width - 58, 0,
	58, visibleSize.height);
// slider
auto slider = Sprite::create("exam4/slider/fg-f.png");
this->addChild(slider, 3, SLIDER_TAG);
slider->setVisible(false);

// slider left
auto slider_left = Sprite::create("exam4/slider/bg-left.png");
slider_left->setPosition(Vec2(visibleSize.width - 60, visibleSize.height / 2));
this->addChild(slider_left, 2);

// boundary left
auto boundary_left = Sprite::create("exam4/slider/bg-left.png");
boundary_left->setPosition(Vec2(3, visibleSize.height / 2));
this->addChild(boundary_left);

// boundary right
auto boundary_right = Sprite::create("exam4/slider/bg-left.png");
boundary_right->setPosition(Vec2(visibleSize.width - 2, visibleSize.height / 2));
this->addChild(boundary_right, 2);

// init aim rect
_aimRect = Rect(40, 40, visibleSize.width - 140, visibleSize.height - 80);

// init physics world
this->initPhysics();

// 白球
_mainBilliards = new BilliardSprite("main", false, true, _world, "exam4/Ball/8.png", Vec2(200, visibleSize.height / 2), score[0]);
this->addChild(_mainBilliards, 10, MAIN_BILLIARDS_TAG);

for (int i = 0; i < 15; i++)
{
	auto ballSprite = new BilliardSprite(ballName[i], false, false, _world, ball[i], ballPos[i], score[i + 1]);
	this->addChild(ballSprite, 10);
}

// add touch listener
auto listener = EventListenerTouchOneByOne::create();
auto listenerMouse = EventListenerMouse::create();
auto listenerKeyBoard =EventListenerKeyboard::create();
listenerMouse->onMouseMove = [=](cocos2d::EventMouse* event) {
	if (_mainBallFall && event->getLocation().x < 320 - BALL_RADIO && event->getLocation().x > 40 + BALL_RADIO
		&& event->getLocation().y < 1240 - BALL_RADIO && event->getLocation().y > 680 + BALL_RADIO)
	{
		_mainBilliards->setb2Vec2Position(changePos(Vec2(event->getLocation().x, 1280 - event->getLocation().y)));
		_mainBilliards->setVisible(true);
	}
};

listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(PhysicsBox2dScene::onKeyPressed, this);
listenerKeyBoard->onKeyReleased= CC_CALLBACK_2(PhysicsBox2dScene::onKeyReleased, this);
listener->onTouchBegan = CC_CALLBACK_2(PhysicsBox2dScene::onTouchBegan, this);
listener->onTouchMoved = CC_CALLBACK_2(PhysicsBox2dScene::onTouchMoved, this);
listener->onTouchEnded = CC_CALLBACK_2(PhysicsBox2dScene::onTouchEnded, this);
listener->setSwallowTouches(true);
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse, this);
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
// main loop
this->scheduleUpdate();

// dash line
auto dashLine = Sprite::create("exam4/aim/dot_line.png");
this->addChild(dashLine, 2, DASH_LINE_TAG);
dashLine->setAnchorPoint(Vec2(0.5, 0));
dashLine->setVisible(false);

// aim icon
auto aim_icon = Sprite::create("exam4/aim/aim.png");
this->addChild(aim_icon, 10, AIM_ICON_TAG);
aim_icon->setScale(0.4f);
aim_icon->setVisible(false);

// 球杆
auto aim_gan = Sprite::create("exam4/aim/sheet-f.png");
this->addChild(aim_gan, 10, AIM_GAN_TAG);
aim_gan->setAnchorPoint(Vec2(0.5, 0));   //设置锚点
aim_gan->setScale(1.6f);
aim_gan->setVisible(false);


//每个球分数显示
for (b2Body* Cur = _world->GetBodyList(); Cur; Cur = Cur->GetNext())
{
	if (Cur->GetType() == b2_dynamicBody)
	{
		BilliardSprite* sprite = (BilliardSprite*)Cur->GetUserData();
		if (sprite&&sprite->isVisible())
		{
			char *name = sprite->getName();
			int sc = sprite->getScore();
			if (strcmp(name, "main") == 0)
			{
				scoreLabel[0] = Label::createWithBMFont("fonts/usual-for-num.fnt", StringUtils::format("%d", sc));
				scoreLabel[0]->setPosition(changePos(sprite->getPosition()));
				scoreLabel[0]->setScale(0.5);
				scoreLabel[0]->setTag(lableTag[0]);
				this->addChild(scoreLabel[0], 11);
			}
			else
			{
				for (int i = 0; i < 15; i++)
				{
					if (strcmp(name, ballName[i]) == 0)
					{
						scoreLabel[i+1] = Label::createWithBMFont("fonts/usual-for-num.fnt", StringUtils::format("%d", sc));
						scoreLabel[i+1]->setPosition(changePos(sprite->getPosition()));
						scoreLabel[i+1]->setScale(0.5);
						scoreLabel[i+1]->setTag(lableTag[i+1]);
						this->addChild(scoreLabel[i+1], 11);
					}
				}
			}
		}
	}
}
//玩家得分
scoreLabel[16] = Label::createWithBMFont("fonts/usual-for-num.fnt", StringUtils::format("%d", _ContactListener->Player1Score));
scoreLabel[16]->setPosition(Vec2(visibleSize.width-20,560));
scoreLabel[16]->setScale(0.5);
scoreLabel[16]->setTag(lableTag[16]);
this->addChild(scoreLabel[16], 11);

scoreLabel[17] = Label::createWithBMFont("fonts/usual-for-num.fnt", StringUtils::format("%d", _ContactListener->Player2Score));
scoreLabel[17]->setPosition(Vec2(visibleSize.width - 20, 80));
scoreLabel[17]->setScale(0.5);
scoreLabel[17]->setTag(lableTag[17]);
this->addChild(scoreLabel[17], 11);

//回合指示球
round = Sprite::create("exam4/Ball/8.png");
round->setPosition(Vec2(visibleSize.width - 45, 560));
round->setScale(0.35);
this->addChild(round, 11);

//玩家1头像
Sprite* hero1 = Sprite::create("exam4/aim/hero.png");
hero1->setScale(0.5);
hero1->setPosition(Vec2(visibleSize.width - 30, 610));
this->addChild(hero1, 11);

//玩家2头像
Sprite* hero2 = Sprite::create("exam4/aim/hero1.png");
hero2->setScale(0.5);
hero2->setPosition(Vec2(visibleSize.width - 30, 30));
this->addChild(hero2, 11);
	return true;


}

Scene* PhysicsBox2dScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PhysicsBox2dScene::create();
	scene->addChild(layer);

	return scene;
}

bool PhysicsBox2dScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!_isResult&&_mainBallFall&& touch->getLocation().x< 320 - BALL_RADIO && touch->getLocation().x > 40 + BALL_RADIO
		&& touch->getLocation().y > 40 + BALL_RADIO && touch->getLocation().y < 640 - BALL_RADIO)
	{
		_mainBilliards->setb2Vec2Position(changePos(touch->getLocation()));
		_mainBilliards->setVisible(true);
		_mainBallFall = false;
	}
	else {
		if (_aimRect.containsPoint(touch->getLocation()) && _canAim)
		{
			_aim = true;
			auto start_p = changePos(_mainBilliards->getPosition());
			auto end_p = touch->getLocation();
			updateLine(start_p, end_p);
		}
		_powerEnd = false;
	}
	return true;
}

void PhysicsBox2dScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (!_isResult && !_mainBallFall) {
		auto slider_bg = (Sprite*)getChildByTag(SLIDER_BG_TAG);
		auto start_p = changePos(_mainBilliards->getPosition());
		auto end_p = touch->getLocation();
		if (_aimRect.containsPoint(touch->getStartLocation()))//如果在球桌上拖动鼠标
		{
			if (_aim) {
				_curPower = end_p.getDistance(start_p);
				if (_curPower > 50) { //力度较大时在已定的角度动态更新力度条和杆的坐标
					if (_curPower < 0) {
						_curPower = 0;
					}
					else if (_curPower > slider_bg->getContentSize().height)
					{
						_curPower = slider_bg->getContentSize().height;
					}
					updatePowerSlider(_curPower);
				}
				else if (_aimRect.containsPoint(touch->getLocation()) && _canAim)  //力度较小时进行角度设置
				{
					updateLine(start_p, end_p);
				}
			}
		}
	}
}

void PhysicsBox2dScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!_isResult && !_mainBallFall) {
		/*if (_powerRect.containsPoint(touch->getLocation()) && _aim)
		{
			auto slider_bg = (Sprite*)getChildByTag(SLIDER_BG_TAG);
			_sliderSpeed = _curPower / slider_bg->getContentSize().height * 50.0f;

			// 击球
			auto start_p = changePos(_mainBilliards->getPosition());
			auto end_p = _aimPos;
			auto v = changePos((end_p - start_p).getNormalized());
			float q = _curPower / slider_bg->getContentSize().height;

			//更新玩家击球次数
			if (_ContactListener->isPlayer1Round)
				_hitNum_p1++;
			else
				_hitNum_p2++;

			// 设置白球速度
			_mainBilliards->SetLinearVelocity(b2Vec2(v.x * q * MAX_SPEED, v.y * q * MAX_SPEED));

			auto dash_line = (Sprite*)getChildByTag(DASH_LINE_TAG);
			dash_line->setVisible(false);
			auto aim_icon = (Sprite*)getChildByTag(AIM_ICON_TAG);
			aim_icon->setVisible(false);
			auto aim_gan = (Sprite*)getChildByTag(AIM_GAN_TAG);
			aim_gan->setVisible(false);

			// 击球运动后,在所有物体都静止之前无法再进行瞄准和击球
			_canAim = false;
			_aim = false;

			_powerEnd = true; // 进度条可以消除
			SimpleAudioEngine::sharedEngine()->playEffect("exam4/aim/hit.wav");
*/
		_thirdPoint = _aimPos;
		if (_aim)
		{
			auto slider_bg = (Sprite*)getChildByTag(SLIDER_BG_TAG);
			_sliderSpeed = _curPower / slider_bg->getContentSize().height * 50.0f;
			// 击球
			_firstPoint = changePos(_mainBilliards->getPosition()); 
			b2Vec2 v;
			// 如果_force=0 即并未按下 Z 键，此时认为仍单一方向移动，只有两个点,firsrpoint 与
			//thirdpoint，对应于源码中的 startpoint 与 endpoint，如果 force != 0, 则认为曲线运动，此时 3 个
				//点，分别为 first, second, third
			if (_force) {
				v = changePos((_secondPoint - _firstPoint).getNormalized());
			}
			else {
				v = changePos((_thirdPoint - _firstPoint).getNormalized());
			}

			_mainBilliards->SetLinearVelocity(b2Vec2(v.x * _q * MAX_SPEED, v.y * _q *MAX_SPEED));
			_q = _curPower / slider_bg->getContentSize().height;

			//更新玩家击球次数
			if (_ContactListener->isPlayer1Round)
				_hitNum_p1++;
			else
				_hitNum_p2++;

			// 设置白球速度
			if (_force) {
				_move = true;
			}
			CCLOG("_move to true");
			auto dash_line = (Sprite*)getChildByTag(DASH_LINE_TAG);
			dash_line->setVisible(false);
			auto aim_icon = (Sprite*)getChildByTag(AIM_ICON_TAG);
			aim_icon->setVisible(false);
			auto aim_gan = (Sprite*)getChildByTag(AIM_GAN_TAG);
			aim_gan->setVisible(false);
			// 击球运动后,在所有物体都静止之前无法再进行瞄准和击球
			_canAim = false;
			_aim = false;
			_powerEnd = true; // 进度条可以消除
			SimpleAudioEngine::sharedEngine()->playEffect("exam4/aim/hit.wav");
		}
	}
}

void PhysicsBox2dScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// 如果按下 Z 键
	if (keyCode == EventKeyboard::KeyCode::KEY_Z) {
		auto slider_bg = (Sprite*)getChildByTag(SLIDER_BG_TAG);
		_q = _curPower / slider_bg->getContentSize().height;
		_secondPoint = _aimPos;
		_firstPoint = changePos(_mainBilliards->getPosition());
		_force = 60;
	}
}
void PhysicsBox2dScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
}

//绘制gameresult
void PhysicsBox2dScene::drawGameResult()
{
	//继续按钮
	auto conItem = MenuItemImage::create(
		"exam4/aim/continue.png",
		"exam4/aim/continue.png",
		CC_CALLBACK_1(PhysicsBox2dScene::menuContinueCallback, this));
	conItem->setPosition(Vec2(visibleSize.width/2+300,130));
	conItem->setScale(0.8);
	auto menu = Menu::create(conItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 14);

	//player1\player2文字
	auto labelplayer1 = Label::createWithBMFont("fonts/usual.fnt", "Player1");
	labelplayer1->setPosition(Vec2(visibleSize.width / 2 - 350, 500));
	this->addChild(labelplayer1, 14);

	auto labelplayer2 = Label::createWithBMFont("fonts/usual.fnt", "Player2");
	labelplayer2->setPosition(Vec2(visibleSize.width / 2 + 300, 500));
	this->addChild(labelplayer2, 14);

	//各个数据对应的名字
	Dictionary* strings = Dictionary::createWithContentsOfFile("fonts/my.xml");
	const char *score_text = ((String*)strings->objectForKey("score"))->getCString();
	const char *hit_text = ((String*)strings->objectForKey("hit"))->getCString();
	const char *fall_text = ((String*)strings->objectForKey("fall"))->getCString();

	auto tips_score_1 = Label::createWithBMFont("fonts/usual.fnt", score_text);
	tips_score_1->setPosition(Vec2(visibleSize.width / 2 - 380, visibleSize.height - 200));
	tips_score_1->setScale(0.6);
	this->addChild(tips_score_1, 14);

	auto tips_hit_1 = Label::createWithBMFont("fonts/usual.fnt", hit_text);
	tips_hit_1->setPosition(Vec2(visibleSize.width / 2 - 380, visibleSize.height - 300));
	tips_hit_1->setScale(0.6);
	this->addChild(tips_hit_1, 14);

	auto tips_fall_1 = Label::createWithBMFont("fonts/usual.fnt", fall_text);
	tips_fall_1->setPosition(Vec2(visibleSize.width / 2 - 380, visibleSize.height - 400));
	tips_fall_1->setScale(0.6);
	this->addChild(tips_fall_1, 14);


	auto tips_score_2 = Label::createWithBMFont("fonts/usual.fnt", score_text);
	tips_score_2->setPosition(Vec2(visibleSize.width / 2 + 330, visibleSize.height - 200));
	tips_score_2->setScale(0.6);
	this->addChild(tips_score_2, 14);

	auto tips_hit_2 = Label::createWithBMFont("fonts/usual.fnt", hit_text);
	tips_hit_2->setPosition(Vec2(visibleSize.width / 2 + 330, visibleSize.height - 300));
	tips_hit_2->setScale(0.6);
	this->addChild(tips_hit_2, 14);

	auto tips_fall_2 = Label::createWithBMFont("fonts/usual.fnt", fall_text);
	tips_fall_2->setPosition(Vec2(visibleSize.width / 2 + 330, visibleSize.height - 400));
	tips_fall_2->setScale(0.6);
	this->addChild(tips_fall_2, 14);

	//计算入球率
	float fallrate_p1 = (_hitNum_p1 > 0) ? 1.0*_fallNum_p1 / _hitNum_p1: 0;
	float fallrate_p2 = (_hitNum_p2 > 0) ? 1.0*_fallNum_p2 / _hitNum_p2 : 0;
	
	//显示数据
	auto tips_score_p1 = Label::createWithBMFont("fonts/usual.fnt", StringUtils::format("%d", _ContactListener->Player1Score));
	tips_score_p1->setWidth(150);
	tips_score_p1->setAlignment(cocos2d::TextHAlignment::RIGHT);
	tips_score_p1->setPosition(Vec2(visibleSize.width /3, visibleSize.height - 230));
	tips_score_p1->setScale(0.8);
	this->addChild(tips_score_p1, 14);

	auto tips_hit_p1 = Label::createWithBMFont("fonts/usual.fnt", StringUtils::format("%d",_hitNum_p1));
	tips_hit_p1->setWidth(150);
	tips_hit_p1->setAlignment(cocos2d::TextHAlignment::RIGHT);
	tips_hit_p1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height - 330));
	tips_hit_p1->setScale(0.8);
	this->addChild(tips_hit_p1, 14);
	auto tips_fall_p1 = Label::createWithBMFont("fonts/usual.fnt", StringUtils::format("%.2f%%", fallrate_p1 * 100));
	tips_fall_p1->setWidth(150);
	tips_fall_p1->setAlignment(cocos2d::TextHAlignment::RIGHT);
	tips_fall_p1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height - 430));
	tips_fall_p1->setScale(0.8);
	this->addChild(tips_fall_p1, 14);


	auto tips_score_p2 = Label::createWithBMFont("fonts/usual.fnt", StringUtils::format("%d", _ContactListener->Player2Score));
	tips_score_p2->setWidth(150);
	tips_score_p2->setAlignment(cocos2d::TextHAlignment::LEFT);
	tips_score_p2->setPosition(Vec2(visibleSize.width * 3 / 5, visibleSize.height - 230));
	tips_score_p2->setScale(0.8);
	this->addChild(tips_score_p2, 14);

	auto tips_hit_p2 = Label::createWithBMFont("fonts/usual.fnt", StringUtils::format("%d", _hitNum_p2));
	tips_hit_p2->setWidth(150);
	tips_hit_p2->setAlignment(cocos2d::TextHAlignment::LEFT);
	tips_hit_p2->setPosition(Vec2(visibleSize.width * 3 / 5, visibleSize.height - 330));
	tips_hit_p2->setScale(0.8);
	this->addChild(tips_hit_p2, 14);

	auto tips_fall_p2 = Label::createWithBMFont("fonts/usual.fnt", StringUtils::format("%.2f%%", fallrate_p2 * 100.0));
	tips_fall_p2->setWidth(150);
	tips_fall_p2->setAlignment(cocos2d::TextHAlignment::LEFT);
	tips_fall_p2->setPosition(Vec2(visibleSize.width * 3 / 5, visibleSize.height - 430));
	tips_fall_p2->setScale(0.8);
	this->addChild(tips_fall_p2, 14);

	//判断胜负
	auto sprite_win = Sprite::create("exam4/aim/win.png");
	auto sprite_lose = Sprite::create("exam4/aim/lose.png");
	sprite_win->setScale(0.4);
	sprite_lose->setScale(0.4);
	if (_ContactListener->Player1Score > _ContactListener->Player2Score)
	{
		sprite_win->setPosition(Vec2(visibleSize.width/ 2 - 95,500));
		sprite_lose->setPosition(Vec2(visibleSize.width/2 + 45, 500));
	}
	else if(_ContactListener->Player1Score < _ContactListener->Player2Score)
	{
		sprite_lose->setPosition(Vec2(visibleSize.width/2 -105,500));
		sprite_win->setPosition(Vec2(visibleSize.width/2 +35, 500));
	}
	else
	{
		if (_ContactListener->isPlayer1Round)  //谁最先达到该分数谁赢
		{
			sprite_lose->setPosition(Vec2(visibleSize.width / 2-105,500));
			sprite_win->setPosition(Vec2(visibleSize.width /2+35, 500));
		}
		else
		{
			sprite_win->setPosition(Vec2(visibleSize.width /2 -95, 500));
			sprite_lose->setPosition(Vec2(visibleSize.width /2+45, 500));
		}
	}
	this->addChild(sprite_win, 14);
	this->addChild(sprite_lose, 14);

	//背景
	auto sprite = Sprite::create("exam4/aim/popupbg.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 - 30, visibleSize.height / 2));
	this->addChild(sprite, 13);
}

void PhysicsBox2dScene::update(float delta)
{
	float timeStep = 1.0f / 60.0f; // 时间同步
	int32 velocityIterations = 8; // 速度迭代次数
	int32 positionIterations = 1; // 位置迭代次数
	// 如果按下Z键，force不为0，则增加曲线运动，具体为secondpoint与thirdpoint，利用ApplyForce方法，进行曲线运动，
		if (_force) {
			if (_move)
			{
				auto v2 = changePos((_thirdPoint - _secondPoint).getNormalized());
				CCLOG("v2: %f %f", v2.x, v2.y);
				_mainBilliards->ApplyForceToCenter(b2Vec2(v2.x * _q * MAX_SPEED * 10, v2.y * _q * MAX_SPEED * 10), _mainBilliards->GetWorldCenter(),true);
				_force--;
				if (_force == 0) {
					_move = false;
				}
			}
		}
	_world->Step(timeStep,velocityIterations,positionIterations);

	_ContactListener->deleteBody(); // 循环判定游戏输赢

	scoreLabel[16]->setString(StringUtils::format("%d", _ContactListener->Player1Score));
	scoreLabel[17]->setString(StringUtils::format("%d", _ContactListener->Player2Score));
	
	for (b2Body* Cur = _world->GetBodyList(); Cur; Cur = Cur->GetNext())
	{
		if (Cur->GetType() == b2_dynamicBody)
		{
			BilliardSprite* sprite = (BilliardSprite*)Cur->GetUserData();
			if (sprite)
			{
				char *name = sprite->getName();
				int sc = sprite->getScore();
				if (strcmp(name, "main") == 0)
				{
					if (!sprite->isVisible() && scoreLabel[0]->isVisible())
					{
						scoreLabel[0]->setVisible(false);
					}
					else if(sprite->isVisible())
					{
						scoreLabel[0]->setPosition(changePos(sprite->getPosition()));
						scoreLabel[0]->setString(StringUtils::format("%d", sc));
						scoreLabel[0]->setVisible(true);
					}
				}
				else
				{
					for (int i = 0; i < 15; i++)
					{
						if (strcmp(name, ballName[i]) == 0)
						{
							if (!sprite->isVisible() && scoreLabel[i + 1]->isVisible())
							{
								scoreLabel[i + 1]->setVisible(false);
							}
							else if (sprite->isVisible())
							{
								scoreLabel[i + 1]->setPosition(changePos(sprite->getPosition()));
								scoreLabel[i + 1]->setString(StringUtils::format("%d", sc));
								scoreLabel[i + 1]->setVisible(true);
							}
						}
					}
				}
			}
		}
	}
	for (b2Body* Cur = _world->GetBodyList(); Cur; Cur = Cur->GetNext() )
	{
		if ( Cur->GetType() == b2_dynamicBody && Cur->IsAwake() == true )
		{
			// 模拟阻力
			Cur->SetLinearVelocity(b2Vec2(Cur->GetLinearVelocity().x * 0.989, Cur->GetLinearVelocity().y * 0.989));
			if( abs(Cur->GetLinearVelocity().x) < 0.5f && abs(Cur->GetLinearVelocity().y) < 0.5f )
			{
				Cur->SetAwake(false);
			}
		}
	}

	if (_powerEnd)
	{
		// 滑块消失
		//if (_curPower !=0)  //力度会在释放之后会减到负数
		if (_curPower > 0) 
		{
			_curPower -= _sliderSpeed;
		} else if (_curPower <= 0)
		{
			_curPower = 0.0f;
		}
		updatePowerSlider(_curPower);
	}

	// 所有球静止才可以进行瞄准
	int awak = 0;
	for (b2Body* Cur = _world->GetBodyList(); Cur; Cur = Cur->GetNext() )
	{
		//如果是球且进洞则将其视为不可见
		if ( Cur->GetType() == b2_dynamicBody)
		{
			if(Cur->IsAwake())
				awak++;
			BilliardSprite* sprite = (BilliardSprite*)Cur->GetUserData();
			
			if (sprite)
			{
				char *name = sprite->getName();
				if (!strcmp(name, "main") == 0)  //分数小于等于0的球移除界面外
				{
					if (sprite->getScore() <= 0 && sprite->isVisible())
					{
						Cur->SetTransform(changePos(Vec2(-100, -100)),Cur->GetAngle());
						sprite->setVisible(false);
						_ballNum--;
						if (_ContactListener->isPlayer1Round)
							_fallNum_p1++;
						else
							_fallNum_p2++;
						sprite->setScore(1);        //移除出界面外的球不影响玩家分数，将其分数设置大于0，避免再次执行该球
					}
				}
				if ( Cur->GetPosition().x < 40.0 / PTM_RATIO || Cur->GetPosition().x >(visibleSize.width - 96.0) / PTM_RATIO
					|| Cur->GetPosition().y < 40.0 / PTM_RATIO || Cur->GetPosition().y >(visibleSize.height - 40.0) / PTM_RATIO
					|| (Cur->GetPosition().y < 60.0 / PTM_RATIO || Cur->GetPosition().y >(visibleSize.height - 60.0) / PTM_RATIO)
					&& Cur->GetPosition().x >((visibleSize.width / 2 -66) / PTM_RATIO)
					&& Cur->GetPosition().x <((visibleSize.width /2 + 4) / PTM_RATIO))
				{
					if (_canAim == false)  // 有球落网
					{
						if (!_mainBallFall&&strcmp(name, "main") == 0&&!isballfall[0] && sprite->isVisible())
						{
							isballfall[0] = true;
							sprite->setVisible(false);
							Cur->SetAwake(false);
							SimpleAudioEngine::sharedEngine()->playEffect("exam4/aim/fall.wav");
						}
						else
						{
							for (int i = 0; i < 15; i++)
							{
								if (strcmp(sprite->getName(), ballName[i]) == 0&& !isballfall[i + 1]&& sprite->isVisible())
								{
									
									isballfall[i + 1] = true;
									if(i!=10)
										isballfall[16] = true;
									sprite->setVisible(false);
									Cur->SetTransform(changePos(Vec2(-100, -100)), Cur->GetAngle());
									Cur->SetAwake(false);
									SimpleAudioEngine::sharedEngine()->playEffect("exam4/aim/fall.wav");
								}
							}
						}
					}
				}
			}
		}
	}
	if (_ballNum == 0 && awak == 0)//游戏结束
	{
		_isResult = true;
		drawGameResult();
	}
	//所有球均已静止
	if (awak == 0)
	{
		//白球入袋
		if (isballfall[0] && !_mainBilliards->isVisible())
		{
			_mainBallFall = true;
			isballfall[0] = false;
			if (_ContactListener->isPlayer1Round)
				_ContactListener->Player1Score -= _mainBilliards->getScore();
			else
				_ContactListener->Player2Score -= _mainBilliards->getScore();
			_mainBilliards->setScore(0);  //重置白球分数
		}
		else
		{
			for (b2Body* Cur = _world->GetBodyList(); Cur; Cur = Cur->GetNext())
			{
				if (Cur->GetType() == b2_dynamicBody)
				{
					BilliardSprite* sprite = (BilliardSprite*)Cur->GetUserData();
					if (sprite)
					{
						//黑球落网
						if (strcmp(sprite->getName(), ballName[10]) == 0 && isballfall[11] && !sprite->isVisible()) 
						{
							isballfall[11] = false;
							_ballNum--;
							if (_ballNum > 1)  //rounder is punished
							{
								if (_ContactListener->isPlayer1Round)
								{
									_ContactListener->Player1Score -= sprite->getScore();
									_fallNum_p1++;
								}
								else
								{
									_ContactListener->Player2Score -= sprite->getScore();
									_fallNum_p2++;
								}
							}
							else   //rounder get the combo
							{
								if (_ContactListener->isPlayer1Round)
								{
									_ContactListener->Player1Score += sprite->getScore();
									_fallNum_p1++;
								}
								else
								{
									_ContactListener->Player2Score += sprite->getScore();
									_fallNum_p2++;
								}
							}
							sprite->setScore(score[11]);        //移除出界面外的球不影响玩家分数，将其分数设置大于0，避免再次执行该球
						}
						else
						{
							for (int i = 0; i < 15; i++)
							{
								if (strcmp(sprite->getName(), ballName[i]) == 0 && isballfall[i + 1] && !sprite->isVisible())   //非黑球和白球落网
								{
									isballfall[i + 1] = false;
									_ballNum--;
									if (_ContactListener->isPlayer1Round)
									{
										_ContactListener->Player1Score += sprite->getScore();
										_fallNum_p1++;
									}
									else
									{
										_ContactListener->Player2Score += sprite->getScore();
										_fallNum_p2++;
									}
									sprite->setScore(score[i + 1]);        //移除出界面外的球不影响玩家分数，将其分数设置大于0，避免再次执行该球

								}
							}
						}
					}
				}
			}
		}
		if (!_canAim&&!isballfall[16])//没有彩球入网
		{
			_ContactListener->isPlayer1Round = !_ContactListener->isPlayer1Round;
			//更新提示球坐标
			if(_ContactListener->isPlayer1Round)
				round->setPosition(Vec2(visibleSize.width - 45, 560));
			else
				round->setPosition(Vec2(visibleSize.width - 45, 80));
			//显示各球数字
		}
		else if(!_canAim)
		{
			isballfall[16] = false;
		}
		_canAim = true;
	}
}

void PhysicsBox2dScene::initPhysics()
{
	_ContactListener = new GameContactListener();

	// gravity
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);

	// create world
	_world = new b2World(gravity);

	_world->SetContactListener(_ContactListener); // 碰撞

	// allow sleep
	_world->SetAllowSleeping(true);

	// physics test 避免碰撞检测不连续产生碰撞穿透
	_world->SetContinuousPhysics(true);

	// ground
	b2BodyDef groundBodyDef;

	// left down
	groundBodyDef.position.Set(0, 0);

	// create ground
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
	groundBody->SetUserData("boundary");

	// shape
	b2EdgeShape groundBox;

	float ydown = 40.0;
	float yup = visibleSize.height-40.0;
	float ymiddown = 76.0;
	float ymidup = visibleSize.height - 76.0;
	// left
	groundBox.Set(b2Vec2(changePos(Vec2(40, ymiddown))), b2Vec2(changePos(Vec2(40, ymidup))));
	groundBody->CreateFixture(&groundBox, 0);

	// right
	groundBox.Set(b2Vec2(changePos(Vec2(visibleSize.width - 96, ymiddown))), b2Vec2(changePos(Vec2(visibleSize.width - 96, ymidup))));
	groundBody->CreateFixture(&groundBox, 0);

	// downleft
	groundBox.Set(b2Vec2(changePos(Vec2( 76, ydown)) ),b2Vec2(changePos(Vec2(visibleSize.width/2-76, ydown))));
	groundBody->CreateFixture(&groundBox,0);

	// downright
	groundBox.Set(b2Vec2(changePos(Vec2(visibleSize.width / 2 +10 , ydown))), b2Vec2(changePos(Vec2(visibleSize.width -132, ydown))));
	groundBody->CreateFixture(&groundBox, 0);

	// upleft
	groundBox.Set(b2Vec2(changePos(Vec2(76, yup))), b2Vec2(changePos(Vec2(visibleSize.width / 2 - 76, yup))));
	groundBody->CreateFixture(&groundBox, 0);

	// upright
	groundBox.Set(b2Vec2(changePos(Vec2(visibleSize.width / 2 + 10, yup))), b2Vec2(changePos(Vec2(visibleSize.width - 132, yup))));
	groundBody->CreateFixture(&groundBox, 0);
}

b2Vec2 PhysicsBox2dScene::changePos(Vec2 pos)
{
	return b2Vec2(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
}

cocos2d::Vec2 PhysicsBox2dScene::changePos(b2Vec2 pos)
{
	return Vec2(pos.x*PTM_RATIO, pos.y*PTM_RATIO);
}

void PhysicsBox2dScene::updatePowerSlider(int power)
{
	//更新力度条
	auto slider = (Sprite*)getChildByTag(SLIDER_TAG);
	auto slider_bg = (Sprite*)getChildByTag(SLIDER_BG_TAG);
	slider->setPosition(Vec2(visibleSize.width - 30, visibleSize.height/2 + slider_bg->getContentSize().height/2 - power / 2));
	slider->setTextureRect(Rect(0, 0, slider_bg->getContentSize().width, power));
	slider->setVisible(true);
	//更新球杆
	auto sheet = (Sprite*)getChildByTag(AIM_GAN_TAG);
	sheet->setPosition(_sheetPos.x - power*cos(_angle)/2,_sheetPos.y - power*sin(_angle)/2);
	//更新aimPos
	_aimPos = changePos(_mainBilliards->getPosition()) + Vec2(power*cos(_angle)*2, power*sin(_angle)*2);
	if (_aimPos.y > 600)_aimPos= Vec2(_aimPos.x-(_aimPos.y - 600)/ sin(_angle)*cos(_angle),600);
	if (_aimPos.y < 40) _aimPos = Vec2(_aimPos.x + (40-_aimPos.y) / sin(_angle)*cos(_angle),40);
	if (_aimPos.x > visibleSize.width - 96) _aimPos = Vec2(visibleSize.width - 96,_aimPos.y - (_aimPos.x- visibleSize.width + 96) / cos(_angle)*sin(_angle));
	if (_aimPos.x < 40)_aimPos= Vec2(40,_aimPos.y + (40 - _aimPos.x) / cos(_angle)*sin(_angle));
	auto aim_icon = (Sprite*)getChildByTag(AIM_ICON_TAG);
	aim_icon->setPosition(_aimPos);
	//动态更新提示线
	auto dashLine = (Sprite*)getChildByTag(DASH_LINE_TAG);
	dashLine->setPosition(changePos(_mainBilliards->getPosition()));
	dashLine->setTextureRect(Rect(0, 0, 2 * BALL_SCALE, BALL_SCALE*abs((_aimPos - changePos(_mainBilliards->getPosition())).getLength())));
	dashLine->setRotation(CC_RADIANS_TO_DEGREES(-_angle) + 90.0f);
	//根据力量有无设置显示
	if (power <= 0)
	{
		sheet->setVisible(false);
		aim_icon->setVisible(false);
		dashLine->setVisible(false);
	}
	else {
		aim_icon->setVisible(true);
		sheet->setVisible(true);
		dashLine->setVisible(true);
	}
}

void PhysicsBox2dScene::updateLine(Vec2 start_p, Vec2 end_p)
{
	// update line
	_angle = (start_p-end_p).getNormalized().getAngle() ;
	_aimPos = start_p+Vec2(cos(_angle)*100,sin(_angle)*100);
	if (_aimPos.y > 600)_aimPos = Vec2(_aimPos.x - (_aimPos.y - 600) / sin(_angle)*cos(_angle), 600);
	if (_aimPos.y < 40) _aimPos = Vec2(_aimPos.x + (40 - _aimPos.y) / sin(_angle)*cos(_angle), 40);
	if (_aimPos.x > visibleSize.width - 96) _aimPos = Vec2(visibleSize.width - 96, _aimPos.y - (_aimPos.x - visibleSize.width + 96) / cos(_angle)*sin(_angle));
	if (_aimPos.x < 40)_aimPos = Vec2(40, _aimPos.y + (40 - _aimPos.x) / cos(_angle)*sin(_angle));
	auto dashLine = (Sprite*)getChildByTag(DASH_LINE_TAG);
	dashLine->setPosition(start_p);
	dashLine->setTextureRect(Rect(0,0,2 * BALL_SCALE, BALL_SCALE*abs((_aimPos - start_p).getLength())));
	dashLine->setRotation(CC_RADIANS_TO_DEGREES(-_angle) + 90.0f);
	dashLine->setVisible(true);

	// update aim icon
	auto aim_icon = (Sprite*)getChildByTag(AIM_ICON_TAG);
	aim_icon->setPosition(_aimPos);
	aim_icon->setVisible(true);

	// 计算球杆位置
	_sheetPos = start_p -Vec2(BALL_RADIO * 1.5 * cos(_angle), BALL_RADIO * 1.5 * sin(_angle));
	auto aim_gan = (Sprite*)getChildByTag(AIM_GAN_TAG);
	aim_gan->setPosition(_sheetPos);
	aim_gan->setRotation(CC_RADIANS_TO_DEGREES(-_angle) - 90.0f);
	aim_gan->setVisible(true);
}


void PhysicsBox2dScene::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, MenuScene::createScene()));
}
