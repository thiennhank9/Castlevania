#ifndef _PANTHER_H_
#define _PANTHER_H_

#include "../abstract/Enemy.h"

class Panther :
	public Enemy

{
public:
	int health;
	Panther();
	Panther(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Panther();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void Init(int _X, int _Y, bool isRight);
};
#endif // !_PANTHER_H_

