#ifndef _FISH_H_
#define _FISH_H_

#include "../abstract/Enemy.h"

class Fish :
	public Enemy

{
public:
	int health;

	bool jumping; // trang thai nhay tu duoi len
	
	//float isFiring; // bien xac dinh con ca co dang ban hay ko
	float timer;
	
	Fish();
	Fish(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Fish();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Update(float _X, float _Y);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void Init(int _X, int _Y, bool isRight);
};
#endif // !_FISH_H_


