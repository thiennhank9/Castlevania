#include "Enemy.h"
#define CREEP_COUNT_SPRITES 29
#define CREEP_SPRITE_PER_ROW 6
#define SIZE_WIDTH 64
#define SIZE_HEIGHT 64
Enemy::Enemy() 
{
	sizeWidth = SIZE_WIDTH;
	sizeHeight = SIZE_HEIGHT;
}

Enemy::Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	collider = new Collider();
	sizeWidth = 64;
	sizeHeight = 64;
	isActive = false;
	spriteHandler = _SpriteHandler;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, CREEP_COUNT_SPRITES, CREEP_SPRITE_PER_ROW);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, CREEP_COUNT_SPRITES, CREEP_SPRITE_PER_ROW);
	sprite = spriteLeft;
}

Enemy :: ~Enemy()
{

}

void Enemy::Init(int _X, int _Y)
{
}

void Enemy::Init(int _X, int _Y, bool isRight)
{
}


void Enemy::Update(const float &_DeltaTime)
{
}


void Enemy::Render()
{
}

void Enemy::Destroy()
{

}

void Enemy::Collision()
{

}