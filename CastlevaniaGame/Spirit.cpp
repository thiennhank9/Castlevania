#include "Spirit.h"

Spirit::Spirit() {}

Spirit::Spirit(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = EFFECT_TYPE;
	effectType = EFFECT_SPIRIT;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", 64, 64, 7, 6);

	isActive = false;
}

Spirit :: ~Spirit()
{

}

void Spirit::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	sprite->Next(1, 2);
	timeSurvive = 0;
	timerSprite = 0;
}

void Spirit::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 0.5f)
		isActive = false;
	if (isActive)
	{
		timerSprite += _deltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(1, 2);
			timerSprite = 0;
		}
	}
}

void Spirit::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Spirit::Destroy()
{
	isActive = false;
}

