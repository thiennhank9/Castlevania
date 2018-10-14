#include "RedBat.h"
#include "Sprite.h"
#include "World.h"


RedBat::RedBat() {}

RedBat::RedBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = REDBAT;
	// ---- update K_1.7
	spriteLeft->_Index = 7;
	spriteRight->_Index = 7;
}

RedBat :: ~RedBat()
{

}

void RedBat::Init(int _X, int _Y)
{
	health = 1;

	isActive = true;
	position.y = _Y;
	position.x = _X;
	a = 0;
	if (manager->Simon->isRight)
		velocity.x = -150;
	else
		velocity.x = 150;

	lineY = manager->Simon->position.y;
}

void RedBat::Init(int _X, int _Y, bool isRight)
{
	health = 1;

	isActive = true;

	//position.y = _Y;
	//position.y = manager->Simon->position.y;
	lineY = manager->Simon->position.y;

	position.x = _X;
	a = 0;

	if (manager->Simon->isRight)
	{
		velocity.x = -150;
		sprite = spriteLeft;
	}
	else
	{
		velocity.x = 150;
		sprite = spriteRight;
	}
	sprite->_Index = 7;
}

void RedBat::Update(const float &_DeltaTime)
{
	position.x += velocity.x * _DeltaTime;
	a += 0.05;
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		position.y = 20 * sin(a) + lineY;
		sprite->Next(7, 10);
		timerSprite = 0;
	}

	if ((position.x < Sprite::cameraX) || (position.x > Sprite::cameraX + 512))
		isActive = false;

}



void RedBat::Render()
{
	sprite->Render(position.x, position.y);
}

void RedBat::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void RedBat::Collision()
{
	Enemy::Collision();
}

void RedBat::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}
