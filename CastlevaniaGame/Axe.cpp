#include "Axe.h"
#include "World.h"
#include "GroupObject.h"

Axe::Axe(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = AXE;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 1;
	spriteRight->_Index = 1;
	spriteLeft->_Index = 1;
	Damage = 4;
	isReverted = false;

	// update by k
	collider->setCollider(18, -18, -18, 18);
}
Axe::~Axe()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}
void Axe::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	isRight = manager->Simon->isRight;

	velocity.y = 600;

	// update by k
	if (isRight)
	{
		velocity.x = 200;
		sprite = spriteRight;
	}
	else
	{
		velocity.x = -200;
		sprite = spriteLeft;
	}
}

void Axe::Update(const float &_DeltaTime)
{
	
	if (!isActive)
		return;
	timerSprite += _DeltaTime;

	position.x += velocity.x*_DeltaTime;
	//xac dinh toòa do Y
	velocity.y += -(1000 * _DeltaTime);
	position.y += (velocity.y * _DeltaTime);
	if (timerSprite >= ANIM_TIME/1.5f)
	{
		sprite->Next(1,4);
		timerSprite -= ANIM_TIME/1.5f;
	}
	

	if (!IsInCamera())
	{
		isActive = false;
		return;
	}
	CollisionObject(_DeltaTime);
}
void Axe::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void Axe::Destroy()
{
	isActive = false;
}
void Axe::Collision()
{
	isActive = false;
}