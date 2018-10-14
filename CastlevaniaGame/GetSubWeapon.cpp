#include "GetSubWeapon.h"
#include "World.h"

GetSubWeapon::GetSubWeapon() {}

GetSubWeapon::GetSubWeapon(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocity.y = -100;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
	weaponSprite = sprite;
}

GetSubWeapon :: ~GetSubWeapon()
{

}
void GetSubWeapon::Init(int _X, int _Y)
{
	position.x = _X;
	position.y = _Y;
}
void GetSubWeapon::Init(int _X, int _Y, int _type)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(12, -12, -16, 16);
	switch (_type)
	{
	case GETKNIFE:
		itemType = GETKNIFE;
		sprite->Next(0, 0);
		break;
	case GETAXE:
		itemType = GETAXE;
		sprite->Next(1, 1);
		break;
	case GETBOOMERANG:
		itemType = GETBOOMERANG;
		sprite->Next(2, 2);
		break;
	case GETWATER:
		itemType = GETWATER;
		sprite->Next(3, 3);
		break;
	case GETWATCH:
		itemType = GETWATCH;
		sprite->Next(4, 4);
		break;
	}
}


void GetSubWeapon::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		isActive = false;
	if (velocity.y == 0)
		return;
	if (isActive)
	{
		position.y += velocity.y * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			switch (itemType)
			{
			case GETKNIFE:
				sprite->Next(0, 0);
				break;
			case GETAXE:
				sprite->Next(1, 1);
				break;
			case GETBOOMERANG:
				sprite->Next(2, 2);
				break;
			case GETWATER:
				sprite->Next(3, 3);
				break;
			case GETWATCH:
				sprite->Next(4, 4);
				break;
			}
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocity.y = 0;
	}


}

void GetSubWeapon::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void GetSubWeapon::Destroy()
{
	isActive = false;
}

void GetSubWeapon::Collision(Player *player)
{
	isActive = false;
	switch (itemType)
	{
	case GETKNIFE:
		player->subWeapon = KNIFE;
		break;
	case GETAXE:
		player->subWeapon = AXE;
		break;
	case GETBOOMERANG:
		player->subWeapon = BOOMERANG;
		break;
	case GETWATER:
		player->subWeapon = HOLYWATER;
		break;
	case GETWATCH:
		player->subWeapon = GETWATCH;
		break;
	}
	
}