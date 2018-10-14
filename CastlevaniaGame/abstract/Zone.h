#ifndef _ZONE_H_
#define _ZONE_H_

#include "GameObject.h"
#include "Player.h"
#define ZONE_GATEWAY 1

class Zone :
	public GameObject

{
public:
	int typeZone;

	//Zone();
	Zone(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Zone();
	virtual void Init(int _top, int _bottom, int _left, int _right);
	virtual void Update(const int &_deltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *actor, const float _DeltaTime);
};
#endif // !_ZONE_H_



