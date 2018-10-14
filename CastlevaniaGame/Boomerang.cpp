#include "Boomerang.h"
#include "World.h"
#include "GroupObject.h"
#include <math.h>

Boomerang::Boomerang(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = BOOMERANG;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 5;
	spriteRight->_Index = 5;
	spriteLeft->_Index = 5;
	Damage = 4;
	collider->setCollider(10, -10, -10, 10);
	isReverted = false;


}
Boomerang::~Boomerang()
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
void Boomerang::Init(int _X, int _Y)
{
	isReverted = false;
	isActive = true;
	position.x = _X;
	isRight = manager->Simon->isRight;
	if (manager->Simon->isCrouch)
		position.y = _Y - 14;
	else
		position.y = _Y;

	if (isRight)
	{
		velocity.x = 200;
		sprite = spriteRight;
	}
	else
	{
		velocity.x = -200;
		sprite = spriteLeft;
	}

}

void Boomerang::Update(const float &_DeltaTime)
{

	// Hàm trên này quá dở nên viết lại hàm khác
	//timerSprite += _DeltaTime;

	//position.x += velocity.x*_DeltaTime;
	//if (position.x >= Sprite::cameraX + 512 || position.x <= Sprite::cameraX)
	//{
	//	position.x -= velocity.x*_DeltaTime;
	//	if (isRight)
	//	{
	//		if (isReverted)
	//		{
	//			isActive = false;
	//			return;
	//		}
	//		velocity.x = -200;
	//		sprite = spriteLeft;
	//		isRight = false;
	//		isReverted = true;
	//	}
	//	else
	//	{

	//		if (isReverted)
	//		{
	//			isActive = false;
	//			return;
	//		}
	//		velocity.x = 200;
	//		sprite = spriteRight;
	//		isRight = true;
	//		isReverted = true;
	//	}
	//	position.x += velocity.x*_DeltaTime;

	//}
	//if (timerSprite >= BOOM_ANIMATION_TIME)
	//{
	//	sprite->Next(5, 7);
	//	timerSprite -= BOOM_ANIMATION_TIME;
	//}
	//
	//if (SweptAABB(manager->Simon, _DeltaTime) < 1 && isReverted)
	//	isActive = false;
	//if (!IsInCamera())
	//	isActive = false;

	//CollisionObject(_DeltaTime);

	this->timerSprite += _DeltaTime;


	//Nếu Boomerang bay khỏi giới hạn phải của camera hoặc giới hạn trái (cameraX + 512 là giới hạn phải, cameraX là giới hạn trái
	if (this->position.x >= Sprite::cameraX + 512 || this->position.x <= Sprite::cameraX)
	{
		//Nếu Boomerang đã quay lại rồi
		if (this->isReverted)
		{
			this->isActive = false;
			return;
		}

		// Neu51 boomerang chưa quay lại thì xét nó đang bay về bên phải hay không
		if (this->isRight)
		{
			// Có thì cho nó reverted lại và thay đổi chiều vận tốc của nó, đổi trạng thái isRight thành false để báo nó đang đi về bên trái
			this->velocity.x = -200;
			this->sprite = this->spriteLeft;
			this->isRight = false;
			this->isReverted = true;
		}
		else
		{
			// Không thì cho nó reverted lại và thay đổi chiều vận tốc của nó, đổi trạng thái isRight thành true để báo nó đang đi về bên trái
			this->velocity.x = 200;
			this->sprite = this->spriteRight;
			this->isRight = true;
			this->isReverted = true;
		}
	}

	//cập nhật vị trí
	this->position.x += this->velocity.x * _DeltaTime;

	//xét định frame hình để cho boomerang xoay xoay
	if (timerSprite > BOOM_ANIMATION_TIME)
	{
		this->sprite->Next(5, 7);
		timerSprite -= BOOM_ANIMATION_TIME;
	}

	// Nếu gặp trúng Simon lúc quay về thì deactive hoặc ra khỏi màn hình thì deactive 
	if ( (this->SweptAABB(manager->Simon, _DeltaTime) < 1 && this->isReverted) || !this->IsInCamera())
	{
		this->isActive = false;
	}
	
	//Xét va chạm vật thể nào 
	this->CollisionObject(_DeltaTime);
}
void Boomerang::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void Boomerang::Destroy()
{
	isActive = false;
}
void Boomerang::Collision()
{
	isActive = false;
}