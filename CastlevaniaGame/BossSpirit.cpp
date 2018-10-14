#include "BossSpirit.h"

BossSpirit::BossSpirit() {}

BossSpirit::BossSpirit(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = EFFECT_TYPE;
	effectType = EFFECT_BOSSSPIRIT;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", 64, 64, 7, 6);

	isActive = false;
}

BossSpirit :: ~BossSpirit()
{

}

void BossSpirit::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	sprite->Next(3, 4);
	timeSurvive = 0;
	timerSprite = 0;
}

void BossSpirit::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 2.0f)
		isActive = false;
	if (isActive)
	{
		timerSprite += _deltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(3, 4);
			timerSprite = 0;
		}
	}
}

void BossSpirit::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void BossSpirit::Destroy()
{
	isActive = false;
}

