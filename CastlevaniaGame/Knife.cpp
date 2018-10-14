#include "Knife.h"
#include "World.h"
#include "GroupObject.h"

Knife::Knife(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = KNIFE;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 0;
	spriteRight->_Index = 0;
	spriteLeft->_Index = 0;
	Damage = 3;

}
Knife::~Knife()
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
void Knife::Init(int _X, int _Y)
{
	isActive = true;
	if (manager->Simon->isCrouch)
		position.y = _Y - 14;
	else
		position.y = _Y;

	if (manager->Simon->isRight)
	{
		position.x = _X + 10;
		velocity.x = 250;
		sprite = spriteRight;
		collider->setCollider(10, -10, -18, 18);
	}
	else
	{
		position.x = _X -10;
		velocity.x = -250;
		sprite = spriteLeft;
		collider->setCollider(10, -10, -18, 18);
	}

}

void Knife::Update(const float &_DeltaTime)
{
	position.x += velocity.x*_DeltaTime;
	if (!IsInCamera())
		isActive = false;
	if (manager->Simon->isAttack && manager->Simon->killingMoment)
		CollisionObject(_DeltaTime);
}
void Knife::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void Knife::Destroy()
{
	isActive = false;
}
void Knife::Collision()
{
	isActive = false;
}
