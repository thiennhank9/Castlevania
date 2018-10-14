#include "Enemy.h"
#include "World.h"
Enemy::Enemy()
{
}

Enemy::Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	objectType = ENEMY_TYPE;
	manager = _manager;
	collider = new Collider();
	
	isActive = false;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteHandler = _SpriteHandler;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;


}

Enemy :: ~Enemy()
{

}

void Enemy::Init(int _X, int _Y)
{
}

void Enemy::Init(int _X, int _Y, bool _IsRight)
{
}

void Enemy::Update(const float &_DeltaTime)
{
}


void Enemy::Render()
{
}

void Enemy::Destroy()
{
	isActive = false;
}

void Enemy::TakeDamage(int Damage)
{
	health -= Damage;
	if (health <= 0)
		Destroy();
}

void Enemy::Collision()
{
	Effect* effect = Effect::CreateEffect(EFFECT_HIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	TakeDamage(NULL, 1);
}



void Enemy::CheckActive()
{

}

void Enemy::TakeDamage(GameObject * actor, int damage)
{
	health -= damage;
	if (health <= 0)
		Destroy();
}

Enemy * Enemy::CreateEnemy(int enemyType, int X, int Y, LPD3DXSPRITE _SpriteHandler, World * _manager)
{
	Enemy* enemy = new Enemy();
	switch (enemyType)
	{
	case KNIGHT:
		enemy = new Knight(_SpriteHandler, _manager);
		enemy->Init(X, Y);
		break;
	}
	return enemy;
}
bool Enemy::CheckGroundCollision(World * manager, const float _DeltaTime)
{
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject* tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)tempObject)->typeGround)
				{
				case GROUND_BLOCK:
					if (normaly > 0.1f)//chạm từ trên xuống
						return true;
					else
						return false;
					break;
				}
			}
			break;
		default:
			return false;
			break;
		}
	}
	
}