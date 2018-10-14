#include "MoneyBag.h"
#include "World.h"

MoneyBag::MoneyBag() {}

MoneyBag::MoneyBag(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocity.y = -100;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

MoneyBag :: ~MoneyBag()
{
	
}
void MoneyBag::Init(int _X, int _Y)
{
	position.x = _X;
	position.y = _Y;
}
void MoneyBag::Init(int _X, int _Y, int _type)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(12, -12, -16, 16);
	switch (_type)
	{
	case BAG100:
		itemType = BAG100;
		sprite->Next(13, 13);
		break;
	case BAG400:
		itemType = BAG400;
		sprite->Next(14, 14);
		break;
	case BAG700:
		itemType = BAG700;
		sprite->Next(15, 15);
		break;
	}
}


void MoneyBag::Update(const float &_DeltaTime)
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
			case BAG100:
				sprite->Next(13, 13);
				break;
			case BAG400:
				sprite->Next(14, 14);
				break;
			case BAG700:
				sprite->Next(15, 15);
				break;
			}
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocity.y = 0;
	}


}

void MoneyBag::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void MoneyBag::Destroy()
{
	isActive = false;
}

void MoneyBag::Collision(Player *player)
{
	isActive = false;
	switch (itemType)
	{
	case BAG100:
		player->score += 100;
		break;
	case BAG400:
		player->score += 400;
		break;
	case BAG700:
		player->score += 700;
		break;
	}
}