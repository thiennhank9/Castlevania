#include "Item.h"
#include "World.h"
Item::Item() {}

Item::Item(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 64;
	sizeHeight = 64;

	//position.x = 400;
	velocity.x = 0.2f;

	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Item :: ~Item()
{

}

void Item::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
}

void Item::Init(int _X, int _Y, int _level)
{
	position.x = _X;
	position.y = _Y;
}


void Item::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= ITEM_TIME)
		isActive = false;
}

void Item::Render()
{
	if (!isActive)
		return;
	sprite->Render(position.x, position.y);
}

void Item::Destroy()
{
	isActive = false;
}

void Item::Collision(Player *player)
{
	isActive = false;
	
}

bool Item::CheckGroundCollision(World * manager, const float _DeltaTime)
{
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject* tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)tempObject)->typeGround)
				{
				case GROUND_BLOCK:
					if
						(normaly > 0.1f)//chạm từ trên xuống
						return true;
					break;
				}
			}
			break;
		}
	}
	return false;
}

Item * Item::CreateItem(int itemType, int _X, int _Y, LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	Item* item=new Item();
	switch (itemType)
	{
	case HEART:
		item = new Heart(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case BIGHEART:
		item = new BigHeart(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case BAG100:
		item = new MoneyBag(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG100);
		break;
	case BAG400:
		item = new MoneyBag(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG400);
		break;
	case BAG700:
		item = new MoneyBag(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG700);
		break;
	case BAG1000:
		item = new Treasure(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG1000);
		break;
	case WHIPUPGRADE:
		item = new WhipUpgrade(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case GETKNIFE:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETKNIFE);
		break;
	case GETAXE:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETAXE);
		break;
	case GETWATER:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETWATER);
		break;
	case GETWATCH:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETWATCH);
		break;
	case GETBOOMERANG:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETBOOMERANG);
		break;
	case CROSS:
		item = new Cross(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case POTION:
		item = new Potion(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case CHICKEN:
		item = new Chicken(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case MULTIPLY:
		item = new Multiply(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case TREASURE:
		item = new Treasure(_SpriteHandler, _manager);
		item->Init(_X, _Y, TREASURE);
		break;
	case CROWN:
		item = new Treasure(_SpriteHandler, _manager);
		item->Init(_X, _Y, CROWN);
		break;
	}
	return item;
}
