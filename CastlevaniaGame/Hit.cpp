#include "Hit.h"

Hit::Hit() {}

Hit::Hit(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = EFFECT_TYPE;
	effectType = EFFECT_HIT;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", 64, 64, 7, 6);
	
	isActive = false;
}

Hit :: ~Hit()
{

}

void Hit::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	sprite->Next(0, 0);
	timeSurvive = 0;
	timerSprite = 0;
}

void Hit::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 0.5f)
		isActive = false;
	if (isActive)
	{
		timerSprite += _deltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(0, 0);
			timerSprite = 0;
		}
	}
}

void Hit::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Hit::Destroy()
{
	isActive = false;
}

