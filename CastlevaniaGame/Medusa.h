#pragma once
#pragma once
#ifndef _MEDUSA_H_
#define _MEDUSA_H_

#include "Enemy.h"

class Medusa :
	public Enemy

{
public:
	float thoigiandung;
	double a;
	bool isAttack;
	Medusa();
	Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Medusa();
	
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
};
#endif // !_MEDUSA_H_