#include "Potion.h"
#include "World.h"

Potion::Potion() {}

Potion::Potion(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = POTION;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocity.y = -80;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Potion :: ~Potion()
{

}

void Potion::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(14, -14, -14, 14);
	sprite->Next(6, 6);
}


void Potion::Update(const float &_DeltaTime)
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
			sprite->Next(6, 6);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocity.y = 0;
	}


}

void Potion::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Potion::Destroy()
{
	isActive = false;
}

void Potion::Collision(Player *player)
{
	isActive = false;
	player->timeImmortal = -10;
	player->isImmortal = true;
}