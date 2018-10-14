#ifndef _KNIGHT_
#define _KNIGHT_

#include "Enemy.h"

class Knight :
	public Enemy

{
public:
	bool isSleeping;
	Knight();
	Knight(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Knight();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
	bool CheckGroundCollision(World * manager, const float _DeltaTime);
};
#endif // !_Knight_H_

