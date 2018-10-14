#include "Ground.h"

Ground::Ground() {}

Ground::Ground(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = GROUND_TYPE;
	isBreakable = false;


}

Ground :: ~Ground()
{

}

void Ground::Init(int _X, int _Y)
{

}

void Ground::Update(const int &_deltaTime)
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