#include "Panther.h"
#include "../engine/Sprite.h"

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager) : Enemy(_SpriteHandler, _manager)
{

	collider->setCollider(6, -32, -14, 14);


}

Panther :: ~Panther()
{

}

void Panther::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	position.y = _Y;
	position.x = _X;
	if (isRight)
		velocity.x = -150;
	else
		velocity.x = 150;
}
void Panther::Init(int _X, int _Y)
{
}

void Panther::Update(const float &_DeltaTime)
{

	position.x += velocity.x * _DeltaTime;
	if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(3, 4);
		timerSprite = 0;
	}

}



void Panther::Render()
{
	sprite->Render(position.x, position.y);
}

void Panther::Destroy()
{

}

void Panther::Collision()
{

}