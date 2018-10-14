#include "Panther.h"
#include "Sprite.h"
#include "World.h"

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(24, -24, -14, 14);
	enemyType = PANTHER;

	// ---- update K_1.7
	spriteLeft->_Index = 2;
	spriteRight->_Index = 2;
	// -----------
}

Panther :: ~Panther()
{

}


void Panther::Init(int _X, int _Y)
{
	health = 1;

	isActive = true;
	isSleeping = true;
	hasJumped = false;
	position.y = _Y;
	position.x = _X;
	if (manager->Simon->isRight)
		velocity.x = -30;
	else
		velocity.x = 30;
	velocity.y = -150;
}

void Panther::Update(const float &_DeltaTime)
{
	sprite = spriteLeft;
	if (manager->Simon->position.x > position.x - 200)
		isSleeping = false;
	if (!isSleeping)
	{
		if (!hasJumped)
		{
			position.x += velocity.x * _DeltaTime * 8;
			position.y -= velocity.y * _DeltaTime;

			timerSprite += _DeltaTime;

			if (timerSprite >= ANIM_TIME)
			{
				velocity.y += velocity.x*velocity.x / 5;
				sprite->Next(4, 4);
				timerSprite = 0;
			}

			if (Enemy::CheckGroundCollision(manager, _DeltaTime))
			{
				hasJumped = true;
			}
		}
		else
		{
			position.x += velocity.x * _DeltaTime * 8;
			timerSprite += _DeltaTime;

			if (timerSprite >= ANIM_TIME)
			{
				sprite->Next(3, 5);
				timerSprite = 0;
			}
		}			
	}
}



void Panther::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Panther::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void Panther::Collision()
{
	Enemy::Collision();
}

void Panther::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
	
}