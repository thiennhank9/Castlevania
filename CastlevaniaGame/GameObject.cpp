﻿// ------------  update K_1.5

#include "GameObject.h"
#include <limits>	// chứa std::numeric_limits

//#define max(a, b) (((a) > (b)) ? (a) : (b))
//#define min(a, b) (((a) < (b)) ? (a) : (b))
// ở đâu đó define rồi

// --- constructor & destructor ---
GameObject::GameObject()
{
	manager = NULL;

	isActive = false;
	objectType = 0;

	sizeWidth = 0;
	sizeHeight = 0;

	sprite = NULL;
	timerSprite = 0;
	collider = NULL;

	// ---- bo sung K_1.2
	BroadPhaseBox = NULL;

	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;
}


GameObject::~GameObject()
{
	if (collider != NULL)
	{
		delete collider;
	}
}

// --- === các hàm chính === ---

// trả về vị trí (của this) va chạm, trả về vector 0 nếu không có va chạm
// cách thức: swept AABB
// hàm này bỏ
D3DXVECTOR3 GameObject::VecCollide(GameObject *target)
{
	D3DXVECTOR3 temp(0, 0, 0);

	if ((target->collider == NULL) || (this->collider == NULL))
		return temp;

	// swept AABB here

	return temp;
}

// có va chạm hay không
// cách thức: có lồng vào nhau hay không
bool GameObject::IsCollide(GameObject* target)
{
	// cả 2 phải có collider mới va chạm được
	if ((target->collider == NULL) || (this->collider == NULL))
		return false;

	// cạnh trái của this > cạnh phải của target
	if ((position.x + collider->left) > (target->position.x + target->collider->right))
		return false;

	// cạnh phải của this < cạnh trái của target
	if ((position.x + collider->right) < (target->position.x + target->collider->left))
		return false;

	// cạnh trên của this < cạnh dưới của target
	if ((position.y + collider->top) < (target->position.y + target->collider->bottom))
		return false;

	// cạnh dưới của this > cạnh trên của target
	if ((position.y + collider->bottom) > (target->position.y + target->collider->top))
		return false;

	// ko thoả điều kiện nào hết => đang nằm lồng vào nhau
	return true;
}

// có nằm bên trong hay không
bool GameObject::IsInside(GameObject* target)
{
	// cả 2 phải có collider mới va chạm được
	if ((target->collider == NULL) || (this->collider == NULL))
		return false;

	if (((position.x + collider->left) > (target->position.x + target->collider->left)) && // vị trí cạnh trái ta > địch
		((position.x + collider->right) < (target->position.x + target->collider->right)) &&// vị trí cạnh phải ta < địch
		((position.x + collider->top) < (target->position.x + target->collider->top)) &&// vị trí cạnh trên ta < địch
		((position.x + collider->bottom) > (target->position.x + target->collider->bottom)))	// vị trí cạnh dưới ta > địch
		return true;

	// else
	return false;
}

bool GameObject::IsInCamera()
{
	if (collider == NULL)
		return false;
	if (position.x + collider->right <= Sprite::cameraX)
		return false;
	if (position.x + collider->left >= Sprite::cameraX + 512)
		return false;
	if (position.y + collider->top <= Sprite::cameraY - 480)
		return false;
	if (position.y + collider->bottom >= Sprite::cameraY)
		return false;
	return true;
}

