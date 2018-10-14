#include "RedBat.h"
#include "../engine/Sprite.h"


RedBat::RedBat() {}

RedBat::RedBat(LPD3DXSPRITE _SpriteHandler, World *_manager) : Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);

}

RedBat :: ~RedBat()
{

}

void RedBat::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	position.y = _Y;
	position.x = _X;
	a = 0;
	if (isRight)
		velocity.x = -150;
	else
		velocity.x = 150;
}
void RedBat::Init(int _X, int _Y)
{
}

void RedBat::Update(const float &_DeltaTime)
{
	if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;
	position.x += velocity.x * _DeltaTime;
	a += 0.05;
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		position.y = 20*sin(a) + 94;
		sprite->Next(7, 10);
		timerSprite = 0;
	}
	
}



void RedBat::Render()
{
	sprite->Render(position.x, position.y);
}

void RedBat::Destroy()
{

}

void RedBat::Collision()
{

}