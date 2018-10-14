#ifndef _WORLD_H_
#define _WORLD_H_
#include "Player.h"
#include "Whip.h"
#include "Ghoul.h"
#include "RedBat.h"
#include "BlueBat.h"
#include "Panther.h"
#include "Fish.h"
#include "Item.h"
#include "Effect.h"
#include "GateWay.h"
#include "ThamSo.h"
#include "VamBat.h"
#include "Medusa.h"
#include "Snake.h"
#include "Knight.h"
//-------Item--------
#include "Heart.h"
#include "BigHeart.h"
#include "MoneyBag.h"
#include "Chicken.h"
#include "GetSubWeapon.h"
#include "Cross.h"
#include "Crystal.h"
#include "Multiply.h"
#include "Potion.h"
#include "Treasure.h"
#include "WhipUpgrade.h"

//------Effect-----
#include "Hit.h"
#include "Rubble.h"
#include "Spirit.h"
#include "Bubble.h"
#include "BossSpirit.h"
//------Projectile
#include "Whip.h"
#include "Knife.h"
#include "Boomerang.h"
#include "Axe.h"
#include "HolyFire.h"
#include "HolyWater.h"
//------Stair-------
#include "Stair.h"
class World
{
public:
	LPD3DXSPRITE spriteHandler;
	MainGame* castlevania;

	Sprite* background;
	
	Player* Simon;
	//GameObject *Ground;

	// !!! for testing
	Whip* whip;
	Fish* fish;
	Ghoul *ghoul;
	RedBat *redBat;
	BlueBat *blueBat;
	Knight *panther;
	Item *item;
	VamBat *vamBat;
	Medusa *medusa;
	Snake *snake;

	//Projectile
	Boomerang *boo[3];
	Knife *knife[3];
	Axe *axe[3];
	HolyFire *holyFire[3];
	HolyWater *holyWater[3];
	// ---- bo sung K_1.3 ---
	GroupObject *groupSpecialCollision;
	GroupObject *groupQuadtreeCollision;
	GroupObject *groupItem;
	GroupObject *groupEffect;
	GroupObject *groupProjectile;

	
	
	// ---- bo sung K_1.7 ---
	// 2 cái này cập nhật theo map
	GroupObject* groupEnemy;
	OTreeNode* rootGONode;

	// ---- bo sung K_1.9 // con trỏ boss
	GameObject* boss;
	
	int isPause;
	bool isFlash;
	int local; //bien random vi tri cua c?

	World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame);
	~World();

	void Init();
	void Update(float _DeltaTime);
	void Render();
	void CheckActive(float _DeltaTime);
	void Destroy();
};


#endif // !_WORLD_H_
