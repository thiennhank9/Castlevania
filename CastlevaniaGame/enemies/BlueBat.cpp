#include "BlueBat.h"
#include "../engine/Sprite.h"


BlueBat::BlueBat() {}

BlueBat::BlueBat(LPD3DXSPRITE _SpriteHandler, World *_manager) : Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	spriteLeft->_Index = 18;
	spriteRight->_Index = 18;
	sprite = spriteLeft;

}


BlueBat :: ~BlueBat()
{

}

void BlueBat::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	velocity.y = -250;

	if (isRight)
		velocity.x = -160;
	else
		velocity.x = 160;
}

void BlueBat::Init(int _X, int _Y)
{
}

void BlueBat::Update(const float &_DeltaTime)
{
	// set sprites with direction
	if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	// move
	position.x += velocity.x * _DeltaTime;
	position.y += velocity.y * _DeltaTime;

	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		velocity.y = velocity.y / 2;
		sprite->Next(18, 22);
		timerSprite -= 0.2f;
	}
}



void BlueBat::Render()
{
	sprite->Render(position.x, position.y);
}

void BlueBat::Destroy()
{

}

void BlueBat::Collision()
{

}