// trả về vị trí (của this) va chạm, trả về 1.0f nếu không có va chạm
// cách thức: swept AABB
float GameObject::SweptAABB(GameObject *target, const float &_DeltaTime)
{
	// không có collider thì nghỉ sớm, bớt đau khổ
	if ((target->collider == NULL) || (this->collider == NULL))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// ---------------======== Broad - Phasing ============-------------
	// ------------- loại nhanh trường hợp không va chạm ---------------

	// delta velocity
	float deltaVX = ((this->velocity.x) - (target->velocity.x)) * _DeltaTime;
	float deltaVY = ((this->velocity.y) - (target->velocity.y)) * _DeltaTime;
	// thực ra không phải là hiệu vận tốc,
	// mà là hiệu đoạn đường đi được trong thời gian _DeltaTime
	// dùng để tính tỉ lệ với "đoạn đường va chạm"

	// tạo ra cái hộp bao quanh quỹ đạo của "this"
	if (BroadPhaseBox == NULL)
	{
		BroadPhaseBox = new Collider();
	}
	if (deltaVX > 0.0f)	// left & right
	{
		BroadPhaseBox->left = this->collider->left;
		BroadPhaseBox->right = (this->collider->right + deltaVX);
	}
	else
	{
		BroadPhaseBox->left = (this->collider->left + deltaVX);
		BroadPhaseBox->right = this->collider->right;
	}

	if (deltaVY > 0.0f) // top & bottom
	{
		BroadPhaseBox->top = (this->collider->top + deltaVY);
		BroadPhaseBox->bottom = this->collider->bottom;
	}
	else
	{
		BroadPhaseBox->top = this->collider->top;
		BroadPhaseBox->bottom = (this->collider->bottom + deltaVY);
	}

	// --- xét coi Box có lồng vào target hay không ------------------

	// cạnh trái của hộp > cạnh phải của target
	if ((position.x + BroadPhaseBox->left) > (target->position.x + target->collider->right))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh phải của hộp < cạnh trái của target
	if ((position.x + BroadPhaseBox->right) < (target->position.x + target->collider->left))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh trên của hộp < cạnh dưới của target
	if ((position.y + BroadPhaseBox->top) < (target->position.y + target->collider->bottom))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh dưới của hộp > cạnh trên của target
	if ((position.y + BroadPhaseBox->bottom) > (target->position.y + target->collider->top))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// end of Broad - Phasing
	// --------------------------===============================----------------------------


	// ---=== xét xem có lồng nhau ngay từ đầu không ===---
	if (this->IsCollide(target))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 0.0f;
	}

	// ---==== trường hợp không bị intersect ngay từ đầu ====---


	// --- chiều x gần nhất & xa nhất giữa 2 đối tượng ---
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	if (deltaVX > 0.0f)
	{
		dxEntry = (target->position.x + target->collider->left) - (this->position.x + this->collider->right);
		dxExit = (target->position.x + target->collider->right) - (this->position.x + this->collider->left);
		// 2 đối tượng rời xa nhau thì x gần nhất > x xa nhất (nghe có vẻ sai sai :v )
		// dùng từ "gần nhất" và "xa nhất" chỉ đúng khi 2 đối tượng đang hướng vào nhau
	}
	else
	{
		dxEntry = (target->position.x + target->collider->right) - (this->position.x + this->collider->left);
		dxExit = (target->position.x + target->collider->left) - (this->position.x + this->collider->right);
	}

	// --- chiều y gần nhất & xa nhất giữa 2 đối tượng ---
	if (deltaVY > 0.0f)
	{
		dyEntry = (target->position.y + target->collider->bottom) - (this->position.y + this->collider->top);
		dyExit = (target->position.y + target->collider->top) - (this->position.y + this->collider->bottom);
	}
	else
	{
		dyEntry = (target->position.y + target->collider->top) - (this->position.y + this->collider->bottom);
		dyExit = (target->position.y + target->collider->bottom) - (this->position.y + this->collider->top);
	}

	// --- "thời gian hun nhau" và "thời gian ngừng hun" trên mỗi chiều ---
	float txEntry, tyEntry;
	float txExit, tyExit;

	if (deltaVX == 0.0f)	// chống chia cho 0
	{		// so sánh == trong số floating thì không hay, mà thầy thích thì làm theo thầy
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / deltaVX;
		txExit = dxExit / deltaVX;
	}

	if (deltaVY == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / deltaVY;
		tyExit = dyExit / deltaVY;
	}

	// --- thời gian "hun" và "ngừng hun" trên cả 2 chiều
	float entryTimeScale = max(txEntry, tyEntry);
	float exitTimeScale = min(txExit, tyExit);

	// nếu như không có va chạm
	if ((entryTimeScale > exitTimeScale) || ((txEntry < 0.0f) && (tyEntry < 0.0f))
		|| (txEntry > 1.0f) || (tyEntry > 1.0f))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	//else // nếu như có va chạm
	// ở trên có return rồi thì còn else làm gì ta


	// tính toán vector pháp tuyến của bề mặt va chạm
	if (txEntry > tyEntry)
	{
		if (dxEntry < 0.0f)
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else
	{
		if (dyEntry < 0.0f)
		{
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else
		{
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}

	// trả về scale của thời gian va chạm
	//	0.0f < scale < 1.0f là có va chạm --- tại thời điểm (scale * _DeltaTime)
	// 0.0f va chạm intersect (lồng vào nhau sẵn)
	return entryTimeScale;
}

// ---------- update K_1.5
// thay vì di chuyển lồng vào trong tường => di chuyển đến sát tường
void GameObject::ResponseFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale)
{
	position.x += velocity.x * (_CollisionTimeScale * _DeltaTime);
	position.y += velocity.y * (_CollisionTimeScale * _DeltaTime);
}// nếu chạy hàm này thì không chơi post += velocity * _DeltaTime trong update nữa

 // văng vào tường thì bật ra
void GameObject::DeflectFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale)
{
	// di chuyển vào sát tường trước
	this->ResponseFrom(target, _DeltaTime, _CollisionTimeScale);

	// rồi mới bật ra
	if (normalx > 0.1f)	// tông bên phải
	{
		if (velocity.x < -0.0f)// đang chạy qua trái => văng ngược lại
			velocity.x *= -1;
	}
	else if (normalx < -0.1f) // tông bên trái
	{
		if (velocity.x > 0.0f)//	đang chạy qua phải => văng ngược lại
			velocity.x *= -1;
	}

	if (normaly > 0.1f) // tông phía trên
	{
		if (velocity.y < -0.0f)// đang rơi xuống => văng lên trên
			velocity.y *= -1;
	}
	else if (normaly < -0.1f) // tông phía dưới
	{
		if (velocity.y > 0.0f)// đang bay lên => văng xuống
			velocity.y *= -1;
	}

	position.x += velocity.x * (1.0f - _CollisionTimeScale) *_DeltaTime;
	position.y += velocity.y * (1.0f - _CollisionTimeScale) *_DeltaTime;
}

