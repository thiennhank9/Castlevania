#ifndef _FISH_H_
#define _FISH_H_

#include "Enemy.h"
#include "EnemyFire.h"

class Fish :
	public Enemy

{
public:

	// trang thai nhay tu nuoc len
	bool jumping;

	// trang tha�i con ca?m�� mi��ng b��n
	bool isFiring;

	//bien do thoi gian de con ca tan cong
	float TimeToAttack;

	//khoang thoi gian can thiet de co the tan cong
	float timer;


	Fish();
	Fish(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Fish();
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, bool isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	virtual void CheckActive();

};
#endif // !_FISH_H_


