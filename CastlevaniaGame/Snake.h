#pragma once
#ifndef _SNAKE_
#define _SNAKE_

#include "Enemy.h"

class Snake :
	public Enemy
{
public:
	Snake(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Snake();
	
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	void Snake::CollisionObject(float _DeltaTime);
};

#endif // !_SNAKE_


