#include "VamBat.h"
#include "Sprite.h"
#include "World.h"


VamBat::VamBat() {}

VamBat::VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = VAMBAT;
	spriteVamBat = new Sprite(_SpriteHandler, "Resources\\Sprites\\VamBat.png", 96, 46, 3, 3);
}

VamBat :: ~VamBat()
{

}

void VamBat::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	velocity.y = -250;
	velocity.x = -160;
	//if (manager->Simon->isRight)
	//	velocity.x = -160;
	//else
	//	velocity.x = 160;
}

void VamBat::Update(const float &_DeltaTime)
{
	// set sprites with direction
	/*if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;*/
	// move
	sprite = spriteVamBat;
	if (position.x >= 1000 - 400)
	{
		position.x += velocity.x * _DeltaTime;
		position.y += velocity.y * _DeltaTime;
	}
	
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		velocity.y = velocity.y / 2;
		sprite->Next(0, 2);
		timerSprite -= 0.2f;
	}
	else
	{
		velocity.y = -250;
	}

}



void VamBat::Render()
{
	sprite->Render(position.x, position.y);
}

void VamBat::Destroy()
{
	// hang 1
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 2
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 3
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 3000;
	isActive = false;

	// tạo item add vào world
	Item* newItem = Item::CreateItem(CRYSTAL, this->position.x, this->position.y, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);
}

void VamBat::Collision()
{
	Enemy::Collision();
}

void VamBat::CheckActive()
{
	if (manager->Simon->position.x<1000-200 || manager->Simon->position.x>1500) //zone của vamBat từ 1000 - 15000, bắt đầu hành động khi simon còn cách 200
		isActive = false;  
	else
		isActive = true;
}
