#include "Knight.h"
#include "../engine/Sprite.h"

Knight::Knight() {}

Knight::Knight(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(28, -32, -14, 14);
	spriteLeft->_Index = 14;
	spriteRight->_Index = 14;
}

Knight :: ~Knight()
{

}


void Knight::Init(int _X, int _Y)
{
	/*health = 8;

	isActive = true;
	postY = _Y;
	postX = _X;
	if (manager->Simon->isRight)
		velocityX = -30;
	else
		velocityX = 30;*/

}

void Knight::Init(int X, int Y, bool isRight, int Left, int Right)
{
	health = 8;

	isActive = true;
	position.y = Y;
	position.x = X;
	maxLeft = Left;
	maxRight = Right;
	if (isRight)
		velocity.x = -50;
	else
		velocity.y = 50;
}

void Knight::Update(const float &_DeltaTime)
{
	position.x += velocity.x * _DeltaTime;
	if (position.x >= maxRight)
	{
		if (velocity.x > 0)
		{
			velocity.x *= -1;
			sprite = spriteLeft;
		}
	}
	else if (position.x <= maxLeft)
	{
		if (velocity.x < 0)
		{
			velocity.x *= -1;
			sprite = spriteRight;
		}
	}
	timerSprite += _DeltaTime;
	if (timerSprite >= (ANIM_TIME * 3))
	{
		sprite->Next(14, 17);
		timerSprite = 0;
	}


}


void Knight::Render()
{
	sprite->Render(position.x, position.y);
}

void Knight::Destroy()
{
	
}

void Knight::Collision()
{
	Enemy::Collision();
}

void Knight::CheckActive()
{
	/*if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;*/

}
