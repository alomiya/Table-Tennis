#include "BilliardSprite.h"

BilliardSprite::BilliardSprite(const char* name, bool isStatic, bool isBullet,
	b2World* world, std::string picPath, Vec2 position, int score)
{
	_name = const_cast<char*>(name);
	_isStatic = isStatic;
	_isBullet = isBullet;
	_world = world;
	_picPath = picPath;
	_position = position;
	_score = score;
	init();
}

void BilliardSprite::update(float t)
{
	_sprite->setPosition(Vec2(
		_body->GetPosition().x * PTM_RATIO,
		_body->GetPosition().y * PTM_RATIO));
	_sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(_body->GetAngle()));
}

BilliardSprite::~BilliardSprite()
{

}


bool BilliardSprite::init( float density /*= 1.0*/, 
						   float friction /*= 0.1*/, 
						   float restitution /*= 0.78*/)
{
	if (!Sprite::init())
	{
		return false;
	}
	// 创建精灵
	_sprite = Sprite::create(_picPath);
	_sprite->setScale(BALL_SCALE);
	this->addChild(_sprite);

	// bodyDef
	b2BodyDef bodyDef;
	if (!_isStatic)
	{
		bodyDef.type = b2_dynamicBody;
	}
	if (_isBullet)
	{
		bodyDef.bullet = true;
	}
	bodyDef.position.Set(_position.x / PTM_RATIO,_position.y / PTM_RATIO);

	// 创建body
	_body = _world->CreateBody(&bodyDef); 
	
	_body->SetUserData(this);

	b2CircleShape circle;
	circle.m_radius = BALL_SCALE*(_sprite->getContentSize().width / 2 ) / PTM_RATIO;
	if (_isStatic)
	{
		// 静态
		_body->CreateFixture(&circle,0.0f);
	} else
	{
		// 动态
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		_body->CreateFixture(&fixtureDef);
	}
	this->scheduleUpdate();

	return true;
}

