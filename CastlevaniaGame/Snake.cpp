#include "Snake.h"
#include "World.h"
#include "GroupObject.h"

Snake::Snake(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	collider = new Collider();
	collider->setCollider(18, 4, 26, 72);

	position.x = 0;
	position.y = 0;
	sizeWidth = 32;
	sizeHeight = 20;
	enemyType = SNAKE;
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\snake.png", 32, 20, 2, 2);
	sprite = spriteRight;
	isActive = false;
}
Snake::~Snake()
{
	
}
void Snake::Init(int _X, int _Y)
{
	health = 1;

	isActive = true;
	position.x = _X;
	position.y = _Y;
	velocity.x = -160;
	
}

void Snake::Update(const float &_DeltaTime)
{
	if (!manager->medusa->isAttack)
		isActive = false;
	
	position.x += velocity.x*_DeltaTime;

	//position.y = velocity.y*_DeltaTime;
	timerSprite += _DeltaTime;

	if (timerSprite >= 0.2f)
	{
		
		sprite->Next(0, 1);
		timerSprite = 0;
	}
	if (manager->medusa->isAttack )
		CollisionObject(_DeltaTime);
}
void Snake::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void Snake::Destroy()
{
	isActive = false;
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 100;
}
void Snake::Collision()
{}

void Snake::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	/*for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{

		tempObject = manager->groupQuadtreeCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ENEMY_TYPE:
			if (tempObject->objectType == MEDUSA)
				break;
			else
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				if (collisionScale < 1.0f)
				{
					tempObject->Collision();
				}
				break;
			}
			
		default:
			break;
		}
	}*/
}