// ---------- update K_1.5
// phản hồi sau khi va chạm với GROUND
void GameObject::SlideFromGround(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale)
{
	//ResponseFrom(target, _DeltaTime, collisionTimeScale);
	// lỡ đụng 2,3 ground mà chạy cái này nhiều lần sẽ rất sai
	// "góc lag" sẽ làm đi luôn vào trong tường


	if (normalx > 0.1f)	// tông bên phải
	{
		this->position.x = (target->position.x + target->collider->right - this->collider->left) + 0.1f;
		position.x -= velocity.x*_DeltaTime;
		//velocity.x = 0.0f;
	}

	else if (normalx < -0.1f)// tông bên trái
	{
		this->position.x = (target->position.x + target->collider->left - this->collider->right) - 0.1f;
		position.x -= velocity.x*_DeltaTime;
		//velocity.x = 0.0f;
	}


	else if (normaly > 0.1f)	// tông ở trên
	{
		this->position.y = (target->position.y + target->collider->top - this->collider->bottom) + 0.1f;
		velocity.y = 0.0f;
	}
	else
		return;
}//----------------------------------

 // --- cac phuong thuc ao
 // reset this object
void GameObject::Init(int _X, int _Y)
{
	// thao tác để reset object này
}

// update object per frame
void GameObject::Update(const float &_DeltaTime)
{
	// gọi xử lý va chạm (nếu có)


	// xử lý vị trí
	// xử lý các vấn đề khác

}

// render object per frame
void GameObject::Render()
{
	// gọi sprite->Render() 
	// !!! HẠN CHẾ XỬ LÝ CPU TẠI ĐÂY !!!
	// video adapter đang chờ được "vẽ"
}


void GameObject::Destroy() {}
void GameObject::Collision() {};

// --- bo sung K_1.1
void GameObject::CollisionObject(GameObject *target, const float &_DeltaTime)
{
	// xét xem object có active không
	if (!(target->isActive))
		return;		// không active tức là không va chạm

					// xét xem object là gì (ba của mi là ai, ta còn biết đường xử lý)
	if ((target->objectType) == 0)
	{
		// sau khi biết đối tượng con nhà nông dân (dễ bắt nạt) => xét "đụng chạm"
		collisionTimeScale = this->SweptAABB(target, _DeltaTime);
		if (collisionTimeScale < 1.0f) // có đụng chạm đến ta, ta "xử" nó
		{
			// "xử" sao thì còn tuỳ ta là ai :v
		}
	}

	// ví dụ va chạm mặt đất
	if ((target->objectType) == GROUND_TYPE)
	{
		collisionTimeScale = this->SweptAABB(target, _DeltaTime);
		// nothing to do here, just a trash
	}
}
// ----------