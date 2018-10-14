#include "GateWay.h"
//#include "Player.h"
//#include "Sprite.h"


GateWay::GateWay(LPD3DXSPRITE _SpriteHandler, World *_manager) :Zone::Zone(_SpriteHandler, _manager)
{
	//manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = ZONE_GATEWAY;
	collider = new Collider();

	sizeWidth = 64;
	sizeHeight = 64;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\gateway.bmp", sizeWidth-10, sizeHeight-10, 1, 1);
}


GateWay::~GateWay()
{
}

void GateWay::Render()
{
	sprite->Render(position.x, position.y);
}



// virtual function
void GateWay::Init(int _top, int _bottom, int _left, int _right,
	int _triggerX, int _triggerY, int _camXLeft, int _camXRight, int _camY)
{

	isActive = true;
	// convert form topleft coordinate to center coordinate
	position.x = (_left + _right) / 2;
	position.y = (_top + _bottom) / 2;	// clear previous position set

	collider->top = (_top - _bottom) / 2;
	collider->bottom = -collider->top;

	collider->left = (_left - _right) / 2;
	collider->right = -collider->left;

	triggerX = _triggerX;
	triggerY = _triggerX;
	camXLeft = _camXLeft;
	camXRight = _camXRight;
	camY = _camY;
}


void GateWay::Collision(Player *simon, const float _DeltaTime)
{
	simon->position.x = triggerX;
	simon->position.y = triggerY;

	Sprite::cameraXLeft = camXLeft;
	Sprite::cameraXRight = camXRight;
	Sprite::cameraY = camY;

	// !!! testing only
	simon->tempGround = 526;
}