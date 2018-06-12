#ifndef __BILLIARDS_H__
#define __BILLIARDS_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameConfig.h"
USING_NS_CC;
using namespace cocos2d;

class BilliardSprite : public Sprite
{
public:
	BilliardSprite(const char* name, bool isStatic, bool isBullet,
		b2World* world, std::string picPath, Vec2 position, int score);
	~BilliardSprite();

	virtual void update(float t);

	virtual bool init(
		float density     = 1.0,     // density default     =  1.0f
		float friction    = 0.1,     // friction default    =  0.1f
		float restitution = 0.78);   // restitution default =  0.78f
	
	void SetLinearVelocity(b2Vec2 velocity) { _body->SetLinearVelocity(velocity); };
	b2Vec2 GetLinearVelocity() { return _body->GetLinearVelocity(); };
	void ApplyForceToCenter(b2Vec2 velocity, b2Vec2 point,bool wake) { _body->ApplyForce(velocity,point,wake); }
	b2Vec2 GetWorldCenter() { return _body->GetWorldCenter(); }

	char * getName() { return _name; };
	void setName(char* name) { _name = name; };

	b2Vec2 getPosition() { return _body->GetPosition(); };
	void setb2Vec2Position(b2Vec2 b2vPos) {
		_body->SetTransform(b2vPos, _body->GetAngle());
	}
	void setScore(int score) { _score = score; };
	void updateScore(int score) { _score += score; };
	int getScore() { return _score; };
	
private:
	b2Body* _body;
	char* _name;
	int _score;
	Sprite* _sprite;
	
	bool _isStatic; 
	bool _isBullet;
    b2World* _world;
	std::string _picPath;
	Vec2 _position;
};

#endif