#include "Treasure.h"
#include "World.h"

Treasure::Treasure() {}

Treasure::Treasure(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Treasure :: ~Treasure()
{

}
void Treasure::Init(int _X, int _Y)
{
	position.x = _X;
	position.y = _Y;
}
void Treasure::Init(int _X, int _Y, int _type)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(12, -12, -16, 16);
	switch (_type)
	{
	case BAG1000:
		itemType = BAG1000;
		sprite->Next(13, 15);
		break;
	case TREASURE:
		itemType = TREASURE;
		sprite->Next(20, 21);
		break;
	case CROWN:
		itemType = CROWN;
		sprite->Next(18, 19);
		break;
	}
}


void Treasure::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 5.0f)
		isActive = false;

	timerSprite += _DeltaTime;
	if (timerSprite >= 0.1f)
	{
		switch (itemType)
		{
		case BAG1000:
			sprite->Next(13, 15);
			break;
		case TREASURE:
			sprite->Next(20, 21);
			break;
		case CROWN:
			sprite->Next(18, 19);
			break;
		}
		timerSprite = 0;
	}

}

void Treasure::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Treasure::Destroy()
{
	isActive = false;
}

void Treasure::Collision(Player *player)
{
	isActive = false;
	switch (itemType)
	{
	case BAG1000:
		player->score += 1000;
		break;
	case TREASURE:
	case CROWN:
		player->score += 2000;
		break;
	}
}