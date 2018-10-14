#include "HolyWater.h"
#include "World.h"
#include "GroupObject.h"


HolyWater::HolyWater(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = HOLYWATER;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 8;
	spriteRight->_Index = 8;
	spriteLeft->_Index = 8;
	Damage = 2;
	isReverted = false;

}
HolyWater::~HolyWater()
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
void HolyWater::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	isRight = manager->Simon->isRight;

	velocity.y = 400;

	if (isRight)
	{
		velocity.x = 150;
		sprite = spriteRight;
	}
	else
	{
		velocity.x = -150;
		sprite = spriteLeft;
	}
	
}

void HolyWater::Update(const float &_DeltaTime)
{
	CollisionObject(_DeltaTime);
	if (!isActive)
		return;
	timerSprite += _DeltaTime;

	position.x += velocity.x*_DeltaTime;
	//xac dinh tọa do Y
	velocity.y += -(1000 * _DeltaTime);
	position.y += (velocity.y * _DeltaTime);

	if (!IsInCamera())
	{
		isActive = false;
		return;
	}
	
	if (manager->Simon->isAttack && manager->Simon->killingMoment)
		CollisionObject(_DeltaTime);
}
void HolyWater::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void HolyWater::Destroy()
{

	isActive = false;
}
void HolyWater::Collision()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		if (manager->holyFire[i]->isActive)
			count++;
	}

	if (count <= manager->Simon->weaponNumber)
		manager->holyFire[count]->Init(position.x, position.y);
	isActive = false;
}

void HolyWater::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				//switch (((Ground*)tempObject)->typeGround)
				//{
				//case GROUND_BLOCK:
				//	if (normaly > 0.1f)//chạm từ trên xuống
				//		Collision();
				//	break;
				//}
				Collision();
			}
			break;
		}
	}
}