#include "Projectile.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Projectile::Projectile() {}

Projectile::Projectile(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PROJECTILE_TYPE;
}


Projectile::~Projectile()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}

// ===== VIRTUAL =====
void Projectile::Init(int _X, int _Y)
{
	isActive = true;

	position.x = _X;
	position.y = _Y;
}

// ---=== THE MAIN PROCESSING ===---
void Projectile::Update(const float &_DeltaTime)
{
	position.x += (velocity.x * _DeltaTime);
	position.y += (velocity.y * _DeltaTime);
	//position.y = 94;

	if (velocity.x != 0)
		sprite->Next(0, 3);
}

void Projectile::Render()
{
	sprite->Render(position.x, position.y);
}

void Projectile::Destroy() {}

void Projectile::Collision() {}

