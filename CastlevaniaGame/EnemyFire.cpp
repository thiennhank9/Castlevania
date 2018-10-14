#include "EnemyFire.h"
#include "Sprite.h"
#include "World.h"

EnemyFire::EnemyFire() {}

EnemyFire::EnemyFire(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(2, -2, -3, 3);
	enemyType = ENEMYFIRE;
	spriteLeft->_Index = 28;
	spriteRight->_Index = 28;
}

EnemyFire :: ~EnemyFire()
{

}

void EnemyFire::Init(int _X, int _Y)
{
	// -----------
	health = 1;

	isActive = true;
	position.y = _Y;
	position.x = _X;
	if (!manager->Simon->isRight)
	{
		velocity.x = -150;
		sprite = spriteLeft;
	}
	else
	{
		velocity.x = 150;
		sprite = spriteRight;
	}

	sprite->_Index = 28;
}

void EnemyFire::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;
	position.x += velocity.x * _DeltaTime;

}



void EnemyFire::Render()
{
	if (!isActive)
		return;
	sprite->Render(position.x, position.y);
}

void EnemyFire::Destroy()
{
	manager->Simon->score += 100;
	isActive = false;
}

void EnemyFire::Collision()
{
	Enemy::Collision();
}

void EnemyFire::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}