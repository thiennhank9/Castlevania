#include "Projectile.h"
#include "World.h"
#include "GroupObject.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Projectile::Projectile() {}

Projectile::Projectile(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PROJECTILE_TYPE;
	manager = _manager;
	collider = new Collider();
	position.x = 0;
	position.y = 0;
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
	isActive = false;
	position.x = _X;
	position.y = _Y;
}

// ---=== THE MAIN PROCESSING ===---
void Projectile::Update(const float &_DeltaTime)
{

}

void Projectile::Render()
{
}

void Projectile::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;

	//đây là 1 biến ảo dùng để tùy biến nó thành bất kỳ loại object khác khi xét va chạm
	GameObject* tempObject;

	// Check với những object đặc biệt phải xét va chạm
	for (int i = 0; i < (manager->groupSpecialCollision->number); i++)
	{

		tempObject = manager->groupSpecialCollision->objects[i];

		switch (tempObject->objectType)
		{
		// nếu trường hợp là enemy thì sẽ thực hiện cho enemy mất máu
		case ENEMY_TYPE:
			if ((this->projectileType != HOLYFIRE) && (this->projectileType != KNIFE) && (this->projectileType != WHIP))
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				// // -----------------
				if (collisionScale < 1.0f&& collisionScale > 0.0f)
				{
					((Enemy*)tempObject)->TakeDamage(Damage);
				}
			}
			else
			{

				// Các trường hợp ngoại lệ VD như HOLYFIRE WHIP KNIFE do
				// tự dưng xuất hiện ColliderBox do tới killing moment mới xuất hiện nên kg dùng sweptAABB bình thường được 
				// cái này phải dùng Intersect để xét va chạm
				if (IsCollide(tempObject))
				{
					((Enemy*)tempObject)->TakeDamage(Damage);
					if (this->projectileType == KNIFE)
						this->isActive = false;
				}
			}
			break;
		default:
			break;
		}
	}

	// check với các object cần được xét va chạm lấy ra từ quadtree
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{

		tempObject = manager->groupQuadtreeCollision->objects[i];

		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			if ((this->projectileType == WHIP) && ((Ground*)tempObject)->isBreakable)
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				if (collisionScale < 1.0f)
				{
					((Ground*)tempObject)->Destroy();
				}
			}
			break;
		case DESTRUCTIBLE_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				// // //------------
				if (this->projectileType == KNIFE)
					this->isActive = false;
				tempObject->Destroy();
			}
			
			break;
		default:
			break;
		}
	}
}

void Projectile::Destroy() {}

void Projectile::Collision() {}