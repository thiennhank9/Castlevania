#include "BattleBoss.h"
#include "Player.h"
#include "World.h"
#include "Enemy.h"


BattleBoss::BattleBoss(LPD3DXSPRITE _SpriteHandler, World *_manager) :Zone::Zone(_SpriteHandler, _manager)
{
	manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = ZONE_BATTLEBOSS;

	isActive = false;
}


BattleBoss::~BattleBoss() {}


// virtual function
void BattleBoss::Init(int _X, int _Y, int _Width, int _Height,// rect
	int rubbish1, int rubbish2,
	int rubbish3, int rubbish4, int rubbish5)
{
	isActive = true;
	// coordinate & collider
	Zone::Init(_X, _Y, _Width, _Height);
	// ----------

	// đối với grinder
	//if
	//iStack = _Stack;
	//status = 0;
}

// player đụng vào => phép màu xảy ra
void BattleBoss::Collision(Player *actor, const float &_DeltaTime)
{
	// khoá camera
	Sprite::cameraXLeft = Sprite::cameraX;
	Sprite::cameraXRight = Sprite::cameraX;

	// tìm boss và kích động nó 
		// !!! --- testing --- !!!
	manager->boss->isActive = true;
	this->isActive = false;
}