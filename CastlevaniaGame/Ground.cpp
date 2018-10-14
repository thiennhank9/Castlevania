#include "Ground.h"

Ground::Ground() {}

Ground::Ground(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = GROUND_TYPE;
	typeGround = 0;
	isBreakable = false;
}

Ground :: ~Ground() {}

void Ground::Init(int _X, int _Y, int param1, int param2)
{
	position.x = _X;
	position.y = _Y;
}

//
void Ground::Update(const float &_DeltaTime)
{
}

void Ground::Render()
{
	sprite->Render(position.x, position.y);
}

void Ground::Destroy()
{

}

void Ground::Collision()
{

}