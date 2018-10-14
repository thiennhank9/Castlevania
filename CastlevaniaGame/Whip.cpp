#include "Whip.h"
#include "World.h"
#include "GroupObject.h"

Whip::Whip(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = WHIP;
	sizeWidth = 256;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\whip_left.bmp", sizeWidth, sizeHeight, 18, 3);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\whip_right.bmp", sizeWidth, sizeHeight, 18, 3);
	sprite = spriteRight;
	whipLevel = 0;
	Damage = 3;
	isActive = false;

}
Whip::~Whip()
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
void Whip::Init(int _X, int _Y)
{
	isActive = true;

	position.x = _X;

	if (manager->Simon->isCrouch)
		position.y = _Y - 14;
	else
		position.y = _Y;

	if (manager->Simon->isRight)
	{
		sprite = spriteRight;
		// --------- update by k
		if (whipLevel < 2)
			collider->setCollider(18, 4, 26, 72);
		else
			collider->setCollider(18, 4, 26, 100);
	}
	else
	{
		sprite = spriteLeft;
		// --------- update by k
		if (whipLevel < 2)
			collider->setCollider(18, 4, -72, -26);
		else
			collider->setCollider(18, 4, -100, -26);
	}

	sprite->_Index = 3 * whipLevel;
	// ---------- update by k
	if (whipLevel < 1)
		Damage = 3;
	else
	{
		Damage = 4;
		if (whipLevel > 1)
		{
			sprite->_Index = 6;
			lvl3indexsprite = 6;
		}
	}
}

void Whip::Update(const float &_DeltaTime)
{
	if (!manager->Simon->isAttack)
		isActive = false;
	if (!isActive)
		return;
	position.x = manager->Simon->position.x;

	if (manager->Simon->isCrouch)
		position.y = manager->Simon->position.y - 14;
	else
		position.y = manager->Simon->position.y;

	// update by khang -------------
	if (manager->Simon->isChangeFrame)
	{
		switch (whipLevel)
		{
		case 0:
			sprite->Next(0, 2);
			break;
		case 1:
			sprite->Next(3, 5);
			break;
			//
		case 2:
			lvl3indexsprite += 4;
			break;
		}
	}

	if (whipLevel == 2)
	{
		sprite->Next(lvl3indexsprite, lvl3indexsprite + 3);
	}

	//-----------------------

	if (manager->Simon->isAttack && manager->Simon->killingMoment)
		CollisionObject(_DeltaTime);
}
void Whip::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void Whip::Destroy()
{
	isActive = false;
}
void Whip::Collision()
{}
