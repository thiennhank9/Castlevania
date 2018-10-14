#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../abstract/GameObject.h"

class Enemy :
	public GameObject

{
public:
	int health;

	Sprite *spriteLeft;
	Sprite *spriteRight;
	Enemy();
	Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager);
	virtual ~Enemy();

	//ham ao ke thua tu game object
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();


	virtual void Init(int _X, int _Y, bool isRight);
};
#endif // !_ENEMY_H_

