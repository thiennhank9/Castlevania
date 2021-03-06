#include "Bubble.h"

Bubble::Bubble() {}

Bubble::Bubble(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = EFFECT_TYPE;
	effectType = EFFECT_BUBBLE;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", 64, 64, 7, 6);

	isActive = false;
}

Bubble :: ~Bubble()
{

}

void Bubble::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	sprite->Next(6, 6);
	timeSurvive = 0;
	timerSprite = 0;
	velocity.x = 25;
	velocity.y = -200;
	heso = 1;
}
void Bubble::Init(int _X, int _Y, int _heso)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	sprite->Next(6, 6);
	timeSurvive = 0;
	timerSprite = 0;
	velocity.x = 25;
	velocity.y = -200;
	heso = _heso;
}

void Bubble::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 3.0f)
		Destroy();
	position.x += velocity.x * _deltaTime*heso;
	position.y -= velocity.y * _deltaTime;

	timerSprite += _deltaTime;

	if (timerSprite >= 0.2f)
	{
		velocity.y += velocity.x*velocity.x/5 ;
		sprite->Next(6, 6);
		timerSprite = 0;
	}
}

void Bubble::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Bubble::Destroy()
{
	isActive = false;
}

