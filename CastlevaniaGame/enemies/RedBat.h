#ifndef _REDBAT_H_
#define _REDBAT_H_

#include "../abstract/Enemy.h"

class RedBat :
	public Enemy

{
public:
	int health;
	float a; //dung de xac dinh ham sin
	RedBat();
	RedBat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~RedBat();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void Init(int _X, int _Y, bool isRight);
};
#endif // !_REDBAT_H_
