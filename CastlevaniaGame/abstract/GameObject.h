//======= GAMEOBJECT ========

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <iostream>
#include <d3dx9.h>
#include "../engine/Sprite.h"
#include "Misc.h"

#include <cstdlib>
#include <ctime>

//#include <math.h>

#define PLAYER_TYPE 1
#define PROJECTILE_TYPE 2
#define EFFECT_TYPE 3
#define ITEM_TYPE 4
#define ENEMY_TYPE 5
#define DESTRUCTIBLE_TYPE 6
#define GROUND_TYPE 7
#define STAIR_TYPE 8
#define ZONE_TYPE 9

#define ANIM_TIME 0.15f
#define IMMORTAL_TIME 0.3f

#define PI 3.141592f
#define val PI/180


class GameObject
{
public:
	// các biến
	World *manager;
	LPD3DXSPRITE spriteHandler; // Nguyen them

	bool isActive;
	int objectType;

	int sizeWidth;
	int sizeHeight;

	float postX;
	float postY;
		
	//LPD3DXSPRITE spriteHandler;
	Sprite *sprite;
	float timerSprite;

	Collider *collider;

	//Vector2 position
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;

	// constructor và destructor
	GameObject();
	virtual ~GameObject();

	// ====== CÁC HÀM CHÍNH ======
	// vị trí collistion (= vector0 nếu ko chạm)
	D3DXVECTOR3 vecCollide(GameObject *target);
	// xét coi có va chạm ko
	bool Intersect(GameObject *target);
	//Hàm va chạm sweptAABB
	float sweptAABB(GameObject *target,const float _deltatime);

	// ====== các phương thức ảo =====
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	
};

#endif // !_GAMEOBJECT_H_


