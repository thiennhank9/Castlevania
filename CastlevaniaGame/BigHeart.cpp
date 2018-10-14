#include "BigHeart.h"
#include "World.h"

BigHeart::BigHeart() {}

BigHeart::BigHeart(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ITEM_TYPE;
	itemType = BIGHEART;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocity.y = -80;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

BigHeart :: ~BigHeart()
{
	
}

void BigHeart::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(14, -14, -14, 14);
	sprite->Next(9, 9);
}


void BigHeart::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		Destroy();
	if (velocity.y == 0)
		return;
	if (isActive)
	{
		position.y += velocity.y * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(9, 9);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocity.y = 0;
	}
	
		
}

void BigHeart::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void BigHeart::Destroy()
{
	isActive = false;
}

void BigHeart::Collision(Player *player)
{
	player->heart += 5;
	Destroy();
}