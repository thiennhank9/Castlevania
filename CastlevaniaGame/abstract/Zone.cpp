#include "Zone.h"

//Zone::Zone() {}

Zone::Zone(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = 0;	// for sub class
	collider = new Collider();
}

Zone :: ~Zone()
{

}

void Zone::Init(int _top, int _bottom, int _left, int _right)
{
	// convert form topleft coordinate to center coordinate
	position.x = (_left + _right) / 2;
	position.y = (_top + _bottom) / 2;	// clear previous position set

	collider->top = (_top - _bottom) / 2;
	collider->bottom = collider->top;

	collider->left = (_left - _right) / 2;
	collider->right = -collider->left;
}

void Zone::Update(const int &_deltaTime)
{
	// không có gì để update cả
}

void Zone::Render()
{
	// chẳng có gì để update luôn
}

void Zone::Destroy()
{

}

void Zone::Collision(Player *actor, const float _DeltaTime)
{
	// virtual
}