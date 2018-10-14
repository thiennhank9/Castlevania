#include "Ghoul.h"
#include "Sprite.h"
#include "World.h"
Ghoul::Ghoul() {}

Ghoul::Ghoul(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(24, -32, -14, 14);
	enemyType = GHOUL;
}

Ghoul :: ~Ghoul()
{

}

void Ghoul::Init(int _X, int _Y, bool isRight)
{
	health = 1;

	isActive = true;
	position.y = _Y;
	position.x = _X;
	if (isRight)
		velocity.x = -70;
	else
		velocity.x = 70;
}
void Ghoul::Init(int _X, int _Y)
{
	isActive = true;
	position.y = _Y;
	position.x = _X;
	velocity.x = -70;
	velocity.y = 0;
}

void Ghoul::Update(const float &_DeltaTime)
{
	position.x += velocity.x * _DeltaTime;
	position.y += velocity.y * _DeltaTime;
	
	if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(0, 1);
		timerSprite = 0;
	}

	// ghoul neu khong va cham voi ground se roi xuong
	if (!CheckGroundCollision(_DeltaTime))
	{
		velocity.y = -200;
	}
	else
	{
		velocity.y = 0;
	}
}

void Ghoul::Render()
{
	sprite->Render(position.x, position.y);
}

void Ghoul::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 100;
	isActive = false;
}

void Ghoul::Collision()
{
	Enemy::Collision();
}

void Ghoul::CheckActive()
{
	if (position.x < Sprite::cameraX || position.x > Sprite::cameraX + 512)
		isActive = false;
}

bool Ghoul::CheckGroundCollision(const float &_DeltaTime)
{
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			// ghoul va cham voi ground
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)tempObject)->typeGround)
				{
				case GROUND_BLOCK:
					return true;
					break;
				default:
					break;
				}
			}
		default:
			break;
		}
	}
	return false;
}

