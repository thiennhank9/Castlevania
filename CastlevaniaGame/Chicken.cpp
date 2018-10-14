#include "Chicken.h"
#include "World.h"

Chicken::Chicken() {}

Chicken::Chicken(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = CHICKEN;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocity.y = -100;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Chicken :: ~Chicken()
{

}

void Chicken::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(10, -10, -16, 16);
	sprite->Next(10, 10);
}


void Chicken::Update(const float &_DeltaTime)
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
			sprite->Next(10, 10);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocity.y = 0;
	}
}

void Chicken::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Chicken::Destroy()
{
	isActive = false;
}

void Chicken::Collision(Player *player)
{
	isActive = false;
	player->health += 2;

	if (player->health > 16)
	{
		player->health = 16;
	}
}

void Chicken::Init(int _X, int _Y, int type)
{
}
