#include "Bar.h"
#include "World.h"

Bar::Bar(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	Ground::Ground(_SpriteHandler, _manager);
	// ko hiểu sao bị NULL chỗ này
	manager = _manager;
	objectType = GROUND_TYPE;
	typeGround = GROUND_BAR;


	// sẵn sàng render
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\ground_bar.bmp", 64,16, 1, 1);
	sprite->_Index = 0;

	// set giá trị collider
	collider = new Collider();
	collider->top = 8;
	collider->bottom = -8;
	collider->right = 32;
	collider->left = -32;

	// set các giá trị cơ bản
	isBreakable = false;
	isRight = false;
	collisionScale = 0.0f;
	wait = 0.0f;
	// set cái này có vẻ thừa
	velocity.y = 0.0f;
}

Bar::~Bar() {}

// cac ham virtual
void Bar::Init(int _X, int _Y, int rubbish1, int rubbish2)
{
	// không cần quan tâm tới rubbish làm gì
		//chẳng qua init của mấy cái ground cần 4 parameter thôi

	isActive = true;
	position.x = _X;
	position.y = _Y;
}

// update per frame
void Bar::Update(const float &_DeltaTime)
{
	// nếu đang trong khoảng thời gian chờ (sau khi va chạm cái gì đó)
	if (wait > 0.0f)
	{
		wait -= _DeltaTime;
		return;
	}

	if (isRight)
	{
		velocity.x = 50;
	}
	else
	{
		velocity.x = -50;
	}

	HandlingCollision(_DeltaTime);

	position.x += (velocity.x*_DeltaTime);
}

// Check collision
void Bar::HandlingCollision(const float &_DeltaTime)
{
	float minCollisionScale = 1.0f;
	GameObject* objectNearest = NULL;
	// Xét va chạm với nhóm đối tượng trong quadtree. Ví dụ như Ground, Destructibe, Zone,...
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		
		tempObject = manager->groupQuadtreeCollision->objects[i];
		// loại trường hợp va chạm với chính nó
		if (tempObject == this)
		{
			continue;
		}

		if (tempObject->objectType == GROUND_TYPE)
		{

			collisionScale = SweptAABB(tempObject, _DeltaTime);
			// nếu có va chạm
			if (collisionScale < minCollisionScale)
			{
				minCollisionScale = collisionScale;	
				objectNearest = tempObject;
			}
		}
	}

	// xử lý va chạm với ground gần nhất
	if (objectNearest != NULL)
	{
		SlideFromGround(objectNearest, _DeltaTime, minCollisionScale);
		wait = 1.0f;
		if (isRight)
		{
			isRight = false;
			velocity.x = 0;
		}
		else
		{
			isRight = true;
			velocity.x = 0;
		}
	}
}

// render per frame
void Bar::Render()
{
	sprite->Render(position.x, position.y);
}

