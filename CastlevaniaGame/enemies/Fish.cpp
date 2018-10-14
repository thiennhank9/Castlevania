#include "Fish.h"
#include "../engine/Sprite.h"
#include <time.h>

Fish::Fish() {}

Fish::Fish(LPD3DXSPRITE _SpriteHandler, World *_manager): Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -32, -13, 13);
	//isFiring = false;
	timer = 5;
	sprite->_Index = 12;
	spriteRight->_Index = 12;
}

Fish:: ~Fish()
{

}

void Fish::Init(int _X, int _Y, bool isRight)
{
	//isFiring = 0;
	isActive = true;
	position.y += 10;
	velocity.y = 450;
	position.x = _X;
	if (isRight)
		velocity.x = -80;
	else
		velocity.x = 80;
	jumping = true;
	
}
void Fish::Init(int _X, int _Y)
{
}

void Fish::Update(const float &_DeltaTime)
{
	if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	velocity.y += -(600 *_DeltaTime);
	position.y += (velocity.y * _DeltaTime);

	if (velocity.y < 0 && position.y < 94)
	{
		//Kết thúc nhảy
		jumping = false;
		position.y = 94;
		position.x += velocity.x * _DeltaTime;
		timerSprite += _DeltaTime;

		if (timerSprite >= 2 * ANIM_TIME)
		{	
			sprite->Next(11, 13);
			timerSprite = 0;
		}
	}
}

void Fish::Update(float _X, float _Y)
{

}


void Fish::Render()
{
	sprite->Render(position.x, position.y);
}

void Fish::Destroy()
{

}

void Fish::Collision()
{

}