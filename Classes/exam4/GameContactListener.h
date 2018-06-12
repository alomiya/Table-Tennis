#ifndef __GAME_CONTACTLISTENER_H__
#define __GAME_CONTACTLISTENER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameConfig.h"

#include <deque>
USING_NS_CC;
using namespace cocos2d;
using namespace std;

// ��ײ�����
class GameContactListener : public b2ContactListener
{

public:

	GameContactListener();;

	~GameContactListener();;

	// ��ײ��ʼ
	void BeginContact(b2Contact*contact);

	// ��ײ����
	void EndContact(b2Contact* contact);

	void PreSolve(b2Contact* contact,const b2Manifold* oldManifold);

	void PostSolve(b2Contact* contact,const b2ContactImpulse* impulse);

	void deleteBody();

	int Player1Score = 0;
	int Player2Score = 0;
	
	bool isPlayer1Round = true;
private:
	
};

#endif

