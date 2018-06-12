#include "GameContactListener.h"
#include "BilliardSprite.h"

GameContactListener::GameContactListener()
{

}

GameContactListener::~GameContactListener()
{

}

void GameContactListener::BeginContact(b2Contact*contact)
{
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	BilliardSprite* spriteA = (BilliardSprite*)(bodyA->GetUserData());
	BilliardSprite* spriteB = (BilliardSprite*)(bodyB->GetUserData());
	char *nameA = spriteA->getName();
	char *nameB = spriteB->getName();
	if (spriteA&&spriteB)
	{
		if (strcmp(nameA, "main") == 0 ||strcmp(nameA, ballName[10]) == 0)  //main ball or black ball
		{
			spriteA->updateScore(1);
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				if (strcmp(nameA, ballName[i]) == 0)
				{
					spriteA->updateScore(-1);
					if (isPlayer1Round)
						Player1Score++;
					else
						Player2Score++;
				}
			}
		}

		if (strcmp(nameB, "main") == 0 || strcmp(nameB, ballName[10]) == 0)  //main ball or black ball
		{
			spriteB->updateScore(1);
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				if (strcmp(nameB, ballName[i]) == 0)
				{
					spriteB->updateScore(-1);
					if (isPlayer1Round)
						Player1Score++;
					else
						Player2Score++;
				}
			}
			
		}
	}
}

void GameContactListener::EndContact(b2Contact* contact)
{
	// handle end event
}

void GameContactListener::PreSolve(b2Contact* contact,const b2Manifold* oldManifold)
{
	// handle pre-solve event
}

void GameContactListener::PostSolve(b2Contact* contact,const b2ContactImpulse* impulse)
{
	// handle post-solve event
}

void GameContactListener::deleteBody()
{
	
}